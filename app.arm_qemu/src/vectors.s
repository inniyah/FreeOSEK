.cpu cortex-m0
.thumb

.thumb_func
.global _start
_start:
stacktop: .word 0x20001000
.word   ResetISR        /* 0x04 1 Reset */
.word   hang            /* 0x08 2 NMI */
.word   hang            /* 0x0C 3 HardFault */
.word   hang            /* 0x10 4 MemManage */
.word   hang            /* 0x14 5 BusFault */
.word   hang            /* 0x18 6 UsageFault */
.word   hang            /* 0x1C 7 RESERVED */
.word   hang            /* 0x20 8 RESERVED */
.word   hang            /* 0x24 9 RESERVED*/
.word   hang            /* 0x28 10 RESERVED */
.word   hang            /* 0x2C 11 SVCall */
.word   hang            /* 0x30 12 Debug Monitor */
.word   hang            /* 0x34 13 RESERVED */
.word   hang            /* 0x38 14 PendSV */
.word   SysTick_Handler /* 0x3C 15 SysTick */
