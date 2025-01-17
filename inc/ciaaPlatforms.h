/* Copyright 2014, ACSE & CADIEEL
 *    ACSE   : http://www.sase.com.ar/asociacion-civil-sistemas-embebidos/ciaa/
 *    CADIEEL: http://www.cadieel.org.ar
 * Copyright 2014, 2015 Mariano Cerdeiro
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

#ifndef CIAAPLATFORMS_H
#define CIAAPLATFORMS_H
/** \brief Platform file
 **
 ** Platform header file
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */
/** \addtogroup Platform
 ** @{ */



/*==================[inclusions]=============================================*/



/*==================[cplusplus]==============================================*/



#ifdef __cplusplus
extern "C" {
#endif



/*==================[macros]=================================================*/



/** \brief check for ARCH/CPUTYPE and CPU */
#ifndef ARCH
#error ARCH is not defined, this define shall be included in the compile command
#endif

#ifndef CPUTYPE
#error CPUTYPE is not defined, this define shall be included in the compile command
#endif

#ifndef CPU
#error CPU is not defined, this define shall be included in the compile command
#endif

#define ARCH_LINUX      0xA000000
#define ARCH_POWERPC    0xA000001
#define ARCH_CORTEXM0   0xA000002
#define ARCH_CORTEXM4   0xA000003
#define ARCH_X86        0xA000004
#define ARCH_MIPS       0xA000005
#define ARCH_SPARCV8    0xA000006

#define CPUTYPE_NONE    0xB000000
#define CPUTYPE_LPC43XX 0xB000001
#define CPUTYPE_POSIX   0xB000002
#define CPUTYPE_SPC5XX  0xB000003
#define CPUTYPE_KEA64   0xB000004
#define CPUTYPE_THUMB   0xB000005
#define CPUTYPE_IA32    0xB000006
#define CPUTYPE_IA64    0xB000007
#define CPUTYPE_PIC32   0xB000008

#define CPU_NONE        0xC000000
#define CPU_QEMU        0xC000001
#define CPU_LPC4337     0xC000002
#define CPU_SPC560D     0xC000003
#define CPU_SKEAZN642   0xC000004


/****** ARCH macro definitions ******/
/** \brief ARCH x86 */
#define x86                   1
/** \brief ARCH cortexM4 */
#define cortexM4              2
/** \brief ARCH mips */
#define mips                  3
/** \brief ARCH cortexM0 */
#define cortexM0              4
/** \brief ARCH sparcV8 */
#define sparcV8               5



/****** CPUTYPE macro definitions ******/
/*** CPUTYPES for ARCH=x86 ***/
/** \brief CPUTTYPE ia32 */
#define ia32                  1

/** \brief CPUTTYPE ia64 */
#define ia64                  2

/*** CPUTYPES for ARCH=cortexM0 ***/
#define kea64                 3

/*** CPUTYPES for ARCH=cortexM4 and ARCH=cortexM0 ***/
#define lpc43xx               4
#define lpc5410x              5

/*** CPUTYPES for ARCH=cortexM4 ***/
#define k60_120               6

/*** CPUTYPES for ARCH=mips ***/
#define pic32                 7

/*** CPUTYPES for ARCH=sparcV8 ***/
#define leon3                 8



/****** CPU macro definitions ******/
/*** CPU for ARCH=x86 CPUTYPE=ia32 ***/

/*** CPU for ARCH=x86 CPUTYPE=ia64 ***/

/*** CPU for ARCH=cortexM0 and CPUTYPE=kea64 ***/
#define skeazn642             1

/*** CPU for ARCH=cortexM4 or ARCH=cortexM0 and CPUTYPE=lpc43xx ***/
#define lpc4337               2

/*** CPU for ARCH=cortexM4 CPUTYPE=k60_120 ***/
#define mk60fx512vlq15        3

/*** CPU for ARCH=mips CPUTYPE=pic32 ***/
#define pic32mz               4

/*** CPU for ARCH=cortexM4 or ARCH=cortexM0 and CPUTYPE=lpc5410x ***/
#define lpc54102              5

/*** CPU for ARCH=sparcV8 CPUTYPE=leon3 ***/
#define leon3nfp              6



/****** BOARDS macro definitions ******/
/*** BOARD for ARCH=x86 CPUTYPE=ia32 ***/
#define ciaa_sim_ia32         1

/*** BOARD for ARCH=x86 CPUTYPE=ia64 ***/
#define ciaa_sim_ia64         2

/*** BOARD for ARCH=cortexM4 CPUTYPE=lpc43xx ***/
#define ciaa_nxp              3

/*** BOARD for ARCH=cortexM4 CPUTYPE=lpc43xx ***/
#define edu_ciaa_nxp          4

/*** CPU for ARCH=cortexM4 CPUTYPE=k60_120 ***/
#define ciaa_fsl              5

/*** BOARD for ARCH=mips CPUTYPE=pic32 ***/
#define ciaa_pic              6

/*** BOARD for ARCH=cortexM4 CPUTYPE=lpc5410x ***/
#define pico_ciaa             7

/*** BOARD for ARCH=sparcV8 CPUTYPE=leon3nfp ***/
#define ciaa_leon3_fpga_nfp   8



/****** CIAAPLATFORM_REGLENGTH ******/
/** \brief definition of the length of the register */
#if (ARCH == x86)
#if (CPUTYPE == ia32)
#define CIAAPLATFORM_REGLENGTH      32
#elif (CPUTYPE == ia64)
#define CIAAPLATFORM_REGLENGTH      64
#endif
#endif



/****** CIAAPLATFORM_ENDIANESS ******/
#define CIAAPLATFORM_BIGENDIAN      0
#define CIAAPLATFORM_LITTLEENDIAN   1
#if (ARCH == posix)
#define CIAAPLATFORM_ENDIANESS CIAAPLATFORM_LITTLEENDIAN
#endif

#if ( (ARCH == cortexM4) && (CPUTPYE == lpc43xx) )

#endif

#if   ( ( ARCH == ARCH_X86 )      && ( ( CPUTYPE == CPUTYPE_IA32 ) || ( CPUTYPE == CPUTYPE_IA64 ) ) )
#elif ( ( ARCH == ARCH_CORTEXM4 ) && ( CPUTYPE == CPUTYPE_LPC43XX ) && ( CPU == CPU_LPC4337 ) )
#elif ( ( ARCH == ARCH_CORTEXM0 ) && ( CPUTYPE == CPUTYPE_LPC43XX ) && ( CPU == CPU_LPC4337 ) )
#elif ( ( ARCH == ARCH_CORTEXM4 ) && ( CPUTYPE == k60_120 )         && ( CPU == mk60fx512vlq15 ) )
#elif ( ( ARCH == ARCH_MIPS )     && ( CPUTYPE == CPUTYPE_PIC32 )   && ( CPU == pic32mz ) )
#elif ( ( ARCH == ARCH_CORTEXM4 ) && ( CPUTYPE == lpc5410x )        && ( CPU == lpc54102 ) )
#elif ( ( ARCH == ARCH_SPARCV8 )  && ( CPUTYPE == leon3 )           && ( CPU == leon3nfp ) )
#elif ( ( ARCH == ARCH_CORTEXM0 ) && ( CPUTYPE == CPUTYPE_THUMB )   && ( CPU == CPU_QEMU ) )
#elif ( ( ARCH == ARCH_CORTEXM0 ) && ( CPUTYPE == CPUTYPE_KEA64 )   && ( CPU == CPU_SKEAZN642 ) )
#elif ( ( ARCH == ARCH_LINUX )    && ( CPUTYPE == CPUTYPE_POSIX )   && ( CPU == CPU_NONE ) )
#else
#error the entered architecture is not supported... :(
#endif



/*==================[typedef]================================================*/



/*==================[external data declaration]==============================*/



/*==================[external functions declaration]=========================*/



/*==================[cplusplus]==============================================*/



#ifdef __cplusplus
}
#endif



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
#endif /* #ifndef CIAAPLATFORMS_H */
