#include "os.h"
#include "systick.h"
#include "printf.h"

#include "Os_Internal_Arch_Cfg.h"
#include "Os_Internal_Cfg.h"


void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int GET8 ( unsigned int );
unsigned int GETPC ( void );

#define UART0BASE 0x4000C000


void _putchar ( char character ) {
    PUT32(UART0BASE + 0x00, character);
}

void puts( const char * str ) {
    char c;
    while ((c = *str)) {
        PUT32(UART0BASE + 0x00, c);
        str++;
    }
}

#if 0
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
    puts("[Tasks]\n");
    for (unsigned int loopi = 0; loopi < TASKS_COUNT; loopi++) {
        printf("[Task %u]  ->  Entry Point: 0x%08X,  Stack Base: 0x%08X,  Stack Size: 0x%08X,  Initial SP: 0x%08X\n",
            loopi, (uintptr_t)TasksConst[loopi].EntryPoint, (uintptr_t)TasksConst[loopi].StackPtr, (uintptr_t)TasksConst[loopi].StackSize,
            (uintptr_t) (TasksConst[loopi].StackPtr + TasksConst[loopi].StackSize - 4)
        );
    }

    puts("[SystemInit]\n");
    SystemInit();

    puts("[StartOS]\n");
    StartOS(AppMode1);
}

/** \brief Initial task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(InitTask) {
    puts("[InitTask]\n");

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
    puts("[PeriodicTask]\n");

    TerminateTask();
}

/** \brief My task
 *
 * This task is started automatically in the application mode 1.
 */
TASK(MyTask) {
    puts("[MyTask]\n");

    while (TRUE) {
        puts("[Low Prio Task]\n");
        //~ msleep(100);
        Schedule();
    }

    TerminateTask();
}


const char * getServiceName(unsigned int service_id) {
    switch (service_id) {
        case OSServiceId_ActivateTask:
            return "ActivateTask";
        case OSServiceId_TerminateTask:
            return "TerminateTask";
        case OSServiceId_ChainTask:
            return "ChainTask";
        case OSServiceId_Schedule:
            return "Schedule";
        case OSServiceId_GetTaskID:
            return "GetTaskID";
        case OSServiceId_GetTaskState:
            return "GetTaskState";
        case OSServiceId_DisableAllInterrupts:
            return "DisableAllInterrupts";
        case OSServiceId_EnableAllInterrupts:
            return "EnableAllInterrupts";
        case OSServiceId_SuspendAllInterrupts:
            return "SuspendAllInterrupts";
        case OSServiceId_ResumeAllInterrupts:
            return "ResumeAllInterrupts";
        case OSServiceId_SuspendOSInterrupts:
            return "SuspendOSInterrupts";
        case OSServiceId_ResumeOSInterrupts:
            return "ResumeOSInterrupts";
        case OSServiceId_GetResource:
            return "GetResource";
        case OSServiceId_ReleaseResource:
            return "ReleaseResource";
        case OSServiceId_SetEvent:
            return "SetEvent";
        case OSServiceId_ClearEvent:
            return "ClearEvent";
        case OSServiceId_GetEvent:
            return "GetEvent";
        case OSServiceId_WaitEvent:
            return "WaitEvent";
        case OSServiceId_GetAlarmBase:
            return "GetAlarmBase";
        case OSServiceId_GetAlarm:
            return "GetAlarm";
        case OSServiceId_SetRelAlarm:
            return "SetRelAlarm";
        case OSServiceId_SetAbsAlarm:
            return "SetAbsAlarm";
        case OSServiceId_CancelAlarm:
            return "CancelAlarm";
        case OSServiceId_GetActiveApplicationMode:
            return "GetActiveApplicationMode";
        case OSServiceId_StartOS:
            return "StartOS";
        case OSServiceId_ShutdownOS:
            return "ShutdownOS";
        case OSServiceId_StackOverflow:
            return "StackOverflow";
        default:
            return "Unknown";
    }
}

void ErrorHook(void) {
    printf("[ErrorHook] Service: %ld (%s), P1: %ld, P2: %ld, P3: %ld, Ret: %ld\n",
        (long)OSErrorGetServiceId(),
        getServiceName(OSErrorGetServiceId()),
        (long)OSErrorGetParam1(),
        (long)OSErrorGetParam2(),
        (long)OSErrorGetParam3(),
        (long)OSErrorGetRet()
    );

    ShutdownOS(0);
}

void NMI_Handler(void) {
    puts("[NMI]\n");
    while (1) {
    }
}

void HardFault_Handler(void) {
    puts("[HardFault]\n");
    while (1) {
    }
}

void SVC_Handler(void) {
    puts("[SVC]\n");
    while (1) {
    }
}

void DebugMon_Handler(void) {
    puts("[DebugMon]\n");
    while (1) {
    }
}
