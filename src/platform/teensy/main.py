# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
# 
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.

#
# This is a sample application that duplicates a stripped-back version of Teensy's own "blinky.c"
# in Python - blinking an LED with morse code and concurrently outputting a text version via usb serial
#

# Implementation by Angus Gratton, 2010.


print "Hello world."

import avr

# Swap this number to 2 if you have a Teensy++ 2.0 (changes LED pins & polarity)
teensyVersion = 1

# NB: 8kb is not enough RAM to have a full translation table character -> morse code string 
# in a dictionary!
#
# So we're going with a stripped down morse code(!) If you comment out
# some of the other functions in avr.py (portA & ddrA are uncommented
# by default) & __bi.py then you save a bit more RAM and can uncomment
# more morse characters without running out of RAM!
morse = {
#    'A' : '.-',
#    'B' : '-...',
#    'C' : '-.-.',
    'D' : '-..',
    'E' : '.',
#    'F' : '..-.',
#    'G' : '--.',
#    'H' : '....',
#    'I' : '..',
#    'J' : '.---',
#    'K' : '-.-',
    'L' : '.-..',
    'M' : '--',
#    'N' : '-.',
    'O' : '---',
#    'P' : '.--.',
#    'Q' : '--.-',
#    'R' : '.-.',
    'S' : '...',
#    'T' : '-',
#    'U' : '..-',
#    'V' : '...-',
#    'W' : '.--',
#    'X' : '-..-',
#    'Y' : '-.--',
#    'Z' : '--..',
}

def loop():
    for i in range(1,6):
        printMorse("SOS")
        avr.delay(1500)
    printMorse("DOES ANYBODY STILL KNOW MORSE CODE?")
    avr.delay(4000)

def printMorseCharacter(c):
    print "Char " + c,
    if c in morse:
        for s in morse[c]:
            # Some constants, in here because we run out of memory if we put them at the top-level            
            ledOn = False if teensyVersion == 1 else True
            ledPin = 6 if teensyVersion == 1 else 1
            ledPort = 'D' if teensyVersion == 1 else 'C'
            dit = 80

            avr.digitalWrite(ledPort, ledPin, ledOn)
            if s == '.':
                print " dit",
                avr.delay(dit)
            elif s == '-':
                print " dah",
                dah = dit * 3
                avr.delay(dah)
            else:
                print " ?",            
            avr.digitalWrite(ledPort, ledPin, not ledOn)
            avr.delay(dit)  
    else:
        print " ?",
    print

def printMorse(msg):
    print "Message " + msg
    for c in msg:
        printMorseCharacter(c)

while True:
    loop()
