#include "os.h"
#include "systick.h"
#include "printf.h"

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

#define UART0BASE 0x4000C000


void _putchar ( char character ) {
    PUT32(UART0BASE + 0x00, character);
}

#if 1
void SysTick_Handler ( void ) {
    _putchar('*');
    SYSTICK_CLEAN_IRQ(); // Clear pending interrupt
}
#endif

void SystemInit(void) {
#if 1
    PUT32(SYSTICK_CTRL_REG,   0x00000004);
    PUT32(SYSTICK_RELOAD_REG, 1000 - 1);   // Set the Reload value for required tick in STRELOAD.
    PUT32(SYSTICK_CTRL_REG,   0x00000007); // Enabled Systick Module, Select the CPU Clock Source and enable the SysTick interrupt
#endif
}

void main ( void ) {
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
        //~ msleep(100);
        Schedule();
    }

    TerminateTask();
}
