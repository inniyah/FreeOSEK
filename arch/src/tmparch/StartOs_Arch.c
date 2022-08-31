/* Copyright 2008, 2009 Mariano Cerdeiro
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
#error this is a remember to remove the comment on the following line

/*****************************************************************************
 * update the tmparch directory on the \file doxygen comment with your
 * architecture
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/
/** \brief FreeOSEK StartOs Architecture Dependece Implementation File
 **
 ** This file implements the StartOs Arch API
 **
 ** \file tmparch/StartOs_Arch.c
 ** \arch tmparch
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * add your name to the developers and create for you a nick with
 * 3 or 4 letters. Please do not use any given nick.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * add a new version to this file, add the date, your initials and the main
 * changes, only main changes shall be listed here. A detailed message log
 * is saved in svn log and on the tracker system since every svn login message
 * shalle indicate the related tracker id.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * add any needed include, please take into account that normaly NO INCLUDE
 * shall be included here other than Osek_Internal.h, but in case you can do
 * it, but discuss the reason with the project manager.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[macros and definitions]=================================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please try to keep empty this part, define all needed macros
 * in Osek_Internal_Arch.h
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[internal data declaration]==============================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please declare here all needed variables which are only used
 * in this file.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[internal functions declaration]=========================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please declare here all needed functions which are only used
 * in this file.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[internal data definition]===============================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please define here all needed variables which are only used
 * in this file.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external data definition]===============================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please declare here all needed variables which are
 * exported. Please define these variables in Osek_Internal_Arch.h
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[internal functions definition]==========================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please define here all needed functions which are only used
 * in this file.
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/

/*==================[external functions definition]==========================*/
#error this is a remember to remove the comment on the following line
/*****************************************************************************
 * Please declare here all needed functions which are
 * exported. Please define these functions in Osek_Internal_Arch.h
 *
 * PLEASE REMOVE THIS COMMENT
 *****************************************************************************/
/** \brief Architecture Dependnece Start Os function
 **
 ** This function is defined in Osek_Internal.h and has to be defined for
 ** every architecture. This function shall set for all tasks:
 ** - init the stack for all tasks.
 ** - init the entry point of all stack
 ** - init all other necessary registers to the init value for the first
 **   time that the task will be executed.
 ** - if necessary to call StartOs_Arch_Cpu
 **
 ** Needed variables for this function will be:
 ** - TasksConst[].TaskContext
 ** - TasksConst[].StackPtr
 ** - TasksConst[].StackSize
 ** - TasksConst[].EntryPoint
 **
 ** Needed macros for this function will be:
 ** - TASKS_COUNT
 **
 **/
void StartOs_Arch(void)
{
   uint8f loopi;

   /* init every task */
   for( loopi = 0; loopi < TASKS_COUNT; loopi++)
   {
      /* init stack */
#error update here and remove this comment

      /* init entry point */
#error update here and remove this comment

      /* init registers */
#error update here and remove this comment
   }

   /* call CPU dependent initialisation */
#error update here and remove this comment

}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
