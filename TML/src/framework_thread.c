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

#include "framework_windows.h"
#include "framework_Allocator.h"

// **************************************** OS Specific functions

// ####################### Thread

typedef struct tWinThread
{
    DWORD   dwThreadId;
    HANDLE  hThread;
    void* (*threadedFunc)(void *);
    void   *ctx;
    void   *mutexCanDelete;
    uint8_t isStarted;
}tWinThread_t;

DWORD WINAPI Thread_win32(LPVOID ref)
{
    tWinThread_t *winThread = (tWinThread_t *)ref;
    void *res = NULL;
    
    framework_LockMutex(winThread->mutexCanDelete);
    winThread->isStarted = 1;
    res = winThread->threadedFunc(winThread->ctx);
    framework_UnlockMutex(winThread->mutexCanDelete);
    return (DWORD)(uintptr_t)res;
}

eResult framework_CreateThread(void** threadHandle, void * (* threadedFunc)(void *) , void * ctx)
{
    tWinThread_t *winThread = (tWinThread_t *)framework_AllocMem(sizeof(tWinThread_t));
    memset(winThread, 0, sizeof(tWinThread_t));

    winThread->threadedFunc = threadedFunc;
    winThread->ctx          = ctx;
    winThread->isStarted    = 0;

    framework_CreateMutex(&(winThread->mutexCanDelete));

    winThread->hThread = CreateThread(
                     NULL,
                     0,
                     Thread_win32,
                     winThread,
                     0,
                     &(winThread->dwThreadId));

    *threadHandle = winThread;

    return FRAMEWORK_SUCCESS;
}

void framework_JoinThread(void * threadHandle)
{
    // Note this function is highly portable !
    tWinThread_t *winThread = (tWinThread_t*)threadHandle;

    if (framework_GetCurrentThreadId() != framework_GetThreadId(threadHandle))
    {
        // Will cause block if thread still running !!!
        framework_LockMutex(winThread->mutexCanDelete);
        // Check if the thread is started
        if (!winThread->isStarted)
        {
            // Not started !
            framework_UnlockMutex(winThread->mutexCanDelete);
            // Wait until it start.
            while(!winThread->isStarted)
            {
                // DEBUG SC38934
                framework_MilliSleep(1);
                // END DEBUG SC38934
            }
            // Thread started, wait to complete
            framework_LockMutex(winThread->mutexCanDelete);
        }
        framework_UnlockMutex(winThread->mutexCanDelete);
        // Thread now just ends up !
    }
}


void framework_DeleteThread(void * threadHandle)
{
    tWinThread_t *winThread = (tWinThread_t*)threadHandle;
    
    if (winThread->hThread)
    {
        CloseHandle(winThread->hThread);
        winThread->hThread = NULL;
    }
    framework_DeleteMutex(winThread->mutexCanDelete);

    framework_FreeMem(winThread);
}

void * framework_GetCurrentThreadId()
{
	DWORD temp;
	void *ptr = &temp;
	temp = GetCurrentThreadId();
	return ptr;
}

void * framework_GetThreadId(void * threadHandle)
{
    tWinThread_t *winThread = (tWinThread_t*)threadHandle;
	void *ptr = &(winThread->dwThreadId);
    return ptr;
}

void framework_MilliSleep(uint32_t ms)
{
    Sleep(ms);
}
