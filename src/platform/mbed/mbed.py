# This file is Copyright 2009 Dean Hall.
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


"""__NATIVE__
#include "mbed.h"
#include "TextLCD.h"

static DigitalOut led1(LED1);
static DigitalOut led2(LED2);
static DigitalOut led3(LED3);
static DigitalOut led4(LED4);

/* PinName lookup table.  Converts pin number to PinName. */
static PinName const pinNumToName[] = {
    NC, NC, NC, NC, NC, p5, p6, p7, p8, p9,
    p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
    p20, p21, p22, p23, p24, p25, p26, p27, p28, p29,
    p30
};
"""


class AnalogIn(object):

    def __init__(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogIn *adc;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        adc = new AnalogIn(pinNumToName[((pPmInt_t)pn)->val]);

        /* Save the pointer to adc as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)adc, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read_u16(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogIn *adc;
        int32_t n;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        adc = (AnalogIn *)((pPmInt_t)pn)->val;

        /* Return input value on the stack */
        n = adc->read_u16();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    def read(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogIn *adc;
        float n;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        adc = (AnalogIn *)((pPmInt_t)pn)->val;

        /* Return input value on the stack */
        n = adc->read();
        retval = float_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


class AnalogOut(object):

    def __init__(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogOut *dac;


        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the object */
        dac = new AnalogOut(pinNumToName[((pPmInt_t)pn)->val]);

        /* Save the pointer to adc as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)dac, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def write_u16(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogOut *dac;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dac = (AnalogOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        dac->write_u16(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def write(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogOut *dac;
        float n;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_FLT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dac = (AnalogOut *)((pPmInt_t)pn)->val;

        /* Saturate and write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        n = ((pPmFloat_t)pn)->val;
        if (n < 0.0)
        {
            n = 0.0;
        }
        else if (n > 1.0)
        {
            n = 1.0;
        }
        dac->write(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        AnalogOut *dac;
        float n;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dac = (AnalogOut *)((pPmInt_t)pn)->val;

        /* Return output value on the stack */
        n = dac->read();
        retval = float_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


class DigitalIn(object):

    def __init__(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalIn *din;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        din = new DigitalIn(pinNumToName[((pPmInt_t)pn)->val]);

        /* Save the pointer to adc as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)din, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalIn *din;
        int32_t n;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        din = (DigitalIn *)((pPmInt_t)pn)->val;

        /* Return input value on the stack */
        n = din->read();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


class DigitalOut(object):

    def __init__(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalOut *dout;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        dout = new DigitalOut(pinNumToName[((pPmInt_t)pn)->val]);

        /* Save the pointer to adc as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)dout, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalOut *dout;
        int32_t n;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dout = (DigitalOut *)((pPmInt_t)pn)->val;

        /* Return input value on the stack */
        n = dout->read();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    def write(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalOut *dout;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dout = (DigitalOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        dout->write(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


class PwmOut(object):

    def __init__(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        pwm = new PwmOut(pinNumToName[((pPmInt_t)pn)->val]);

        /* Save the pointer to pwm as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)pwm, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        DigitalOut *dout;
        int32_t n;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        dout = (DigitalOut *)((pPmInt_t)pn)->val;

        /* Return input value on the stack */
        n = dout->read();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    def period(self, t):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->period(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def period_ms(self, t):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->period_ms(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def period_us(self, t):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->period_us(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def pulsewidth(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->pulsewidth(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def puslewidth_ms(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->pulsewidth_ms(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def pulsewidth_us(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        PwmOut *pwm;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        pwm = (PwmOut *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        pwm->pulsewidth_us(((pPmInt_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


class Serial(object):

    def __init__(self, tx, rx):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t ptx;
        pPmObj_t prx;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        Serial *ser;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 3)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        ptx = NATIVE_GET_LOCAL(1);
        prx = NATIVE_GET_LOCAL(2);
        if ((OBJ_GET_TYPE(ptx) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(prx) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        ser = new Serial(pinNumToName[((pPmInt_t)ptx)->val],
                         pinNumToName[((pPmInt_t)prx)->val]);

        /* Save the pointer to ser as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)ser, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def putc(self, s):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        Serial *ser;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_STR)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        ser = (Serial *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        ser->putc(((pPmString_t)pn)->val[0]);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def puts(self, s):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        Serial *ser;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_STR)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        ser = (Serial *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        ser->puts((const char *)((pPmString_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def getc(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        Serial *ser;
        int32_t n;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        ser = (Serial *)((pPmInt_t)pn)->val;

        /* Return char (as string) on the stack */
        n = ser->getc();
        retval = string_newFromChar((uint8_t)n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


class SPI(object):

    def __init__(self, mosi, miso, sclk):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pmosi;
        pPmObj_t pmiso;
        pPmObj_t psclk;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        SPI *spi;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 4)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pmosi = NATIVE_GET_LOCAL(1);
        pmiso = NATIVE_GET_LOCAL(2);
        psclk = NATIVE_GET_LOCAL(3);
        if ((OBJ_GET_TYPE(pmosi) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pmiso) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(psclk) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        spi = new SPI(pinNumToName[((pPmInt_t)pmosi)->val],
                      pinNumToName[((pPmInt_t)pmiso)->val],
                      pinNumToName[((pPmInt_t)psclk)->val]);

        /* Save the pointer to ser as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)spi, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def format(self, bits, mode=0):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pbits;
        pPmObj_t pmode;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        SPI *spi;

        /* Raise TypeError if wrong number of args */
        if ((NATIVE_GET_NUM_ARGS() < 2) || (NATIVE_GET_NUM_ARGS() > 3))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pbits = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pbits) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the mode arg if it exists */
        pmode = PM_ZERO;
        if (NATIVE_GET_NUM_ARGS() == 3)
        {
            pmode = NATIVE_GET_LOCAL(3);
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        spi = (SPI *)((pPmInt_t)pn)->val;

        /* Set format args */
        spi->format(((pPmInt_t)pbits)->val, ((pPmInt_t)pmode)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def frequency(self, hz):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t phz;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        SPI *spi;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        phz = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(phz) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        spi = (SPI *)((pPmInt_t)pn)->val;

        /* Set frequency */
        spi->frequency(((pPmInt_t)phz)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def write(self, v):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pv;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        SPI *spi;
        int32_t r;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pv = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pv) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        spi = (SPI *)((pPmInt_t)pn)->val;

        /* Write the value and return the response */
        r = spi->write(((pPmInt_t)pv)->val);
        retval = int_new(r, &pn);
        NATIVE_SET_TOS(pn);
        return retval;
        """
        pass


class I2C(object):

    def __init__(self, sda, scl):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t psda;
        pPmObj_t pscl;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        I2C *i2c;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 3)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        psda = NATIVE_GET_LOCAL(1);
        pscl = NATIVE_GET_LOCAL(2);
        if ((OBJ_GET_TYPE(psda) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pscl) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Instantiate the C++ object */
        i2c = new I2C(pinNumToName[((pPmInt_t)psda)->val],
                      pinNumToName[((pPmInt_t)pscl)->val]);

        /* Save the pointer to ser as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)i2c, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def frequency(self, hz):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t phz;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        I2C *i2c;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        phz = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(phz) != OBJ_TYPE_INT)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        i2c = (I2C *)((pPmInt_t)pn)->val;

        /* Set frequency */
        i2c->frequency(((pPmInt_t)phz)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def read(self, addr, data, length):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t paddr;
        pPmObj_t pdata;
        pPmObj_t plen;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        I2C *i2c;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 4)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        paddr = NATIVE_GET_LOCAL(1);
        pdata = NATIVE_GET_LOCAL(2);
        plen = NATIVE_GET_LOCAL(3);
        if ((OBJ_GET_TYPE(paddr) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pdata) != OBJ_TYPE_STR)
            || (OBJ_GET_TYPE(plen) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        i2c = (I2C *)((pPmInt_t)pn)->val;

        /* Read the bytes into the string */
        /* WARNING: Changing the bytes of a string object is BAD. */
        i2c->read(((pPmInt_t)paddr)->val,
                  (char *)((pPmString_t)pdata)->val,
                  ((pPmInt_t)plen)->val);
        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def write(self, addr, data, length):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t paddr;
        pPmObj_t pdata;
        pPmObj_t plen;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        I2C *i2c;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 4)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        paddr = NATIVE_GET_LOCAL(1);
        pdata = NATIVE_GET_LOCAL(2);
        plen = NATIVE_GET_LOCAL(3);
        if ((OBJ_GET_TYPE(paddr) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pdata) != OBJ_TYPE_STR)
            || (OBJ_GET_TYPE(plen) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        i2c = (I2C *)((pPmInt_t)pn)->val;

        /* Write the value and return the response */
        i2c->write(((pPmInt_t)paddr)->val,
                   (char *)((pPmString_t)pdata)->val,
                   ((pPmInt_t)plen)->val);
        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


class TextLCD(object):

    def __init__(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        TextLCD *lcd;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Instantiate the C++ object */
        lcd = new TextLCD(pinNumToName[24],
                          pinNumToName[25],
                          pinNumToName[26],
                          pinNumToName[27],
                          pinNumToName[28],
                          pinNumToName[29],
                          pinNumToName[30]);

        /* Save the pointer to pwm as an inaccessible attribute */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = int_new((uint32_t)lcd, &pn);
        PM_RETURN_IF_ERROR(retval);
        retval = dict_setItem(pattrs, PM_NONE, pn);
        PM_RETURN_IF_ERROR(retval);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def printf(self, n):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        TextLCD *lcd;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pn = NATIVE_GET_LOCAL(1);
        if (OBJ_GET_TYPE(pn) != OBJ_TYPE_STR)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        lcd = (TextLCD *)((pPmInt_t)pn)->val;

        /* Write value to DAC */
        pn = NATIVE_GET_LOCAL(1);
        lcd->printf((char const *)((pPmString_t)pn)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def cls(self,):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        TextLCD *lcd;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 1)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        lcd = (TextLCD *)((pPmInt_t)pn)->val;

        /* Clear LCD */
        lcd->cls();

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def locate(self, column, row):
        """__NATIVE__
        pPmObj_t pself;
        pPmObj_t pn;
        pPmObj_t pc;
        pPmObj_t pr;
        pPmObj_t pattrs;
        PmReturn_t retval = PM_RET_OK;
        TextLCD *lcd;

        /* Raise TypeError if wrong number of args */
        if (NATIVE_GET_NUM_ARGS() != 3)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }
        pself = NATIVE_GET_LOCAL(0);

        /* Raise TypeError if arg is not the right type */
        pc = NATIVE_GET_LOCAL(1);
        pr = NATIVE_GET_LOCAL(2);
        if ((OBJ_GET_TYPE(pc) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pr) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the the C++ instance */
        pattrs = (pPmObj_t)((pPmInstance_t)pself)->cli_attrs;
        retval = dict_getItem(pattrs, PM_NONE, &pn);
        PM_RETURN_IF_ERROR(retval);
        lcd = (TextLCD *)((pPmInt_t)pn)->val;

        /* Set the location of the LCD's cursor */
        lcd->locate(((pPmInt_t)pc)->val, ((pPmInt_t)pr)->val);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass




def set_led(led, val):
    """__NATIVE__
    pPmObj_t pled;
    pPmObj_t pval;
    int32_t nled;
    int32_t nval;
    PmReturn_t retval = PM_RET_OK;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() > 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* If arg is not an int, raise TypeError */
    pled = NATIVE_GET_LOCAL(0);
    pval = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(pled) != OBJ_TYPE_INT)
        || (OBJ_GET_TYPE(pval) != OBJ_TYPE_INT))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Get int value from the arg */
    nled = ((pPmInt_t)pled)->val;
    nval = ((pPmInt_t)pval)->val;

    /* Set the LED to the given value */
    switch (nled)
    {
        case 1: led1 = nval; break;
        case 2: led2 = nval; break;
        case 3: led3 = nval; break;
        case 4: led4 = nval; break;
    }

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass

# :mode=c:
