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

## @file
#  @brief Sample code to illustrate use of 
#         PIC24/dsPIC33-specific Python functions
#

# Load in the PIC24/dsPIC33 library
import pic24_dspic33 as pic

# Demo some of the PIC hardware functions
# ---------------------------------------

# Toggle a pin
#                    port pin isInput isOpenDrain pullDir
dio = pic.digital_io(1,   1,  False,  False,      0)
dio.set(not dio.get())

# Do some analog input
ain = pic.analog_input(0)
print ain.getVoltage()

# Do some PWM
#              freq  isTimer2 oc ocPin
pwm1 = pic.pwm(1000, True,    2, 0)
pwm1.set(0.5)

# Now run main.py to start up ipm
import main
