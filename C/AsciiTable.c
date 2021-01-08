/*
 
 Simple ASCII Table Generator
 June 9th, 2019
 
 Comment added: January 7th, 2021
 
 The main goal of this simple software is to print character map on
 C64's screen. Generated character map will have 16 chars in row by
 16 rows.
 
 (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 
 */

#include <conio.h>                                      /* Include for standard console-like operations. */

#define PRINT  cprintf                                  /* Some macro for printing procedure. */
#define PUT(c) cputc((char)(c))                         /* Some, much more useful, macro for printing single character on screen. */
#define GET() (int)cgetc()                              /* Also some macro for getting single characters from keyboard. */

int main(void)                                          // Main code of the program.
{
	unsigned int x=0, y=0;                              // Template variables for loops below.
    
	clrscr();                                           // Clears C64's screen.
    
	revers(1);                                          // Switches on "reverse characters" on display.
	gotoxy(8,1);                                        // Goes to position 8,1 (in columns and rows, respectively) on screen.
	PRINT(" - Character Map v1.0 - ");                  // Prints text.
    
	gotoxy(4,2);                                        // Goes to position 4,2 on screen.
	PRINT("Copyright (c)2019 Magnetic-Fox!\r\n\r\n");   // Again prints text and goes two rows after (carriage return and line feed x2 at end).
	revers(0);                                          // Switches off reverse characters on display.
    
	PRINT("x 0 1 2 3 4 5 6 7 8 9 A B C D E F\r\n");     // Prints ruler of low parts of hex number representing character.
    
	for(y=0; y<16; ++y)                                 // For-loop for generating row of characters (a.k.a. row loop).
	{
		PRINT("%01X ",y);                               // Prints high part of hex number representing character.
        
		for(x=0; x<16; ++x)                             // For-loop for printing characters (a.k.a. column loop).
		{
			if((16*y+x)>=0x20)                          // Condition for printing printable characters. The formula for computing character is: 16 * (row number) + (column number).
			{
				PUT((char)(16*y+x));                    // The formula described before is used here for printing character. However, the character code has to be casted into character type.
				PUT(' ');                               // Puts one empty space after printed character - for better representation on screen.
			}
		}                                               // End of column loop.
        
		PRINT("\r\n");                                  // Goes one line after (carriage return and line feed).
	}                                                   // End of row loop.
    
	return 0;                                           // End of program - return to Commodore Basic.
}
