/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
 * Copyright 2015, Alejandro Permingeat
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

/** \brief FreeOSEK Os Generated Internal Achitecture Configuration Implementation File
 **
 ** \file cortexM4/Os_Internal_Arch_Cfg.c
 ** \arch cortexM4
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */



/*==================[inclusions]=============================================*/



#include "Os_Internal.h"
#if (CPUTYPE == lpc43xx)
/* THIS IS A DIRTY WORKAROUND :( ciaa/Firmware#309*/
#undef FALSE
#undef TRUE
#include "chip.h"
#endif

#if (CPUTYPE == lpc5410x)
#undef INLINE
#include "chip.h"
#endif




/*==================[macros and definitions]=================================*/



#if (CPU == lpc54102)

#define WEAK __attribute__ ((weak))

#endif



/*==================[internal data declaration]==============================*/



/*==================[internal functions declaration]=========================*/



/*==================[internal data definition]===============================*/



/*==================[external data definition]===============================*/



#if (CPU == mk60fx512vlq15)

   /* Reset_Handler is defined in startup_MK60F15.S_CPP */
   void Reset_Handler( void );

   extern uint32_t __StackTop;

#elif (CPU == lpc4337)

   /* ResetISR is defined in cr_startup_lpc43xx.c */
   extern void ResetISR(void);

   /** \brief External declaration for the pointer to the stack top from the Linker Script */
   extern void _vStackTop(void);

#elif (CPU == lpc54102)

   /* Valid User Code Checksum, calculated on the linker script. */
   WEAK extern void __valid_user_code_checksum();

   /* ResetISR is defined in cr_startup_lpc5410x.c */
   extern void ResetISR(void);

   /** \brief External declaration for the pointer to the stack top from the Linker Script */
   extern void _vStackTop(void);

#else

#error Not supported CPU

#endif

/** \brief Handlers used by OSEK */
extern void SysTick_Handler(void);
extern void PendSV_Handler(void);



/*==================[internal functions definition]==========================*/



/* Default exception handlers. */
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void SVC_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void) {
    while (1) {
    }
}



/*==================[external functions definition]==========================*/



<?php
$this->loadHelper("gen/ginc/Multicore.php");

