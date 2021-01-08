/*
 *
 * Drive detection, model and software version utility.
 * December 1st, 2019
 *
 * Comment added: January 7th, 2021.
 *
 * The goal of this software is to detect all four drives connected
 * to the C64's IEC port and to display their versions.
 *
 * (C)2019-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!
 *
 */

#include <peekpoke.h>                                   /* Library with simple macros for getting and setting data in memory (like PEEK and POKE on Basic). */
#include <cbm.h>                                        /* Library providing KERNAL procedures as C procedures. */

#define put(c) cbm_k_bsout(c)                           /* Macro for shortening the code. */

void screen_print(unsigned char* data)                  // Some simple procedure for printing strings on screen.
{                                                       // REALLY USEFUL PROCEDURE!!! IT DECREASES FINAL PROGRAM SIZE FROM KILOBYTES TO BYTES BECAUSE IT'S
                                                        // LESS COMPLEX THAN CPRINTF!
    
	unsigned int x=0;                               // Template variable for string loop.
	while(data[x]>=0x20)                            // String loop printing characters up to first non-printable character.
	{
		cbm_k_bsout(data[x++]);                 // Using KERNAL's BSOUT to print single characters. Well, I don't know why I haven't used my macro defined before...
	}
	return;                                         // Procedure end.
}

void print2d(unsigned char input)                       // Simple procedure for printing double-digit numbers with the same printed text size.
{
	if(input<10)                                    // If given number is less than 10, then
	{
		put(' ');                               // it prints single space.
	}
	else                                            // If given number is not less than 10, then
	{
		put(0x30+((input/10)%10));              /* it prints first digit of the number. The formula looks a bit complicated, but it's not. First of all, it's important
                                                         * that using this macro we're nearly just entering data to the screen memory. So we have to calculate character codes.
                                                         * That's why here is 0x30 at the beginning. It's '0' code. Adding to this charcode any number will give another digit.
                                                         * Saying about the formula, it's just getting first digit of double-digit number. We have to make integer divide by 10
                                                         * and we get the first digit. The modulo by 10 operation is not necessary while we're using only double-digit numbers,
                                                         * but it should be there because of possibility of using numbers which has more digits. This operation used this way
                                                         * gives always the same digit from input number.
                                                         *
                                                         * Some example:
                                                         *
                                                         * 54
                                                         *
                                                         * 54 div 10 = 5
                                                         *  5 mod 10 = 5
                                                         *
                                                         * 154
                                                         *
                                                         * 154 div 10 = 15 (!)
                                                         *  15 mod 10 =  5 (!)
                                                         */
	}
	put(0x30+(input%10));                           // Prints last digit from number.
    
	return;                                         // Procedure end.
}

void nextLine()                                         // Simple procedure for going to the next line.
{
	put('\r');                                      // Puts carriage return.
	put('\n');                                      // Puts line feed (next line).
    
	return;                                         // Procedure end.
}

int main(void)                                          // Main code.
{
	unsigned char z;                                // Template variables for future use.
	unsigned int x;
    
	POKE(0xD018,0x15);                              // Makes characters normal-sized. The cc65 compiler creates each program the way it sets this variable
                                                        // to 0x17 (as far as I remember now), which causes C64 to display small letters. If we don't wish it
                                                        // to do it, we have to manually set this byte back to 0x15. Most of my programs are using this trick.
    
	nextLine();                                     // Goes next line.
    
	for(x=8; x<12; ++x)                             // Drive addresses loop
	{
		put(' ');                               // Puts single space.
		print2d(x);                             // Prints drive number (address)
		screen_print(":");                      // Prints colon.
		cbm_k_setlfs(1,x,15);                   // Sets first opened device to current loop's number and sets communication channel to 15.
		cbm_k_setnam("");                       // Sets file name to empty string. Just in case it would be set, because IT CAN'T BE SET TO ANY FILE NAME TO WORK PROPERLY BELOW.
		cbm_k_open();                           // Opens device.
		cbm_k_ckout(1);                         // Sets output device to opened device.
		if(cbm_k_readst()!=0)                   // If C64's status code is not equal zero after changing the device, it's not present.
		{
			cbm_k_clrch();                  // Sets input and output devices to default (screen).
			screen_print("not present");    // Prints information, that the device is not present.
		}
		else                                    // If C64's status code is equal zero after changing the device, it's present and we've properly changed it.
		{
			cbm_k_bsout('u');               // Because 15th channel of Commodore Disk Drives is command channel, I can communicate with disk drive controller to get what
			cbm_k_bsout('i');               // is needed. To get disk drive model and its CBM DOS version I have to perform its soft reset. That's because those disk
                                                        // drives gives such information only as a first message You can receive on command channel (this way a.k.a. error channel).
                                                        // Note that every thing You do with the disk drive changes its state - if everything was executed properly the message will be
                                                        // set to string "00, OK,00,00", but if not it should contain error code, name and flags. Even after just listing the directory
                                                        // You can't get drive name and version until its next boot (so, power off and on or just reset).
            
			cbm_k_clrch();                  // Sets default devices.
			cbm_k_chkin(1);                 // Sets input device to first opened device (our disk drive).
            
			while(cbm_k_readst()==0)        // While the C64's status code is equal to zero, we can read disk drive's message character by character.
			{
				z=cbm_k_basin();        // Reads single character to the buffer.
				if(z>=0x20)             // If this buffer contains printable characters
				{
					put(z);         // I'll just print it.
				}
			}                               // Loop end.
            
            cbm_k_clrch();                              // Sets input and output devices to defaults.
		}
		cbm_k_close(1);                         // Closes opened device.
        
		nextLine();                             // Goes next line.
	}
	return 0;                                       // Finishes program.
}
