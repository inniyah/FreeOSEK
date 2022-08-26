/* Copyright 2008, 2009, 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Juan Cecconi
 * Copyright 2014, ACSE & CADIEEL
 *      ACSE: http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *      CADIEEL: http://www.cadieel.org.ar
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _OS_INTERNAL_ARCH_H_
#define _OS_INTERNAL_ARCH_H_
/** \brief FreeOSEK Os Internal Architecture Dependent Header File
 **
 ** \file x86/Os_Internal_Arch.h
 ** \arch x86
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/
#include "stdio.h"      /* used to print debug information */
#include "stdbool.h"    /* needed for bool type */
#include "signal.h"     /* used to simulate interrupts */
#include "unistd.h"     /* used to create a fork to poll the interrupts */
#include "stdlib.h"     /* used to call exit to terminate the process */
#include "time.h"       /* used to simulate the hardware timer */
#include "string.h"     /* used to call the function strerror */
#include "pthread.h"    /* needed for pthread_t */
#include "ucontext.h"   /* setcontext, getcontext, makecontext, and swapcontext */

/*==================[macros]=================================================*/
/** \brief Extra size reserved for each stack
 **
 ** This macro shall be set to the amount of extra stack needed for each task
 ** in the simulation of the rtos in systems like windows/linux. In real
 ** embedded hw this macro shall be set to 0.
 **
 ** TASK_STAC_ADDITIONAL_STACK bytes of extra stack are reserver for each task
 ** running on the system.
 **/
#define TASK_STACK_ADDITIONAL_SIZE      10000

/*==================[cputype macros]=========================================*/

/** \brief Interrupt Secure Start Macro
 **
 ** This macro shall be used to disable the interrupts
 **/
#define IntSecure_Start() SuspendAllInterrupts()

/** \brief Interrupt Secure End Macro
 **
 ** This macro shall be used to restore the interrupts
 **/
#define IntSecure_End() ResumeAllInterrupts()

/** \brief osekpause
 **
 **/
#define osekpause() { \
   PreCallService(); \
   (void)usleep(1); \
   PostCallService(); \
}

/** \brief Jmp to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define JmpTask(task) { \
    printf("[JmpTask(%d)]\n", task); \
    setcontext(TasksConst[task].TaskContext); \
}

/** \brief Call to an other Task
 **
 ** This function jmps to the indicated task.
 **/
#define CallTask(OldTask, NewTask) { \
    printf("[CallTask(old=%d, new=%d)]\n", OldTask, NewTask); \
    swapcontext(TasksConst[OldTask].TaskContext, TasksConst[NewTask].TaskContext); \
}

/** \brief Save context */
#define SaveContext(task) { \
    printf("[SaveContext(%d)]\n", task); \
    getcontext(TasksConst[task].TaskContext); \
}

/** \brief Set the entry point for a task */
#define SetEntryPoint(task) { \
    printf("[SetEntryPoint(%d)] -> [%p]\n", task, TasksConst[(task)].EntryPoint); \
    makecontext(TasksConst[task].TaskContext, TasksConst[(task)].EntryPoint, 0); \
}

#define ISR_NMI      0
#define ISR_CTR      1
#define ISR_CANRX    2
#define ISR_CANTX    3

#define EnableOSInterrupts() { \
   InterruptMask &= (InterruptFlagsType)~(OSEK_OS_INTERRUPT_MASK); \
}

#define EnableInterrupts() { \
   InterruptState = 1; \
}

#define DisableOSInterrupts() { \
   InterruptMask |= (InterruptFlagsType)(OSEK_OS_INTERRUPT_MASK); \
}

#define DisableInterrupts() { \
   InterruptState = 0; \
}

/** \brief Get Counter Actual Value
 **
 ** This macro returns the actual value of the counter
 **
 ** \param[in] CounterID id of the counter to be readed
 ** \return Actual value of the counter
 **/
#define GetCounter_Arch(CounterID) (CountersVar[CounterID].Time)

/** \brief Pre ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is started
 **/
#define PreIsr2_Arch(isr)

/** \brief Post ISR Macro
 **
 ** This macro is called every time that an ISR Cat 2 is finished
 **/
#define PostIsr2_Arch(isr) \
   Schedule_WOChecks();

/** \brief Pre Call Service
 **
 ** This macro shall be called before calling any Os system service
 **/
#define PreCallService() { \
    /*printf("[PreCallService]\n");*/ \
    /* save osek stack and get os stack */ \
    if (sigaltstack(&OsStack, &OsekStack) < 0) { perror("sigaltstack"); } \
}

/** \brief Post Call Service
 **
 ** This macro shall be called after calling any Os system service
 **/
#define PostCallService() { \
    /*printf("[PostCallService]\n");*/ \
    /* save actual Os stack and get osek stack */ \
    if (sigaltstack(&OsekStack, &OsStack) < 0) { perror("sigaltstack"); } \
}

/** \brief ShutdownOs Arch service
 **/
#define ShutdownOs_Arch() { \
   PreCallService(); \
   PostCallService(); \
}

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/
/** \brief Interrupt Falg
 **
 ** This variable indicate the state of the Os interrupts. If bit 0 is set
 ** interrupt 0 has been activated, if bit 1 is set interrupt 1 has been
 ** activated, and so on.
 **/
extern InterruptFlagsType InterruptFlag;

/** \brief Osek Hardware Timer 0
 **/
extern uint32 OsekHWTimer0;

/** \brief Interrupt flags
 **
 ** This variable is used to simulate HW interrupts in x86. Each bit represents
 ** an interrupt:
 **   byte 0 bit 0 -> interrupt 0
 **   byte 0 bit 1 -> interrupt 1
 **   ...
 **   byte 0 bit 31 -> interrupt 31
 **   ...
 **   byte 1 bit 0 -> interrupt 32
 **   ..
 **   byte 1 bit 31 -> interrupt 63
 **
 ** Up to 64 (0..63) interruptions are supported in x86.
 **/
extern uint32* OSEK_InterruptFlags;

extern bool Os_Terminate_Flag;

extern pthread_t Os_Thread_Timer;

/** \brief Os Stack
 **
 ** This variable is used to save the Os stack used to call the system
 ** (linux) services from FreeOSEK
 **/
extern stack_t OsStack;

/** \brief Osek Stack
 **
 ** This variable is used to save the Osek stack while calling a Os
 ** service
 **/
extern stack_t OsekStack;

/*==================[external functions declaration]=========================*/
/** \brief Os Interrupt Handler
 **
 ** This function is called every time when a interrupt message is received.
 **/
extern void OsInterruptHandler(int status);

extern void* HWTimerThread(void *pThread_Arg);

extern void OsekKillSigHandler(int status);

extern void OSEK_ISR_HWTimer0(void);

extern void OSEK_ISR_HWTimer1(void);

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef _OS_INTERNAL_ARCH_H_ */

