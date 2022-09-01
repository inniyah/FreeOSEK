// LPC1768: SysTick Timer
// See: https://www.exploreembedded.com/wiki/LPC1768:_SysTick_Timer

#define SYSTICK_CTRL_REG   0xE000E010 // System Timer Control and status register
#define SYSTICK_RELOAD_REG 0xE000E014 // System Timer Reload value register
#define SYSTICK_CURR_REG   0xE000E018 // System Timer Current value register
#define SYSTICK_CALIB_REG  0xE000E01C // System Timer Calibration value register

#define SYSTICK_ENABLE     (1u << 0)  // This bit is used to enable/disable the systick counter. 0-Disable the systick timer. 1-Enables the systick timer.
#define SYSTICK_TICKINT    (1u << 1)  // This bit is used to enable/disable the systick timer interrupt. When enabled the SysTick_Handler ISR will be called. 0-Disable the systick timer Interrupt. 1-Enables the systick timer Interrupt.
#define SYSTICK_CLKSOURCE  (1u << 2)  // This bit is used to select clock source for System Tick timer. 0-The external clock pin (STCLK) is selected. 1-CPU clock is selected.
#define SYSTICK_COUNTFLAG  (1u << 16) // System Tick counter flag. This flag is set when the System Tick counter counts down to 0, and is cleared by reading this register.

void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );

#define SYSTICK_SETUP() { \
    PUT32(SYSTICK_CTRL_REG,   0x00000004); \
    PUT32(SYSTICK_RELOAD_REG, 32 * 1000);  /* Set the Reload value (1ms) for required tick in STRELOAD. */ \
    PUT32(SYSTICK_CTRL_REG,   0x00000007); /* Enabled Systick Module, Select the CPU Clock Source and enable the SysTick interrupt */ \
}

#define SYSTICK_CLEAN_IRQ() { GET32(SYSTICK_CTRL_REG); }
