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


#if (CPU == lpc4337)
#include "chip.h"
#endif



/*==================[macros and definitions]=================================*/



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/



/*==================[internal functions definition]==========================*/



/*==================[external functions definition]==========================*/


#if (CPU_LPC4337 == CPU)

void StartOs_Arch_SysTick(void)
{
   /* Set lowest priority for PendSV */
   NVIC_SetPriority(PendSV_IRQn, (1 << __NVIC_PRIO_BITS) - 1);

   /* Activate Repetitive Interrupt Timer (RIT) for periodic IRQs */
   Chip_RIT_Init(LPC_RITIMER);
   Chip_RIT_SetTimerInterval(LPC_RITIMER, 1); /* 1ms Period */
   Chip_RIT_Enable(LPC_RITIMER);

   /* Enable IRQ for RIT */
   NVIC_EnableIRQ(RITIMER_IRQn);

   /* Set lowest priority for RIT */
   NVIC_SetPriority(RITIMER_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}

#endif /* CPU_LPC4337 == CPU */

#if (CPU_THUMB == CPU)

#include "systick.h"

void StartOs_Arch_SysTick(void)
{
    //~ PUT32(SYSTICK_CTRL_REG,   0x00000004);
    //~ PUT32(SYSTICK_RELOAD_REG, 1000 - 1);   // Set the Reload value for required tick in STRELOAD.
    //~ PUT32(SYSTICK_CTRL_REG,   0x00000007); // Enabled Systick Module, Select the CPU Clock Source and enable the SysTick interrupt
}

#endif /* CPU_THUMB == CPU */


/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
