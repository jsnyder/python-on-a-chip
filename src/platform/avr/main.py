# This file is Copyright 2007, 2009 Dean Hall.
#
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
# This is a sample application that calls functions in the AVR module.
#
print "Hello world."

import avr


print "Counting from 0 to 249 on portA's pins"

avr.ddrA(0xFF)
i = 0
while i < 250:
    avr.portA(i)
    avr.delay(250)
    i += 1
print "Done."
