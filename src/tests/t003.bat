avr-gcc -ansi -I../vm -I%AVR% -Os -g -Wall -gstabs -mmcu=atmega103 -Map=t003.map -o t003.elf t003.c codeobj.o mem.o img.o heap.o global.o sli.o obj.o string.o tuple.o module.o dict.o
echo off
rem AStudio file creation
avr-objcopy -O avrobj t003.elf t003.obj
avr-objcopy -O srec   t003.elf t003.rom

