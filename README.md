# C64 Tutorial-like Projects

Here are some of my easy projects done for cc65 compiler suite.
Most of them are written in C. However, there are also some assembler projects.

## What is included in this repo?

Some really simple programs showing that programming in C for C64 reminds programming in assembler (a bit) and consist of POKE-ing and PEEK-ing too much like in Basic if you want to do something more.
Okay, maybe I'm exaggerating, but I think that coding for C64 is generally pushing and getting some data into and from memory or devices (both internal and external).
My codes here are really simple and shows some basic operations on Commodore 64 performed using C language, which might be helpful while beginning with cc65 compiler.
However, the C64 memory map and 6502 instruction set (if you want to make some assembly in C codes or understand why some codes work) would be your friends from now - knowing what is where you would have 50% of work done. Really. ;)

## How to compile these codes?

Yep, I know, that I haven't written any Makefiles for my codes. Shame on me, but it's just because I've done those codes really quick in breaks from sad university life. :P
And also I love to write too much in the console while experimenting with some new programming tactics. ;)

OK, not to say so much..

### Compiling C codes

...is really easy. :) Just type in console:
```
cl65 some_code.c -o some_code.prg
```
And it's done now. ;)

Why not to use cc65 and ld65 later? Because using cl65 is more comfortable. At least for me. :) Well, if you want to provide some additional settings to the compilation process, you can do it via cl65 too!
Just type:
```
cl65 --help
```
or
```
cc65 --help
```
or
```
ld65 --help
```
and look what you can set from your needs. :) As far as I know, the cl65 can forward most of the settings to both cc65 and ld65.

### Compiling assembler codes

And here is much more to say...
Maybe I could start with saying that my assembler codes aren't perfect. Well, at least **c128check.asm** isn't perfect. It's just a stub that can be used combined with other program, so it's programmed the way it's not comfortable to compile.

To compile it properly you have to type:
```
cl65 c128check.asm --start-addr 2061 -t none -o c128check.prg
```
**AND IT'S NOT ALL YET!**

Only the assembler code is compiled and linked into machine code. But it doesn't contain Basic's startup code providing SYS 2061 line or similar. You need to provide it manually using some hex editor.

To make it properly, open c128check.prg in hex editor (for example Hex Fiend on Mac, or HxD Hex Editor on Windows) and add those bytes **AT THE BEGINNING** of the whole file:
```
01 08 0B 08 20 03 9E 32 30 36 31 00 00 00
```
This will make a Basic startup code, and you will be able to run this code both on Commodore 64 and Commodore 128.

I know, not really comfortable to work on it. I'll try to make some Makefiles next time. At least for assembly. ;)

## Codes history

It was in late May 2019. I've still remembered last AmiParty from February, when I coded in Commodore Basic the whole saturday evening using MarX's C64. ;)
I felt really interested in playing with these great 8-bit computers. Especially because I always loved classic computers and just wanted to try. I remember, that I dreamed of creating software which could save and load data from datassette.
So I decided to spent some days on trying to code some great software using Basic, but finally I've seen that programs written in this language are not really efficient even while coding some really basic stuff.
I've thought whole evening how to do it better, and finally I've decided to code something in language needing compiling. But the choice wasn't really wide. "Assembler is the best!", of course. Everybody would say that.
Well, for coding powerful demos it's probably the only solution, but I still wanted to code some basic stuff like simple notepad, image displayer or tape-to-disk file copier. I felt really confused to make it using assembly.
Suddenly, I remembered, that some years ago I've accidentally found a C compiler for 6502-based computers. It was called **cc65**. I've found it on the internet and compiled simple "Hello world!" program.
I felt perfect. "I can make everything!". :) But, there wasn't as good and easy as I've thought.

### Documentation of cc65

Haha, that's something that does not exists.. :D
Well, to be fair, it nearly doesn't exists. The main documentation of procedures and structures of libraries available to use is in the include files and in archived mailing list (which is also not fully archived because it was deleted from cc65's official website due to GDPR).
However, I decided to be stubborn and to find as much solutions for my problems as I'll be able to.

## Disclaimer

I've made much effort to provide here working and checked codes with hope it will be useful. Most of these programs were checked on a real hardware.
**However, these codes are provided here "AS IS", with absolutely no warranty! I take no responsibility for using them - DO IT ON YOUR OWN RISK!**

## License

Codes provided here are free for personal use.
If you like to use any part of these codes in your software, just please give me some simple credits and it will be okay. ;)
In case you would like to make paid software and use parts of these codes - please, contact me before.

*Bartłomiej "Magnetic-Fox" Węgrzyn,
8th January, 2021*
