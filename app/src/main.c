#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "os.h"

char const * global_program_name;

// msleep(): Sleep for the requested number of milliseconds.
int msleep(long msec) {
    struct timespec ts;
    int res;
    if (msec < 0) {
        errno = EINVAL;
        return -1;
    }
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
    return res;
}

void SystemInit(void) {
    //~ set_signal_handler();
}

int main(int argc, char * argv[]) {
    global_program_name = argv[0];

    printf("[SystemInit]\n");
    SystemInit();

    printf("[StartOS]\n");
    StartOS(AppMode1);
}

void ErrorHook(void) {
    printf("ErrorHook was called\n");
    printf("Service: %ld, P1: %ld, P2: %ld, P3: %ld, RET: %ld\n",
        (long)OSErrorGetServiceId(),
        (long)OSErrorGetParam1(),
        (long)OSErrorGetParam2(),
        (long)OSErrorGetParam3(),
        (long)OSErrorGetRet()
    );
    ShutdownOS(0);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask) {
    printf("[InitTask]\n");

   /* open CIAA digital outputs */
   /* activate periodic task:
    *  - for the first time after 350 ticks (350 ms)
    *  - and then every 1000 ticks (1s)
    */
   SetRelAlarm(ActivatePeriodicTask, 350, 1000);

   TerminateTask();
}

/** \brief Periodic Task
 *
 * This task is started automatically every time that the alarm
 * ActivatePeriodicTask expires.
 *
 */
TASK(PeriodicTask) {
    printf("[PeriodicTask]\n");

    TerminateTask();
}

/** \brief My task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(MyTask) {
    printf("[MyTask]\n");

    while (TRUE) {
        printf("[Low Prio Task]\n");
        msleep(100);
        Schedule();
    }

    TerminateTask();
}