switch ($this->definitions["CPU"])
{
   case "mk60fx512vlq15":
      /* Interrupt sources for MK60F12.
       * See externals/drivers/cortexM4/k60_120/inc/device/MK60F12/MK60F12.h.
       */
      $intList = array (
         0 => "DMA0_DMA16",
         1 => "DMA1_DMA17",
         2 => "DMA2_DMA18",
         3 => "DMA3_DMA19",
         4 => "DMA4_DMA20",
         5 => "DMA5_DMA21",
         6 => "DMA6_DMA22",
         7 => "DMA7_DMA23",
         8 => "DMA8_DMA24",
         9 => "DMA9_DMA25",
         10 => "DMA10_DMA26",
         11 => "DMA11_DMA27",
         12 => "DMA12_DMA28",
         13 => "DMA13_DMA29",
         14 => "DMA14_DMA30",
         15 => "DMA15_DMA31",
         16 => "DMA_ERR",
         17 => "MCM",
         18 => "FTFE",
         19 => "Read_Collision",
         20 => "LVD_LVW",
         21 => "LLW",
         22 => "WDG",
         23 => "RNG",
         24 => "I2C0",
         25 => "I2C1",
         26 => "SPI0",
         27 => "SPI1",
         28 => "SPI2",
         29 => "CAN0_READ",
         30 => "CAN0_BOFF",
         31 => "CAN0_ERR",
         32 => "CAN0_TXW",
         33 => "CAN0_RXW",
         34 => "CAN0_WAKEUP",
         35 => "I2S0_TX",
         36 => "I2S0_RR",
         37 => "CAN1_READ",
         38 => "CAN1_BOFF",
         39 => "CAN1_EERROR",
         40 => "CAN1_TXW",
         41 => "CAN1_RXW",
         42 => "CAN1_WAKEUP",
         43 => "RES59",
         44 => "UART0_LON",
         45 => "UART0",
         46 => "UART0_ERR",
         47 => "UART1",
         48 => "UART1_ERR",
         49 => "UART2",
         50 => "UART2_ERR",
         51 => "UART3",
         52 => "UART3_ERR",
         53 => "UART4",
         54 => "UART4_ERR",
         55 => "UART5",
         56 => "UART5_ERR",
         57 => "ADC0",
         58 => "ADC1",
         59 => "CMP0",
         60 => "CMP1",
         61 => "CMP2",
         62 => "FTM0",
         63 => "FTM1",
         64 => "FTM2",
         65 => "CMT",
         66 => "RTC",
         67 => "RTC_SEC",
         68 => "PIT0",
         69 => "PIT1",
         70 => "PIT2",
         71 => "PIT3",
         72 => "PDB0",
         73 => "USB0",
         74 => "USBDCD",
         75 => "ENET_1588_Timer",
         76 => "ENET_TX",
         77 => "ENET_RX",
         78 => "ENET_ERR",
         79 => "RES95",
         80 => "SDHC",
         81 => "DAC0",
         82 => "DAC1",
         83 => "TSI0",
         84 => "MCG",
         85 => "LPTimer",
         86 => "RES102",
         87 => "PORTA",
         88 => "PORTB",
         89 => "PORTC",
         90 => "PORTD",
         91 => "PORTE",
         92 => "PORTF",
         93 => "RES109",
         94 => "SWI",
         95 => "NFC",
         96 => "USBHS",
         97 => "RES113",
         98 => "CMP3",
         99 => "RES115",
         100 => "RES116",
         101 => "FTM3",
         102 => "ADC2",
         103 => "ADC3",
         104 => "I2S1_TX",
         105 => "I2S1_RX",
      );
      break;

   case "lpc4337":
      /* Interrupt sources for LPC43xx.
       * See externals/drivers/cortexM4/lpc43xx/inc/cmsis_43xx.h.
       */
      $intList = array (
         0 => "DAC",
         1 => "M0APP",
         2 => "DMA",
         3 => "RES1",
         4 => "FLASH_EEPROM",
         5 => "ETH",
         6 => "SDIO",
         7 => "LCD",
         8 => "USB0",
         9 => "USB1",
         10 => "SCT",
         11 => "RIT",
         12 => "TIMER0",
         13 => "TIMER1",
         14 => "TIMER2",
         15 => "TIMER3",
         16 => "MCPWM",
         17 => "ADC0",
         18 => "I2C0",
         19 => "I2C1",
         20 => "SPI",
         21 => "ADC1",
         22 => "SSP0",
         23 => "SSP1",
         24 => "UART0",
         25 => "UART1",
         26 => "UART2",
         27 => "UART3",
         28 => "I2S0",
         29 => "I2S1",
         30 => "SPIFI",
         31 => "SGPIO",
         32 => "GPIO0",
         33 => "GPIO1",
         34 => "GPIO2",
         35 => "GPIO3",
         36 => "GPIO4",
         37 => "GPIO5",
         38 => "GPIO6",
         39 => "GPIO7",
         40 => "GINT0",
         41 => "GINT1",
         42 => "EVRT",
         43 => "CAN1",
         44 => "RES6",
         45 => "ADCHS",
         46 => "ATIMER",
         47 => "RTC",
         48 => "RES8",
         49 => "WDT",
         50 => "M0SUB",
         51 => "CAN0",
         52 => "QEI"
      );
      break;

case "lpc54102":
      /* Interrupt sources for LPC5410x.
       * See externals/drivers/cortexM4/lpc5410x/inc/cmsis_5410x.h.
       */
      $intList = array (
          0 => "WDT",            /*!< WWDT                                             */
          1 => "BOD",            /*!< BOD                                              */
          2 => "RESERVED2",      /*!< Reserved Interrupt                               */
          3 => "DMA",            /*!< DMA                                              */
          4 => "GINT0",          /*!< GINT0                                            */
          5 => "PIN_INT0",       /*!< PININT0                                          */
          6 => "PIN_INT1",       /*!< PININT1                                          */
          7 => "PIN_INT2",       /*!< PININT2                                          */
          8 => "PIN_INT3",       /*!< PININT3                                          */
          9 => "UTICK",          /*!< Micro-tick Timer interrupt                       */
         10 => "MRT",            /*!< Multi-rate timer interrupt                       */
         11 => "CT32B0",         /*!< CTMR0                                            */
         12 => "CT32B1",         /*!< CTMR1                                            */
         13 => "CT32B2",         /*!< CTMR2                                            */
         14 => "CT32B3",         /*!< CTMR3                                            */
         15 => "CT32B4",         /*!< CTMR4                                            */
         16 => "SCT0",           /*!< SCT                                              */
         17 => "UART0",          /*!< UART0                                            */
         18 => "UART1",          /*!< UART1                                            */
         19 => "UART2",          /*!< UART2                                            */
         20 => "UART3",          /*!< UART3                                            */
         21 => "I2C0",           /*!< I2C0                                             */
         22 => "I2C1",           /*!< I2C1                                             */
         23 => "I2C2",           /*!< I2C2                                             */
         24 => "SPI0",           /*!< SPI0                                             */
         25 => "SPI1",           /*!< SPI1                                             */
         26 => "ADC_SEQA",       /*!< ADC0 sequence A completion                       */
         27 => "ADC_SEQB",       /*!< ADC0 sequence B completion                       */
         28 => "ADC_THCMP",      /*!< ADC0 threshold compare and error                 */
         29 => "RTC",            /*!< RTC alarm and wake-up interrupts                 */
         30 => "RESERVED30",     /*!< Reserved Interrupt                               */
         31 => "MAILBOX",        /*!< Mailbox                                          */
         32 => "GINT1",          /*!< GINT1                                            */
         33 => "PIN_INT4",       /*!< External Interrupt 4                             */
         34 => "PIN_INT5",       /*!< External Interrupt 5                             */
         35 => "PIN_INT6",       /*!< External Interrupt 6                             */
         36 => "PIN_INT7",       /*!< External Interrupt 7                             */
         37 => "RESERVED37",     /*!< Reserved Interrupt                               */
         38 => "RESERVED38",     /*!< Reserved Interrupt                               */
         39 => "RESERVED39",     /*!< Reserved Interrupt                               */
         40 => "RIT",            /*!< Repetitive Interrupt Timer                       */
         41 => "RESERVED41",     /*!< Reserved Interrupt                               */
         42 => "RESERVED42",     /*!< Reserved Interrupt                               */
         43 => "RESERVED43",     /*!< Reserved Interrupt                               */
         44 => "RESERVED44",     /*!< Reserved Interrupt                               */
      );
      break;

   default:
     $this->log->error("the CPU " . $this->definitions["CPU"] . " is not supported.");
      break;
}

