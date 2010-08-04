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
#  @brief PIC24/dsPIC33-specific Python functions
#

"""__NATIVE__
#include <pic24_all.h>
#include "pyFuncsInC.h"
"""

## This class provides basic digital I/O for the PIC.
#  Configuring a given pin overrides any previous
#  configuration (as an analog input, other digitial
#  I/O, peripheral such as UART, SPI, etc.)
class digital_io(object):
    ## Configures a pin for digital operation.
    #  Parameters:
    #  @param port The port, specified as a one-letter string,
    #              which must be from "A" to "G".
    #  @param pin  The pin of the port to configure. Must be
    #              a number between 0 and 15.
    #  @param isInput True to configure the pin as an input,
    #              false to configure the pin as an output.
    #  @param isOpenDrain True to configure the pin's output
    #              drivers to be 
    #              <a href="http://en.wikipedia.org/wiki/Open_collector">open drain</a>,
    #              false to configure the pin's output drivers
    #              as a standrard
    #              <a href="http://en.wikipedia.org/wiki/Totem_pole_output">push-pull</a>
    #              output. <em>IMPORTANT</em>: Not all pins
    #              have open-drain ability; therefore, the only
    #              valid selection for this parameter may be false.
    #              All pins have standard, push-pull drivers.
    #  @param pullDir A value > 0 to enable a 
    #              <a href="http://en.wikipedia.org/wiki/Pull-up_resistor">pull-up resistor</a>
    #              on the pin, a value < 0 to enable a pull-down
    #              resistor on the pin, or 0 to disable both.
    #              <em>IMPORTANT</em>: Not all pins have pull-up
    #              or pull-down capability. Valid values for
    #              some pins are 0 (neither pull-up nor pull-down
    #              resistors are available), or >=0 (only
    #              pull-up resistors are available).
    def __init__(self, port, pin, isInput, isOpenDrain=False, pullDir=0):
        """__NATIVE__
        return configDigitalPinPy(ppframe);
        """
        pass

    ## Set a pin's output to be high or low (True or False). The pin
    #  must be configured as an output for this value to appear on the pin.
    #  @param isHigh True to set the pin high, False to set it low.
    def set(self, isHigh):
        """__NATIVE__
        return setDigitalPinPy(ppframe);
        """
        pass

    ## Read a pin's value. If the pin is an input, read the pin;
    #  if it's an output, read the last value written.
    def get(self):
       """__NATIVE__
       return readDigitalValuePy(ppframe);
       """
       pass

    ## Read the current digital voltage (high or low / True or False) on
    #  a pin.
    def getPin(self):
       """__NATIVE__
       return readDigitalPinPy(ppframe);
       """
       pass

    ## Read the last value written to this pin (that is, the value stored
    #  in the pin's latch).
    def getLatch(self):
       """__NATIVE__
       return readDigitalLatchPy(ppframe);
       """
       pass


## This class provides basic analog input for the PIC.
#  Configuring a given pin overrides any previous
#  configuration (as a digital input, other digital
#  I/O, peripheral such as UART, SPI, etc.)
class analog_input(object):
    ## Create the class for a specific analog pin, numbered ANxx on the
    #  data sheet. Configures the pin as an analog input.
    #  @param analogPin Pin to configure.
    def __init__(self, analogPin):
        """__NATIVE__
        return configAnalogPinPy(ppframe);
        """
        pass

    ## Read the code produced by the ADC, a value from 0 to 4095
    #  which is linearly proportional to the input voltage.
    def getCode(self):
        """__NATIVE__
        return readAnalogCodePy(ppframe);
        """
        pass

    ## Read the voltage produced by the ADC, resulting in a
    #  returned value between 0 and 3.3V.
    def getVoltage(self):
        """__NATIVE__
        return readAnalogFloatPy(ppframe, 3.3/4096.0);
        """
        pass

    ## Read the voltage produced by the ADC, resulting in a
    #  normalized value ranging from 0 to 1.
    def getNorm(self):
        """__NATIVE__
        return readAnalogFloatPy(ppframe, 1.0/4096.0);
        """
        pass

## This class provides basic control of the pulse-width
#  modulation peripheral for the PIC.
class pwm(object):
    ## Create the class instance for a PWM output.
    #  @param freq Frequency at which the PWM will operate, in Hz.
    #  @param isTimer2 True to use timer2, false to use timer3 for
    #      PWM.
    #  @param oc Output compare module to use.
    #  @param ocPin For remappable devices, the port P pin on
    #      which to map the PWM output. For non-remappable devices,
    #      this value must be < 0.
    def __init__(self, freq, isTimer2, oc, ocPin=-1):
        """__NATIVE__
        return configPwmPy(ppframe);
        """
        pass

    ## Set the duty cycle for a PWM output.
    #  @param ratio The desired duty cycle, ranging from 0 (off
    #      completely) to 1 (maximum, 100% duty cycle).
    def set(self, ratio):
        """__NATIVE__
        return setPwmRatioPy(ppframe);
        """
        pass

    ## Set the duty cycle for a PWM output.
    #  @param counts The number of PR2/3 counts which gives the on
    #      time of the PWM wave to generate.
    def setCounts(self, counts):
        """__NATIVE__
        return setPwmCountsPy(ppframe);
        """
        pass

