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

typedef struct tWinMutex
{
    void *handle;
    void *cond;
}tWinMutex_t;

eResult framework_CreateMutex(void ** mutexHandle)
{
    tWinMutex_t *mutex = (tWinMutex_t *)framework_AllocMem(sizeof(tWinMutex_t));

    mutex->handle = CreateMutex(NULL, FALSE, NULL);
    mutex->cond   = CreateEvent(NULL, TRUE, FALSE, NULL);
    ResetEvent(mutex->cond);
    
    *mutexHandle = mutex;

    return FRAMEWORK_SUCCESS;
}

void framework_LockMutex(void * mutexHandle)
{
    tWinMutex_t *mutex = (tWinMutex_t *)mutexHandle;
    DWORD result = WaitForSingleObject(mutex->handle, INFINITE);
    if ((result != WAIT_OBJECT_0)&&(result != WAIT_ABANDONED))
    {
    }
}

void framework_UnlockMutex(void * mutexHandle)
{
    tWinMutex_t *mutex = (tWinMutex_t *)mutexHandle;
    BOOL result = ReleaseMutex(mutex->handle);
    if (!result)
    {
    }
}

void framework_WaitMutex(void * mutexHandle, uint8_t needLock)
{
    tWinMutex_t *mutex = (tWinMutex_t *)mutexHandle;
    if (needLock)
    {
        framework_LockMutex(mutexHandle);
    }

    SignalObjectAndWait(mutex->handle, mutex->cond, INFINITE, FALSE);
    // NOTE : On Windows need to relock again
    framework_LockMutex(mutexHandle);

    ResetEvent(mutex->cond);

    if (needLock)
    {
        framework_UnlockMutex(mutexHandle);
    }
}

void framework_NotifyMutex(void * mutexHandle, uint8_t needLock)
{
    tWinMutex_t *mutex = (tWinMutex_t *)mutexHandle;
    if (needLock)
    {
        framework_LockMutex(mutexHandle);
    }
    SetEvent(mutex->cond);
    if (needLock)
    {
        framework_UnlockMutex(mutexHandle);
    }
}

void framework_DeleteMutex(void * mutexHandle)
{
    tWinMutex_t *mutex = (tWinMutex_t *)mutexHandle;

    // NOTE : If there is a pending WaitForSingleObject() the behavior is undefined.
    SetEvent(mutex->cond);
    ResetEvent(mutex->cond);
    CloseHandle(mutex->handle);
    CloseHandle(mutex->cond);
    framework_FreeMem(mutex);
}