$MAX_INT_COUNT = max(array_keys($intList))+1;

if ($this->definitions["CPU"] == "mk60fx512vlq15") : ?>
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &__StackTop,                    /* The initial stack pointer  */
   Reset_Handler,                  /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   MemManage_Handler,              /* The MPU fault handler      */
   BusFault_Handler,               /* The bus fault handler      */
   UsageFault_Handler,             /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   DebugMon_Handler,               /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   SysTick_Handler,                /* The SysTick handler        */
<?php elseif ($this->definitions["CPU"] == "lpc4337") : ?>
/** \brief LPC4337 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &_vStackTop,                    /* The initial stack pointer  */
   ResetISR,                       /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   MemManage_Handler,              /* The MPU fault handler      */
   BusFault_Handler,               /* The bus fault handler      */
   UsageFault_Handler,             /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   DebugMon_Handler,               /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   SysTick_Handler,                /* The SysTick handler        */
<?php elseif ($this->definitions["CPU"] == "lpc54102") : ?>
/** \brief LPC54102 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &_vStackTop,                    /* The initial stack pointer             */
   ResetISR,                       /* The reset handler                     */
   NMI_Handler,                    /* The NMI handler                       */
   HardFault_Handler,              /* The hard fault handler                */
   MemManage_Handler,              /* The MPU fault handler                 */
   BusFault_Handler,               /* The bus fault handler                 */
   UsageFault_Handler,             /* The usage fault handler               */
   __valid_user_code_checksum,     /* Reserved - Valid User Code Checksum   */
   0,                              /* Reserved                              */
   0,                              /* Reserved                              */
   0,                              /* Reserved                              */
   SVC_Handler,                    /* SVCall handler                        */
   DebugMon_Handler,               /* Debug monitor handler                 */
   0,                              /* Reserved                              */
   PendSV_Handler,                 /* The PendSV handler                    */
   SysTick_Handler,                /* The SysTick handler                   */
