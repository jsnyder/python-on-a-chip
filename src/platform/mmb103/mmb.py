# This file is Copyright 2006, 2007, 2009 Dean Hall.
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
# MMB Access Module
#
# Provides access to the MegaMiniBoard103
# by wrapping libmmb103 functions.
# Use of this module requires that mmb.py
# be run through the pmImgCreator,
# the output from that be compiled
# and linked with libmmb103.a and the PyMite system.
#
# USAGE
# -----
#
# import mmb
# mmb.init()
#

"""__NATIVE__
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libmmb103.h"
"""


def adc_get(c):
    """__NATIVE__
    /* The arg is the ADC channel to read */
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    uint8_t chan;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get arg, throw type exception if it's not an int */
    pc = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pc) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the channel number */
    chan = (uint8_t)(((pPmInt_t)pc)->val & 0x03);

    /* Return new int from the conversion result on the stack */
    retval = int_new(mmb_adc_get(chan), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


#def beep(f, ms):
#    """__NATIVE__
#    pPmObj_t pf = C_NULL;
#    pPmObj_t pms = C_NULL;
#    int16_t f;
#    int16_t ms;
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 2)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get the args, throw exception if needed */
#    pf = NATIVE_GET_LOCAL(0);
#    pms = NATIVE_GET_LOCAL(1);
#    if ((OBJ_GET_TYPE(pf) != OBJ_TYPE_INT) ||
#        (OBJ_GET_TYPE(pms) != OBJ_TYPE_INT))
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get frequency and duration values */
#    f = (int16_t)((pPmInt_t)pf)->val;
#    ms = (int16_t)((pPmInt_t)pms)->val;
#
#    /* Call mmb's beep fxn */
#    mmb_beep(f, ms);
#
#    /* Return none obj on stack */
#    NATIVE_SET_TOS(PM_NONE);
#
#    return PM_RET_OK;
#    """
#    pass


#def dig_get(c):
#    """__NATIVE__
#    pPmObj_t pc = C_NULL;
#    pPmObj_t pr = C_NULL;
#    int8_t chan;
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 1)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get the arg, throw exception if needed */
#    pc = NATIVE_GET_LOCAL(0);
#    if (OBJ_GET_TYPE(pc) != OBJ_TYPE_INT)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get the channel value */
#    chan = (int8_t)(((pPmInt_t)pc)->val & (int8_t)0x03);
#
#    /* Return new int with digital value on stack */
#    retval = int_new(mmb_dig_get(chan), &pr);
#    NATIVE_SET_TOS(pr);
#
#    return retval;
#    """
#    pass


#def dig_get_byte():
#    """__NATIVE__
#    pPmObj_t pr = C_NULL;
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 0)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Return new int from DIG port value on stack */
#    retval = int_new(mmb_dig_get_byte(), &pr);
#    NATIVE_SET_TOS(pr);
#
#    return retval;
#    """
#    pass


def dip_get(c):
    """__NATIVE__
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    int8_t chan;
    PmReturn_t retval;

    /* If no args, get all dip switches as one byte */
    if (NATIVE_GET_NUM_ARGS() == 0)
    {
        retval = int_new(mmb_dip_get_byte(), &pr);
    }

    /* If one arg, get the designated dip switch */
    else if (NATIVE_GET_NUM_ARGS() == 1)
    {
        /* Raise TypeError if arg is not an int */
        pc = NATIVE_GET_LOCAL(0);
        if (OBJ_GET_TYPE(pc) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the channel number and read that dip switch */
        chan = (int8_t)(((pPmInt_t)pc)->val & (int8_t)0x03);
        retval = int_new(mmb_dip_get(chan), &pr);
    }

    /* Raise TypeError if wrong number of args */
    else
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
    }

    NATIVE_SET_TOS(pr);
    return retval;
    """
    pass


#def init():
#    """__NATIVE__
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 0)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Init board */
#    mmb_init(BAUD_19200, ADC_CK_DIV_128, PWM_CK_DIV_8, 4, 20);
#
#    /* Return none obj on stack */
#    NATIVE_SET_TOS(PM_NONE);
#
#    return PM_RET_OK;
#    """
#    pass


#def lcd_cls():
#    """__NATIVE__
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 0)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Clear the LCD screen */
#    mmb_lcd_clr_scr();
#
#    /* Return none obj on stack */
#    NATIVE_SET_TOS(PM_NONE);
#
#    return PM_RET_OK;
#    """
#    pass


def lcd_print(ps):
    """__NATIVE__
    pPmObj_t ps = C_NULL;
    uint8_t *s = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    ps = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(ps) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get a pointer to the string */
    s = ((pPmString_t)ps)->val;

    /* Print the string on the mmb's lcd */
    mmb_lcd_print_str(s);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def lcd_set_line(n):
    """__NATIVE__
    pPmObj_t pn = C_NULL;
    uint8_t n;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the line number and set the cursor to that line */
    n = (uint8_t)((pPmInt_t)pn)->val;
    mmb_lcd_set_cursor(n, 0);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


#def lcd_title_screen():
#    """__NATIVE__
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 0)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    mmb_lcd_title_screen();
#
#    /* Return none obj on stack */
#    NATIVE_SET_TOS(PM_NONE);
#
#    return PM_RET_OK;
#    """
#    pass


def set_pwm_a(n):
    """__NATIVE__
    pPmObj_t pn = C_NULL;
    int16_t duty;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw exception if needed */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the duty cycle value */
    duty = (int16_t)((pPmInt_t)pn)->val;

    mmb_set_mota_pwm(duty);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


#def set_pwm_b(n):
#    """__NATIVE__
#    pPmObj_t pn = C_NULL;
#    int16_t duty;
#    PmReturn_t retval;
#
#    /* If wrong number of args, throw type exception */
#    if (NATIVE_GET_NUM_ARGS() != 1)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get the arg, throw type exception if needed */
#    pn = NATIVE_GET_LOCAL(0);
#    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
#    {
#        PM_RAISE(retval, PM_RET_EX_TYPE);
#        return retval;
#    }
#
#    /* Get the duty cycle value */
#    duty = (int16_t)((pPmInt_t)pn)->val;
#
#    mmb_set_motb_pwm(duty);
#
#    /* Return none obj on stack */
#    NATIVE_SET_TOS(PM_NONE);
#
#    return PM_RET_OK;
#    """
#    pass


def sleepms(ms):
    """__NATIVE__
    pPmObj_t pms = C_NULL;
    int16_t ms;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    pms = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pms) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the delay value, apply API limits and call delay fxn */
    ms = (int16_t)((pPmInt_t)pms)->val;
    if (ms < 0) ms = 0;
    else if (ms > 65) ms = 65;
    _delay_ms(ms);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass

# :mode=c:
