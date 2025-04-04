/**************************************************************************
 * Copyright (C) 2015 Eff'Innov Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Developped by Eff'Innov Technologies : contact@effinnov.com
 *
 **************************************************************************/

#include "framework_Timer.h"
#include "framework_Interface.h"
#include "framework_Allocator.h"

#include <stddef.h>
#include <stdlib.h>

#include <windows.h>

// NOTE : Recursive mutex implementation from : http://preshing.com/20120305/implementing-a-recursive-mutex/

typedef enum _eTimerState
{
    TIMER_STATE_NONE,
    TIMER_STATE_WAIT,
    TIMER_STATE_HAVE_TO_SLEEP,
    TIMER_STATE_HAVE_TO_EXIT
}eTimerState;

typedef struct tTimer
{
// ********************************************
    void                    *thread;
// ********************************************
    void                    *waitMutex;
    eTimerState              timerState;
// ********************************************
    void                    *contextMutex;
    uint32_t                 delay;
    framework_TimerCallBack *callBack;
    void                    *usercontext;
// ********************************************
    void                    *timerHandle;
// ********************************************
}tTimer_t;

typedef struct tRecMutex
{
    CRITICAL_SECTION    critSection;
}tRecMutex_t;

static void RecursiveMutex_Create(void ** context)
{
    tRecMutex_t *newContext = NULL;
    
    if (!context)
    {
        return;
    }
    
    *context = NULL;
    
    newContext = (tRecMutex_t*)framework_AllocMem(sizeof(tRecMutex_t));
    
    if (newContext)
    {
        InitializeCriticalSection(&(newContext->critSection));
        
        *context = newContext;
    }else
    {
    }
}

static void RecursiveMutex_Delete(void * context)
{
    tRecMutex_t *ctx = (tRecMutex_t*)context;
    
    if (!ctx)
    {
        return;
    }
    
    DeleteCriticalSection(&(ctx->critSection));
    
    framework_FreeMem(ctx);
}

static void RecursiveMutex_Lock(void *context)
{
    tRecMutex_t *ctx = (tRecMutex_t*)context;
    
    EnterCriticalSection(&(ctx->critSection));
    
}

static void RecursiveMutex_Unlock(void *context)
{
    tRecMutex_t *ctx   = (tRecMutex_t*)context;
    
    LeaveCriticalSection(&(ctx->critSection));
}

static void *timerThreadedFunc(void* context)
{
    tTimer_t *ctx            = (tTimer_t*)context;
    DWORD     result         = 0;
    void     *copyHandle     = 0;
    uint32_t  copyDelay      = 0;

    uint8_t seeSomewhereElseCompilator = 1;
    
    while (seeSomewhereElseCompilator)
    {
        framework_LockMutex(ctx->waitMutex);
        
        // ************************************ Check Timer Thread State ***************************
        // Should the timer wait ?
        if (ctx->timerState == TIMER_STATE_NONE)
        {
            // Timer is in idle state
            ctx->timerState = TIMER_STATE_WAIT;
            framework_WaitMutex(ctx->waitMutex,0);
        }
        
        // Check if timer thread has to exit.
        if (ctx->timerState == TIMER_STATE_HAVE_TO_EXIT)
        {
            // thread should exit.
            framework_UnlockMutex(ctx->waitMutex);
            break;
        }else
        {
            // Timer thread will now do the timing task.
            ctx->timerState = TIMER_STATE_NONE;
            framework_UnlockMutex(ctx->waitMutex);
        }
        
        // ************************************ Copy timer info ***************************
        RecursiveMutex_Lock(ctx->contextMutex);
        copyHandle = ctx->timerHandle;
        copyDelay  = ctx->delay;
        
        if (ctx->callBack != NULL)
        {
            // Reset the event, if it has been stopped, the callBack will be NULL.
            ResetEvent(ctx->timerHandle);
            RecursiveMutex_Unlock(ctx->contextMutex);
        
            // ************************************ Start Wait Procedure ***************************
            result = WaitForSingleObject(copyHandle, copyDelay);
            
            // ... and check wait result.
            switch(result)
            {
                case WAIT_TIMEOUT:
                {
                    // ************************************ Lock timer context ***************************
                    RecursiveMutex_Lock(ctx->contextMutex);
                    // Time out reached 
                    if (ctx->callBack)
                    {
                        ctx->callBack(ctx->usercontext);
                    }
                    RecursiveMutex_Unlock(ctx->contextMutex);
                    // ************************************ Unlock timer context ***************************
                    
                    break;
                }
                case WAIT_OBJECT_0:
                {
                    break;
                }
                default:
                {
                    // Aborted
                }
            }
        }else
        {
            // Aborted in the meanwhile.
            ResetEvent(ctx->timerHandle);
            RecursiveMutex_Unlock(ctx->contextMutex);
        }
    }
    return NULL;
}

void framework_TimerCreate(void** timer)
{
    tTimer_t *newTimer = NULL;
    
    // Allocate memory.
    newTimer = (tTimer_t*)framework_AllocMem(sizeof(tTimer_t));

	// Set variables.
    newTimer->timerState  = TIMER_STATE_NONE;

    newTimer->timerHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
    // Reset the new event.
    ResetEvent(newTimer->timerHandle);
    
    RecursiveMutex_Create(&(newTimer->contextMutex));
    framework_CreateMutex(&(newTimer->waitMutex));
    framework_CreateThread(&(newTimer->thread),timerThreadedFunc,newTimer);
    
    *timer = newTimer;
}


void framework_TimerDelete(void* timer)
{
    tTimer_t *ctx = (tTimer_t*)timer;
    
    // Stop the timer.
    framework_TimerStop(timer);
    
    // Indicate timer thread we need to exit.
    framework_LockMutex(ctx->waitMutex);
    if (ctx->timerState == TIMER_STATE_WAIT)
    {
        ctx->timerState = TIMER_STATE_HAVE_TO_EXIT;
        framework_NotifyMutex(ctx->waitMutex,0);
    }else
    {
        ctx->timerState = TIMER_STATE_HAVE_TO_EXIT;
    }
    framework_UnlockMutex(ctx->waitMutex);
    
    
    // Wait for timer thread to complete.
    framework_JoinThread(ctx->thread);
    
    // Free Memory.
    framework_DeleteThread(ctx->thread);
    framework_DeleteMutex(ctx->waitMutex);
    RecursiveMutex_Delete(ctx->contextMutex);
    
    CloseHandle(ctx->timerHandle);
    
    framework_FreeMem(ctx);
}


void framework_TimerStart(void* timer,uint32_t delay,framework_TimerCallBack *cb,void *usercontext)
{
    tTimer_t *ctx = (tTimer_t*)timer;
    
    // Stop any previous session.
    framework_TimerStop(timer);

    
    // Setup context variables.
    RecursiveMutex_Lock(ctx->contextMutex);
    ctx->delay       = delay;
    ctx->callBack    = cb;
    ctx->usercontext = usercontext;
    RecursiveMutex_Unlock(ctx->contextMutex);

    // Lock Thread status mutex.
    framework_LockMutex(ctx->waitMutex);
    // Change timer thread status.
    if (ctx->timerState == TIMER_STATE_WAIT)
    {
        // Thread is in idle state, unblock it.
        ctx->timerState = TIMER_STATE_HAVE_TO_SLEEP;
        framework_NotifyMutex(ctx->waitMutex,0);
    }else
    {
        // Not in idle state, timer thread will not goes to idle state and will process new timer.
        ctx->timerState = TIMER_STATE_HAVE_TO_SLEEP;
    }
    framework_UnlockMutex(ctx->waitMutex);
}


void framework_TimerStop(void* timer)
{
    tTimer_t *ctx = (tTimer_t*)timer;
    
    RecursiveMutex_Lock(ctx->contextMutex);
    ctx->delay       = 0;
    ctx->callBack    = NULL;
    ctx->usercontext = NULL;
    
    // Abort any pending WaitForSingleObject()
    SetEvent(ctx->timerHandle);
    RecursiveMutex_Unlock(ctx->contextMutex);
    
    // NOTE : Timer thread will automatically reset.
    
}