<?php else :
     $this->log->error("Not supported CPU: " . $this->definitions["CPU"]);
   endif;
?>
   /*** User Interruptions ***/
<?php

/* get ISRs defined by user application */
$intnames = $this->helper->multicore->getLocalList("/OSEK", "ISR");

for($i=0; $i < $MAX_INT_COUNT; $i++)
{
   $src_found = 0;
   foreach ($intnames as $int)
   {
      $intcat = $this->config->getValue("/OSEK/" . $int,"CATEGORY");
      $source = $this->config->getValue("/OSEK/" . $int,"INTERRUPT");

      if($intList[$i] == $source)
      {
         if ($intcat == 2)
         {
            print "   OSEK_ISR2_$int, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." ISR for " . $intList[$i] . " (IRQ $i) Category 2 */\n";
            $src_found = 1;
         } elseif ($intcat == 1)
         {
            print "   OSEK_ISR_$int, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." ISR for " . $intList[$i] . " (IRQ $i) Category 1 */\n";
            $src_found = 1;
         } else
         {
           $this->log->error("Interrupt $int type $inttype has an invalid category $intcat");
         }
      }
   }
   if($src_found == 0)
   {
      print "   OSEK_ISR_NoHandler, /* 0x".dechex($i+16)." 0x".str_pad(strtoupper(dechex(($i+16)*4)), 8, "0", STR_PAD_LEFT)." - No Handler set for ISR " . $intList[$i] . " (IRQ $i) */\n";
   }
}
?>
};


/** \brief Interrupt enabling and priority setting function */
void Enable_User_ISRs(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $this->helper->multicore->getLocalList("/OSEK", "ISR");
foreach ($intnames as $int)
{

   $source = $this->config->getValue("/OSEK/" . $int,"INTERRUPT");
   $prio = $this->config->getValue("/OSEK/" . $int,"PRIORITY");

   print "   /* Enabling IRQ $source with priority $prio */\n";
   print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   print "   NVIC_SetPriority(" . array_search($source, $intList) . ", $prio);\n\n";
   
}
?>
}

/** \brief Enable user defined category 2 ISRs */
void Enable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $this->helper->multicore->getLocalList("/OSEK", "ISR");
foreach ($intnames as $int)
{
   $source = $this->config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $this->config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Enabling IRQ $source */\n";
      print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}

/** \brief Disable user defined category 2 ISRs */
void Disable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $this->helper->multicore->getLocalList("/OSEK", "ISR");
foreach ($intnames as $int)
{
   $source = $this->config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $this->config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Disabling IRQ $source */\n";
      print "   NVIC_DisableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}



/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

