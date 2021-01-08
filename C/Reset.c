/*
 *
 * Soft reset utility.
 * July 17th, 2019
 *
 * Comment added: January 7th, 2021.
 *
 * This software performs software reset of C64.
 *
 * (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 *
 */

#include <peekpoke.h>           /* PEEK and POKE operations. */

int main(void)                  // Main code.
{
	POKE(0xD018,0x15);      // Changing font mode to normal size.
	__asm__ ("JMP $FCE2");  // Jumping to 0xFCE2 (64738) which contains restart code.
	return 0;               // Program end. Note that this part of code is never reached even if we would use JSR instead of JMP above.
}
