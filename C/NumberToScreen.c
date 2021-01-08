/*
 
 Double-digit number to screen converter.
 December 1st, 2019
 
 Comment added: January 7th, 2021.
 
 This software contains simple procedure for converting
 double-digit numbers to charcodes for screen displaying.
 
 (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 
*/

#include <peekpoke.h>               /* PEEK and POKE operations. */
#include <cbm.h>                    /* KERNAL's BSOUT operation. */

#define put(c) cbm_k_bsout(c)       /* Some simple macro. */

void print2d(unsigned char input)   // Procedure for double-digit numbers converting.
{
	put(0x30+((input/10)%10));      // Prints first digit of the number. The formula looks a bit complicated, but it's not. First of all, it's important
                                    // that using this macro we're nearly just entering data to the screen memory. So we have to calculate character codes.
                                    // That's why here is 0x30 at the beginning. It's '0' code. Adding to this charcode any number will give another digit.
                                    // Saying about the formula, it's just getting first digit of double-digit number. We have to make integer divide by 10
                                    // and we get the first digit. The modulo by 10 operation is not necessary while we're using only double-digit numbers,
                                    // but it should be there because of possibility of using numbers which has more digits. This operation used this way
                                    // gives always the same digit from input number.
    
                                    // Some example:
    
                                    // 54
    
                                    // 54 div 10 = 5
                                    //  5 mod 10 = 5
    
                                    // 154
    
                                    // 154 div 10 = 15 (!)
                                    //  15 mod 10 =  5 (!)
    
	put(0x30+(input%10));           // Prints last digit from number.
    
	return;                         // Procedure end.
}

int main(void)                      // Main code.
{
	POKE(0xD018,0x15);              // Switching font mode to normal size.
	print2d(8);                     // Testing procedure.
	return 0;                       // Program end.
}
