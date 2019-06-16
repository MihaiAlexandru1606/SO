/**
 * SO, 2016 - Lab #4, Semnale
 * Task #3, Windows
 *
 * Timers usage.
 */

#define _WIN32_WINNT    0x0500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include <windows.h>

#define _SECOND        10000000
#define TIMEOUT        (-2 * _SECOND)


/*
 * rutina APC asociata timer-ului
 */

static VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine ,
                                  DWORD dwTimerLowValue , DWORD dwTimerHighValue) {
    /* TODO: Use ctime and time to print current time. */
    time_t current_time;
    char* c_time_string;

    current_time = time(NULL);

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);
    printf ("%s\n", c_time_string);
}

/*
 * initializeaza si configureaza timer
 */

static void InitSetTimer(void) {
    /* TODO */
    HANDLE timerHandle;
    LARGE_INTEGER dueTime;

    timerHandle = CreateWaitableTimer(NULL, TRUE, NULL);
    if (timerHandle == NULL) {
        fprintf(stderr, "CreateWaitableTimer failed (%d)\n", GetLastError());
        exit(-1);
    }

    /* configure to expire in 5 seconds; base unit is 100ns */
    dueTime.QuadPart = TIMEOUT;
    if (SetWaitableTimer(timerHandle, &dueTime, 2000, TimerAPCProc, NULL, 0) == FALSE) {
        fprintf(stderr, "SetWaitableTimer failed (%d)\n", GetLastError());
        exit(-1);
    }

}

int main(void) {
     InitSetTimer ();        /* configureaza timer la 2 secunde */

    while (1) {
        /* TODO: Wait for timer (use SleepEx function). */
        SleepEx(INFINITE, TRUE);
    }



    return 0;
}
