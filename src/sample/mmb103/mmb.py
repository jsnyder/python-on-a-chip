# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

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
# LOG
# ---
#
# 2006/08/21    Updated to new native fxn interface
# 2002/10/14    Implemented most libmmb103 functions.
# 2002/09/07    Created.
#
"""__NATIVE__
#include "libmmb103.h"
"""

#### FUNCS

def adcGet(c):
    """__NATIVE__
    /* The arg is the ADC channel to read */
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    S8 chan;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get arg, throw type exception if it's not an int */
    pc = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pc) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the channel number */
    chan = (S8)(((pPmInt_t)pc)->val & 0x03);

    /* Return new int from the conversion result on the stack */
    retval = int_new(mmb_adcGet(chan), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def adcGetBMA(c):
    """__NATIVE__
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    S8 chan;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get arg, throw type exception if it's not an int */
    pc = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pc) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the channel number */
    chan = (S8)(((pPmInt_t)pc)->val & 0x03);

    /* Return new int from the conversion result on the stack */
    retval = int_new(mmb_adcGetBMA(chan), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def beep(f, ms):
    """__NATIVE__
    pPmObj_t pf = C_NULL;
    pPmObj_t pms = C_NULL;
    U16 f;
    U16 ms;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the args, throw exception if needed */
    pf = NATIVE_GET_LOCAL(0);
    pms = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(*pf) != OBJ_TYPE_INT) ||
        (OBJ_GET_TYPE(*pms) != OBJ_TYPE_INT))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get frequency and duration values */
    f = (U16)((pPmInt_t)pf)->val;
    ms = (U16)((pPmInt_t)pms)->val;

    /* Call mmb's beep fxn */
    mmb_beep(f, ms);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def digGet(c):
    """__NATIVE__
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    S8 chan;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw exception if needed */
    pc = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pc) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the channel value */
    chan = (S8)(((pPmInt_t)pc)->val & 0x03);

    /* Return new int with digital value on stack */
    retval = int_new(mmb_digGet(chan), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def digGetByte():
    """__NATIVE__
    pPmObj_t pr = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Return new int from DIG port value on stack */
    retval = int_new(mmb_digGetByte(), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def dipGet(c):
    """__NATIVE__
    pPmObj_t pc = C_NULL;
    pPmObj_t pr = C_NULL;
    S8 chan;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    pc = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pc) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the chan value */
    chan = (S8)(((pPmInt_t)pc)->val & 0x03);

    /* Return dip value on the stack */
    retval = int_new(mmb_dipGet(chan), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def dipGetByte():
    """__NATIVE__
    pPmObj_t pr = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Return new int from DIG port value on stack */
    retval = int_new(mmb_dipGetByte(), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def init():
    """__NATIVE__
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Init board */
    mmb_init(BAUD19200,         /* uart rate   */
             ADC_CK_DIV_16,     /* DIV_16 = ADC @ 2Ksps */
             PWM_CK_DIV_8,      /* DIV_8  = PWM @ ~2KHz */
             2                  /* 2 lcd lines */
             );

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def lcdClrScr():
    """__NATIVE__
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Clear the LCD screen */
    mmb_lcdClrScr();

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def lcdPrintStr(ps):
    """__NATIVE__
    pPmObj_t ps = C_NULL;
    P_U8 s = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    ps = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*ps) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get a pointer to the string */
    s = (P_U8)((pPmString_t)ps)->val;

    /* Print the string on the mmb's lcd */
    /* WARNING: PyMite's strings aren't null term 100% of the time */
    mmb_lcdPrintStr(s);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def lcdSetLine(n):
    """__NATIVE__
    pPmObj_t pn = C_NULL;
    U8 n;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the line number and call mmb lib fxn*/
    n = (U8)((pPmInt_t)pn)->val;
    mmb_lcdSetLine(n);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def lcdTitleScreen():
    """__NATIVE__
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    mmb_lcdTitleScreen();

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def pwmA(s):
    """__NATIVE__
    pPmObj_t ps = C_NULL;
    S8 duty;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw exception if needed */
    ps = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*ps) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the duty cycle value */
    duty = (S16)((pPmInt_t)ps)->val;

    mmb_pwmA(duty);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def pwmB(s):
    """__NATIVE__
    pPmObj_t ps = C_NULL;
    S8 duty;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    ps = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*ps) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the duty cycle value */
    duty = (S16)((pPmInt_t)ps)->val;

    mmb_pwmB(duty);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def sciGetByte():
    """__NATIVE__
    pPmObj_t pr = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Return new int from SCI value on stack */
    retval = int_new(mmb_sciGetByte(), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def sciPutByte(c):
    """__NATIVE__
    pPmObj_t pc = C_NULL;
    U8 c;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg */
    pc = NATIVE_GET_LOCAL(0);

    /* if arg is a string, write 0th char */
    if (OBJ_GET_TYPE(*pc) == OBJ_TYPE_STR)
    {
        c = (U8)(((pPmString_t)pc)->val[0]);
        mmb_sciPutByte(c);
    }
    /* if arg is an int, write LSB */
    else if (OBJ_GET_TYPE(*pc) == OBJ_TYPE_INT)
    {
        c = (U8)(((pPmInt_t)pc)->val & 0xFF);
        mmb_sciPutByte(c);
    }

    /* Otherwise, throw type exception */
    else
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def sciPutStr(s):
    """__NATIVE__
    pPmObj_t ps = C_NULL;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    ps = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*ps) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Blocking write of s out SCI port */
    /* WARNING: PyMite strings aren't always null-terminated! */
    mmb_sciPutStr(((pPmString_t)ps)->val);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def sleepms(ms):
    """__NATIVE__
    pPmObj_t pms = C_NULL;
    U16 ms;
    PmReturn_t retval;

    /* If wrong number of args, throw type exception */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the arg, throw type exception if needed */
    pms = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(*pms) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get the line number and call mmb lib fxn*/
    ms = (U16)((pPmInt_t)pms)->val;

    mmb_sleepms(ms);

    /* Return none obj on stack */
    NATIVE_SET_TOS(PM_NONE);

    return PM_RET_OK;
    """
    pass


def toc():
    """__NATIVE__
    pPmObj_t pr = C_NULL;
    PmReturn_t retval;

    /* Return new int from toc value on stack */
    retval = int_new((S32)mmb_toc(), &pr);
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass

# :mode=c:
