/*

 Simple interrupt handler.
 December 15th, 2019
 
 Comment added: January 7th, 2021
 
 The goal of this software is to create simple procedure and link
 it to the interrupt vector which is executed by RESTORE key.
 
 (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 
*/

#include <peekpoke.h>                       /* PEEK and POKE operations. */
#include <cbm.h>                            /* KERNAL procedures. */
#include <conio.h>                          /* Basic console procedures. */

#define GET() (int)cgetc()                  /* Macro for getting single chars from keyboard. */
#define put(c) cbm_k_bsout(c)               /* Macro for printing single chars on screen. */

void screen_print(unsigned char* data)      // Simple procedure for printing string.
{
	unsigned int x=0;                       // Temporary variable for string loop.
    
	while(data[x]>=0x20)                    // String loop which displays characters until it find first non-printable character.
	{
		cbm_k_bsout(data[x++]);             // Prints single character at the screen and goes next.
	}
	return;                                 // Procedure end.
}

void function(void)                         // Our function to link to the interrupt vector. This is only a simple procedure which prints simple text.
{
	screen_print("interrupt!");             // Prints "interrupt!" text.
    
	put('\r');                              // Puts carriage return.
	put('\n');                              // Puts line feed.
    
	return;                                 // Procedure end.
}

void callFunction(void)                     // Procedure for calling our interrupt procedure and come back from interrupt.
{
	function();                             // Calls our function.
	asm("rti");                             // After end of our function it's needed to come back from an interrupt. So, we're doing it.
    
	return;                                 // Procedure end. Note that this part of code isn't reached after RTI.
}

int main(void)                              // Main code.
{
	unsigned int var792, var793;            // Temporary address variables.
	unsigned char x;                        // Temporary character variable.
    
	POKE(0xD018,0x15);                      // Switches font to normal mode.
    
	var792=PEEK(792);                       // Gets address of procedure linked to RESTORE. So, the values from 792 and 793 addresses.
	var793=PEEK(793);
    
	POKEW(792,(unsigned int)&callFunction); // Puts word (16-bits) into memory containing address of our caller function.
    
	screen_print("press return to exit");   // Prints information how to exit this demo.
	put('\r');                              // Next line...
	put('\n');
    
	do                                      // Waits for keyboard actions.
	{
		x=GET();                            // Gets received character codes.
	} while(x!=13);                         // If the code is equal to 13 (RETURN), then we can finish this program.
    
	POKE(792,var792);                       // We're restoring address of original procedure.
	POKE(793,var793);
    
	return 0;                               // Program end.
}
