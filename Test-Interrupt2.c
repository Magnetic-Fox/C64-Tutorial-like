/*

 Interrupt array (jump table) handler.
 December 26th, 2019
 
 Comment added: January 7th, 2021.
 
 The goal of this software is to provide simple
 array of procedures (jump table) executed via
 linked interrupt.
 
 (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 
*/

#include <peekpoke.h>                           /* PEEK and POKE operations. */
#include <cbm.h>                                /* KERNAL operations. */
#include <conio.h>                              /* Basic console operations. */

#define put(c) cbm_k_bsout(c)                   /* Simple macro for printing single characters. */

static unsigned int addrTab[12];                // Static array of addresses (jump table).
static unsigned int x;                          // Static variable for procedure choosing.
static unsigned char y, runs=0;                 // Static variables for address taking and some mutex capability.

void screen_print(unsigned char* data)          // Simple string printing procedure.
{
	unsigned int x=0;                           // Template variable for string loop.
	while(data[x])                              // String loop printing whole string until terminator '\0'.
	{
		cbm_k_bsout(data[x++]);                 // Puts single character from string and goes next.
	}
	return;                                     // Procedure end.
}

/* Below are some example functions, that will be added later to the procedure array.
   All of them are really simple and just prints some text. */

void func1(void)
{
	screen_print("this ");
	return;
}

void func2(void)
{
	screen_print("is ");
	return;
}

void func3(void)
{
	screen_print("a ");
	return;
}

void func4(void)
{
	screen_print("simulation ");
	return;
}

void func5(void)
{
	screen_print("of\r\n");
	return;
}

void func6(void)
{
	screen_print("a ");
	return;
}

void func7(void)
{
	screen_print("jump ");
	return;
}

void func8(void)
{
	screen_print("table ");
	return;
}

void func9(void)
{
	screen_print("programmed\r\n");
	return;
}

void func10(void)
{
	screen_print("by ");
	return;
}

void func11(void)
{
	screen_print("magnetic-fox! ");
	return;
}

void func12(void)
{
	screen_print(":)\r\n");
	return;
}

void launch(void)                               // Launcher procedure which is a bit complicated, because it needs to use RTS trick.
{
	y=(unsigned char)((addrTab[x]>>8)&0xFF);    // Gets high part of the procedure's address (0x44AA -> 0x44)
	asm("lda %v",y);                            // Loads high part of address to the accumulator
	asm("pha");                                 // Pushes accumulator onto stack
	y=(unsigned char)(addrTab[x]&0xFF);         // Gets low part of the procedure's address (0x44AA -> 0xAA)
	asm("lda %v",y);                            // Loads low part of address to the accumulator
	asm("pha");                                 // Pushes accumulator onto stack
	asm("rts");                                 // Now, there's a trick. Return from subroutine will cause 6502 to pull address from stack and call it. Our procedure is executed.
	return;                                     // There is one really important thing to say - THESE WHOLE CALL MUST BE DONE USING ADDITIONAL PROCEDURE, LIKE ABOVE!
                                                // IT'S JUST BECAUSE WE HAVE TO HAVE RETURN ADDRESS TO AVOID PROGRAM CRASH. CALLING THIS PROCEDURE WILL CAUSE 6502 TO PUSH ADDRESS
                                                // OF THE NEXT INSTRUCTION ONTO A STACK AND COME BACK FROM ARRAY PROCEDURE WILL BE POSSIBLE.
}

void run(void)                                  // Interrupt procedure
{
	if(!runs)                                   // Some kind of mutex here. ;) If no other interrupt is executing, we can execute a new one.
	{
		runs=1;                                 // Locks possible parallel accessing.
		for(x=0; x<12; ++x)                     // Loop executing whole jump table.
		{
			launch();                           // Launches procedures.
		}
		runs=0;                                 // Unlocks access.
	}
	asm("rti");                                 // Returns from interrupt.
	return;                                     // Procedure end. Note that the program will never reach this place due to RTI.
}

int main(void)                                  // Main code.
{
	unsigned char var792, var793;               // Temporary backup variables.
    
	POKE(0xD018,0x15);                          // Switch to normal font size.
    
	addrTab[0]=(unsigned int)&func1-1;          // Prepares jump table.
	addrTab[1]=(unsigned int)&func2-1;          // The jump table will contain addresses lowered by 1, because after executing the 6502's RTS instruction
	addrTab[2]=(unsigned int)&func3-1;          // the program counter register is automatically incremented by 1.
	addrTab[3]=(unsigned int)&func4-1;          // We have to jump to the correct address to run those procedures properly.
	addrTab[4]=(unsigned int)&func5-1;
	addrTab[5]=(unsigned int)&func6-1;
	addrTab[6]=(unsigned int)&func7-1;
	addrTab[7]=(unsigned int)&func8-1;
	addrTab[8]=(unsigned int)&func9-1;
	addrTab[9]=(unsigned int)&func10-1;
	addrTab[10]=(unsigned int)&func11-1;
	addrTab[11]=(unsigned int)&func12-1;
    
	var792=PEEK(792);                           // Backs up the address of the current interrupt linked to RESTORE.
	var793=PEEK(793);
    
	POKEW(792,(unsigned int)&run);              // Links our interrupt procedure to the RESTORE.
    
	while(1)                                    // Inifinite loop.
	{
		if(kbhit())                             // If any key is pressed.
		{
			cgetc();                            // Clears the keyboard buffer.
			break;                              // Breaks the loop.
		}
	}
    
	POKE(792,var792);                           // Restores the interrupt vector.
	POKE(793,var793);
    
	return 0;                                   // Program end.
}
