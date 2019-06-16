/* do not use UNICODE */
#undef _UNICODE
#undef UNICODE

#define _WIN32_WINNT    0x500

#include <windows.h>
#include <stdio.h>

#include "utils.h"

#define PERIOD       1000
#define TIMES        3

HANDLE finished;

VOID CALLBACK TimerFunction(PVOID lpParam , BOOLEAN TimerOrWaitFired)
{
	static int count;
	BOOL bRet;

	printf ("'TimerFunction' has been called and count is %d\n" , count);

	/* TODO - check if we must increment counter or finish */
	if (count == TIMES - 1) {
		DIE(ReleaseSemaphore (finished , 1 , NULL) == FALSE ,
		    "ReleaseSemaphore");
	} else {
		count++;
	}

}

int main(void)
{
	HANDLE timer_queue;
	HANDLE timer;
	BOOL bRet;
	DWORD dwRet;

	/* create a TimerQueue */
	timer_queue = CreateTimerQueue ();
	DIE(timer_queue == NULL , "CreateTimerQueue");

	/* create a semaphore/event */
	finished = CreateSemaphore (NULL , 0 , 1 , NULL);
	DIE(finished == NULL , "Create Semaphore");

	/* create a timer and associate it with the timer queue */
	bRet = CreateTimerQueueTimer (
		&timer ,
		timer_queue ,
		TimerFunction ,
		NULL ,
		0 ,
		PERIOD ,
		0
	);
	DIE(bRet == FALSE , "CreateTimerQueueTimer");

	/* wait for the semaphore/event to be set, so we can free resources */
	dwRet = WaitForSingleObject (finished , INFINITE);
	DIE (dwRet == WAIT_FAILED , "WaitForSingleObject");

	/*  delete the timer queue and its timers */
	bRet = DeleteTimerQueueTimer (
		timer_queue ,
		timer ,
		NULL
	);
	DIE(bRet == FALSE , "DeleteTimerQueueTimer");

	return 0;
}
