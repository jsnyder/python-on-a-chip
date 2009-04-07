"""__NATIVE__
#include "mbed.h"
#include "TextLCD.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
AnalogIn *adc;
AnalogOut *dac;
DigitalIn *din;
DigitalOut *dout;
PwmOut *pwm;
TextLCD *lcd;
"""


# Imitation of a AnalogIn class
def AnalogIn(pin):

    def _adc_init(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Instantiate the object */
        n = ((pPmInt_t)pn)->val;
        adc = new AnalogIn(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def _adc_read_u16():
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 0)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Return input value on the stack */
        n = adc->read_u16();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _adc_init(pin)
    AnalogIn.read_u16 = _adc_read_u16

    return AnalogIn


# Imitation of a AnalogOut class
def AnalogOut(pin):

    def _dac_init(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Instantiate the object */
        n = ((pPmInt_t)pn)->val;
        dac = new AnalogOut(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def _dac_write_u16(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Write value to output */
        n = ((pPmInt_t)pn)->val;
        dac->write_u16(n);

        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _dac_init(pin)
    AnalogOut.write = _dac_write_u16

    return AnalogOut


# Imitation of a DigitalIn class
def DigitalIn(pin):

    def _din_init(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Instantiate the object */
        n = ((pPmInt_t)pn)->val;
        din = new DigitalIn(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def _din_read():
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 0)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Return input value on the stack */
        n = din->read();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _din_init(pin)
    DigitalIn.read = _din_read

    return DigitalIn


# Imitation of a DigitalOut class
def DigitalOut(pin):

    def _dout_init(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Instantiate the object */
        n = ((pPmInt_t)pn)->val;
        dout = new DigitalOut(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def _dout_read():
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 0)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Return input value on the stack */
        n = dout->read();
        retval = int_new(n, &pn);
        NATIVE_SET_TOS(pn);

        return retval;
        """
        pass


    def _dout_write(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Write value to output */
        n = ((pPmInt_t)pn)->val;
        dout->write(n);

        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _dout_init(pin)
    DigitalOut.read = _dout_read
    DigitalOut.write = _dout_write

    return DigitalOut


# Imitation of a PwmOut class
def PwmOut(pin):

    def _pwm_init(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Instantiate the object */
        n = ((pPmInt_t)pn)->val;
        pwm = new PwmOut(n);

        NATIVE_SET_TOS(PM_NONE);
        return retval;
        """
        pass


    def _pwm_period_us(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Write value to output */
        n = ((pPmInt_t)pn)->val;
        pwm->period_us(n);

        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    def _pwm_pulsewidth_us(n):
        """__NATIVE__
        pPmObj_t pn;
        int32_t n;
        PmReturn_t retval = PM_RET_OK;

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

        /* Write value to output */
        n = ((pPmInt_t)pn)->val;
        pwm->pulsewidth_us(n);

        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _pwm_init(pin)
    PwmOut.period_us = _pwm_period_us
    PwmOut.pulsewidth_us = _pwm_pulsewidth_us

    return PwmOut


# Imitation of a TextLCD class
def TextLCD():

    def _lcd_init():
        """__NATIVE__
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 0)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        lcd = new TextLCD(24, 25, 26, 27, 28, 29, 30);

        /* Return none obj on stack */
        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    def _lcd_printf(s):
        """__NATIVE__
        pPmObj_t ps = C_NULL;
        uint8_t *s = C_NULL;
        PmReturn_t retval = PM_RET_OK;

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

        /* Print the string on the lcd */
        lcd->printf((char *)s);

        /* Return none obj on stack */
        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    def _lcd_cls():
        """__NATIVE__
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 0)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Clear the lcd */
        lcd->cls();

        /* Return none obj on stack */
        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    def _lcd_locate(column, row):
        """__NATIVE__
        pPmObj_t pc = C_NULL;
        pPmObj_t pr = C_NULL;
        int32_t nc;
        int32_t nr;
        PmReturn_t retval = PM_RET_OK;

        /* If wrong number of args, throw type exception */
        if (NATIVE_GET_NUM_ARGS() != 2)
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get the arg, throw type exception if needed */
        pc = NATIVE_GET_LOCAL(0);
        pr = NATIVE_GET_LOCAL(1);
        if ((OBJ_GET_TYPE(pc) != OBJ_TYPE_INT)
            || (OBJ_GET_TYPE(pr) != OBJ_TYPE_INT))
        {
            PM_RAISE(retval, PM_RET_EX_TYPE);
            return retval;
        }

        /* Get a pointer to the values */
        nc = ((pPmInt_t)pc)->val;
        nr = ((pPmInt_t)pr)->val;

        /* Print the string on the lcd */
        lcd->locate(nc, nr);

        /* Return none obj on stack */
        NATIVE_SET_TOS(PM_NONE);

        return retval;
        """
        pass


    # Run initializer and set attrs (methods)
    _lcd_init()
    TextLCD.printf = _lcd_printf
    TextLCD.cls = _lcd_cls
    TextLCD.locate = _lcd_locate

    return TextLCD



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
