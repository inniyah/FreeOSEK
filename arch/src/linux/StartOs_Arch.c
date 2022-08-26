/* Copyright 2008, 2009, 2014 Mariano Cerdeiro
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

/** \brief FreeOSEK Os StartOs Architecture Dependece Implementation File
 **
 ** This file implements the StartOs Arch API
 **
 ** \file x86/StartOs_Arch.c
 ** \arch x86
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

/*==================[macros and definitions]=================================*/
/* Mac OS X only suport deprecated macro version MAP_ANON  */
#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS MAP_ANON
#endif

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
bool Os_Terminate_Flag;

pthread_t Os_Thread_Timer;

/*==================[internal functions definition]==========================*/

// https://stackoverflow.com/questions/34989829/linux-signal-handling-how-to-get-address-of-interrupted-instruction

/*==================[external functions definition]==========================*/
void StartOs_Arch(void) {
   uint8f loopi;

   printf("[StartOs_Arch]\n");

   /* init every task */
   for (loopi = 0; loopi < TASKS_COUNT; loopi++) {
        /* init context */
        getcontext(TasksConst[loopi].TaskContext);
        /* init stack */
        TasksConst[loopi].TaskContext->uc_stack.ss_sp = TasksConst[loopi].StackPtr;
        TasksConst[loopi].TaskContext->uc_stack.ss_size = TasksConst[loopi].StackSize;
        //~ TasksConst[loopi].TaskContext->uc_stack.ss_sp = malloc(4096);
        //~ TasksConst[loopi].TaskContext->uc_stack.ss_size = 4096;
        TasksConst[loopi].TaskContext->uc_stack.ss_flags = 0;
        //~ /* empty signals */
        sigemptyset(&TasksConst[loopi].TaskContext->uc_sigmask);
        /* set entry point */
        makecontext(TasksConst[loopi].TaskContext, TasksConst[loopi].EntryPoint, 0);
        //~ setcontext(TasksConst[loopi].TaskContext);
   }

   /* initialize singals handler */
   signal(SIGALRM, OsInterruptHandler);
   signal(SIGUSR1, OsInterruptHandler);
   signal(SIGTERM, OsInterruptHandler);

   /* shared memory for interrupts */
   OSEK_InterruptFlags = mmap(NULL,
         sizeof(8),
         PROT_READ | PROT_WRITE,
         MAP_SHARED | MAP_ANONYMOUS, -1, 0);

   /* init Thread Terminate flag */
   Os_Terminate_Flag = false;

    if (0 != pthread_create(&Os_Thread_Timer, NULL, HWTimerThread, (void*)0)) {
        printf("Error creating OS Thread timer!\n");
        exit(-1);
    }

#if 0
    printf("Process ID: %d\n", getpid());
#endif

    /* All these is done in a similar way in StartOS.c, Is it code to be deleted? */
#if 0
    /* enable interrupts */
    InterruptState = 1;

    /* enable HWTimer0,  interrupt 4 */
    InterruptMask = ~(1 << 4);

#if (defined HWCOUNTER1)
    /* enable HWTimer0,  interrupt 5 */
    InterruptMask &= ~(1 << 5);
#endif

#endif

    OsStack.ss_sp = NULL;
    OsStack.ss_size = 0;
    OsStack.ss_flags = 0;

    OsStack.ss_sp = NULL;
    OsekStack.ss_size = 0;
    OsekStack.ss_flags = 0;

    if (sigaltstack(NULL, &OsStack) < 0) { perror("sigaltstack"); }
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

