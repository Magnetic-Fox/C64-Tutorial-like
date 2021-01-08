/*
 *
 * Gets loading device's number.
 * December 1st, 2019
 *
 * Comment added: January 7th, 2021.
 *
 * This software gives number of the device that loaded
 * the program to the memory.
 *
 * (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 *
 */

#include <peekpoke.h>                   /* PEEK and POKE operations. */
#include <cbm.h>                        /* KERNAL procedures. */

#define put(c) cbm_k_bsout(c)           /* BSOUT procedure for printing single characters. */

void printByte(unsigned char input)     // Byte printing procedure. Calculates character codes and digits from number.
{
	put(0x30+(input/100));          // Prints first digit from three-digit number.
	put(0x30+((input/10)%10));      // Prints second digit from three-digit number.
	put(0x30+(input%10));           // Prints third digit from three-digit number.
    
	return;                         // Procedure end.
}

int main(void)                          // Main code.
{
	POKE(0xD018,0x15);              // Switch to normal-sized font.
	printByte(PEEK(186));           // Print number of the device, that loaded last program to memory.
                                        // This information is stored at address 0xBA (186).
    
	return 0;                       // Program end.
}
