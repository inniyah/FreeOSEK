/* Copyright 2015, Pablo Ridolfi
 * All rights reserved.
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

/** \brief Start the system counter
 **
 ** This file includes the function to start the system counter
 **
 ** \file cortexM0/StartOs_Arch_SysTick.c
 ** \arch cortexM0
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*==================[inclusions]=============================================*/



#include "Os_Internal_Arch_Cpu.h"
#include "ciaaPlatforms.h"


#if (CPUTYPE_LPC43XX == CPUTYPE)
#include "chip.h"
#endif

#if (CPUTYPE_THUMB == CPUTYPE && CPU_QEMU == CPU)
#include "systick.h"
#endif



/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/

void StartOs_Arch_SysTick(void) {

#if (CPUTYPE_LPC43XX == CPUTYPE && CPU_LPC4337 == CPU)

	/* Enable and Set priority for PendSV irq */
	NVIC_EnableIRQ(PendSV_IRQn); /*TODO Check if this is necessary*/
	NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

	/* Activate Repetitive Interrupt Timer (RIT) for periodic IRQs */
	Chip_RIT_Init(LPC_RITIMER);
	Chip_RIT_SetTimerInterval(LPC_RITIMER, 1); /* 1ms Period */
	Chip_RIT_Enable(LPC_RITIMER);

	/* Enable and set priority for RIT irq */
	NVIC_EnableIRQ(RITIMER_IRQn);
	NVIC_SetPriority(RITIMER_IRQn, (1<<__NVIC_PRIO_BITS) - 1);

#elif (CPUTYPE_KEA64 == CPUTYPE && CPU_SKEAZN642 == CPU)

	/* Enable and Set priority for PendSV irq */
	NVIC_EnableIRQ(PendSV_IRQn); /*TODO Check if this is necessary*/
	NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

	/* Activate Systick timer for periodic IRQs */
	SysTick->CTRL  = 0;
	SysTick->LOAD  = (32*1000); // 1ms
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */
	SysTick->VAL   = 0UL;                          /* Load the SysTick Counter Value */
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk;

	/* Enable and set priority for Systick irq */
	NVIC_EnableIRQ(SysTick_IRQn);
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Systick Interrupt */

#elif (CPUTYPE_THUMB == CPUTYPE && CPU_QEMU == CPU)

    SYSTICK_SETUP();

#endif

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
