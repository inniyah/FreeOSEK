unsigned long __stack_chk_guard;

void __stack_chk_guard_setup(void) {
     __stack_chk_guard = 0xBAAAAAAD;//provide some magic numbers
}

// This will be called when guard variable is corrupted 
void __stack_chk_fail(void) {
 /* Error message */
}
