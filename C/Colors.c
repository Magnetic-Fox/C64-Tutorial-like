/*
 *
 * Simple color chart.
 * June 1st, 2019
 *
 * Comment added: January 7th, 2021.
 *
 * The goal of this simple software is to provide color chart
 * with codes printed on the screen of C64.
 *
 * (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 *
 */

#include <conio.h>                                      /* This include provides basic console-like support. */

#define PRINT  cprintf                                  /* Simple macro for printing text on screen. */
#define PUT(c) cputc((char)(c))                         /* Simple macro for printing single characters on screen. */
#define GET() (int)cgetc()                              /* Simple macro for getting single characters from keyboard. */

int main(void)                                          // Main part of the code.
{
	unsigned int x=0;                               // Template variable for loop below.
    
	clrscr();                                       // Clears the screen.
	bgcolor(0);                                     // Sets VIC's background color to black (which is code 0).
	bordercolor(0);                                 // Sets VIC's border color to black.
	textcolor(1);                                   // Sets VIC's text color to white (which is code 1).
    
	PRINT("Magnetic-Fox's Color Chart v1.0\r\nCopyright (c)2019 Magnetic-Fox!\r\n\r\n");    // Prints some text.
    
	revers(1);                                      // Switches on "reverse characters" on screen.
    
	for(x=0; x<16; ++x)                             // Loop for "enumerating" colors.
	{
		gotoxy(1,3+x);                          // Goes to the next lines starting with first character in third row.
		textcolor(x);                           // Sets next VIC's text color.
        
		if(x<10)                                // If color code is less than 10, then I'll execute another code. This has not much sense to do it this way, but..
		{
			if(x==0)                        // If color code is equal to 0 I'll have to execute yet another part of code to make the color code readable.
			{
				revers(0);              // Switches off reverse characters.
				textcolor(1);           // Sets VIC's text color to white.
				PRINT("     00");       // Prints some space at the beginning and color code in double digits format. Here it prints just 00, because it's black color.
				textcolor(0);           // Sets VIC's text color to black.
				revers(1);              // Switches on reverse characters.
			}
			else                            // If color code isn't equal to 0, then
			{
				PRINT("     0");        // I have to print only first digit of the number which is always 0 here, because at this place we have one-digit color codes,
			}                               // so it's a complement. Since this part of code these spaces are useful while using reverse characters, because we can make
                                                        // some color bars with them.
		}
		else                                    // If color code is not less than 10, then
		{
			PRINT("     ");                 // I only have to print some space (=generate some color bar). Note that here the space has the same length as above.
		}
		if(x!=0)                                // If color code isn't 0, then
		{
			PRINT("%d",x);                  // I have to print color code. Note that this code may be one- or double-digit here. That's beacuse I needed complements before.
		}
		PRINT("     ");                         // After printing color code I have to print yet another space (=generate rest of color bar).
	}
	revers(0);                                      // Switches off reverse characters.
	textcolor(1);                                   // Sets VIC's text color to white.
    
	PRINT("\r\n");                                  // Goes to next line.
    
	return 0;                                       // Finishes program.
}
