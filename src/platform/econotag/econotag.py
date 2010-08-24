# This file is Copyright 2010 Dean Hall.
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
#include "mc1322x.h"
#include "board.h"

#ifndef HAVE_BYTEARRAY
#error HAVE_BYTEARRAY must be defined for the Econotag packet implementation
#endif
"""


def gpio_func_sel(gpio, mode):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pgpio, pmode;
    int32_t gpio, mode;
    uint32_t mask;
    uint8_t shift;
    volatile uint32_t *func_sel_regs[] = {GPIO_FUNC_SEL0, GPIO_FUNC_SEL1,
                                          GPIO_FUNC_SEL2, GPIO_FUNC_SEL3};
    volatile uint32_t *func_sel_reg;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if args are not ints */
    pgpio = NATIVE_GET_LOCAL(0);
    pmode = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(pgpio) != OBJ_TYPE_INT)
        || (OBJ_GET_TYPE(pmode) != OBJ_TYPE_INT))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise ValueError if either value is out of range */
    gpio = ((pPmInt_t)pgpio)->val;
    mode = ((pPmInt_t)pmode)->val;
    if ((gpio < 0) || (gpio > 63) || (mode < 0) || (mode > 3))
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    /* Choose the register and calculate the shift needed for the gpio */
    func_sel_reg = func_sel_regs[gpio >> 4];
    shift = (gpio & 0x0F) << 1;
    mask = 0x03 << shift;

    /* Clear the old mode, apply the new mode */
    *func_sel_reg &= ~mask;
    *func_sel_reg |= (mode << shift);

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def gpio_pad_dir(lo32, hi32):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t plo, phi;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if args are not ints */
    plo = NATIVE_GET_LOCAL(0);
    phi = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(plo) != OBJ_TYPE_INT)
        || (OBJ_GET_TYPE(phi) != OBJ_TYPE_INT))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    *GPIO_PAD_DIR0 = ((pPmInt_t)plo)->val;
    *GPIO_PAD_DIR1 = ((pPmInt_t)phi)->val;
    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def gpio_data(lo32, hi32):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t plo, phi;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if args are not ints */
    plo = NATIVE_GET_LOCAL(0);
    phi = NATIVE_GET_LOCAL(1);
    if ((OBJ_GET_TYPE(plo) != OBJ_TYPE_INT)
        || (OBJ_GET_TYPE(phi) != OBJ_TYPE_INT))
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    *GPIO_DATA0 = ((pPmInt_t)plo)->val;
    *GPIO_DATA1 = ((pPmInt_t)phi)->val;
    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def gpio_data_get_hi():
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pn;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

	retval = int_new(*GPIO_DATA1, &pn);
    NATIVE_SET_TOS(pn);
    return retval;
    """
    pass


def gpio_data_get_lo():
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pn;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

	retval = int_new(*GPIO_DATA0, &pn);
    NATIVE_SET_TOS(pn);
    return retval;
    """
    pass


def set_channel(n):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pn;
    uint8_t n;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not an int */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise ValueError if arg is not within 0..15 inclusive */
    n = (uint8_t)(((pPmInt_t)pn)->val);
    if (n >= (uint8_t)16)
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    maca_off();
    set_channel(n);
    maca_on();

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def set_power(n):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pn;
    uint8_t n;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not an int */
    pn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(pn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise ValueError if arg is not within 0..18 inclusive */
    n = (uint8_t)(((pPmInt_t)pn)->val);
    if (n > (uint8_t)18)
    {
        PM_RAISE(retval, PM_RET_EX_VAL);
        return retval;
    }

    maca_off();
    set_power(n);
    maca_on();

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def check_maca():
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    check_maca();

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def tx_packet(p):
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
	volatile packet_t *p;
	pPmObj_t ppkt;
	pPmBytearray_t pba;
	pPmString_t pstr;
	pPmInt_t pn;

    /* Raise TypeError if wrong number of args */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    ppkt = NATIVE_GET_LOCAL(0);

    /* If object is an instance, get the thing it is containing */
    if (OBJ_GET_TYPE(ppkt) == OBJ_TYPE_CLI)
    {
        retval = dict_getItem((pPmObj_t)((pPmInstance_t)ppkt)->cli_attrs,
                              PM_NONE,
                              (pPmObj_t *)&pba);
        PM_RETURN_IF_ERROR(retval);
        ppkt = (pPmObj_t)pba;
    }

    /* Raise TypeError if arg is not a string or bytearray */
    if ((OBJ_GET_TYPE(ppkt) != OBJ_TYPE_STR)
        && (OBJ_GET_TYPE(ppkt) != OBJ_TYPE_BYA))
    {
        NATIVE_SET_TOS(PM_NONE);
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    p = get_free_packet();
    if (!p)
    {
        /* TODO: raise an IoError (when VM can catch exceptions) */
        NATIVE_SET_TOS(PM_NONE);
        return retval;
    }

    /* Copy bytes from string arg to packet */
    p->offset = 0;
    if (OBJ_GET_TYPE(ppkt) == OBJ_TYPE_STR)
    {
        pstr = (pPmString_t)ppkt;
        sli_memcpy((unsigned char *)&(p->data[0]),
                   (unsigned char *)&(pstr->val[0]),
                   (unsigned int)pstr->length);
        p->length = pstr->length;
    }

    /* Copy bytes from bytearray arg to packet */
    else
    {
        pba = (pPmBytearray_t)ppkt;
        sli_memcpy((unsigned char *)&(p->data[0]),
                   (unsigned char *)&(pba->val->val[0]),
                   (unsigned int)pba->length);
        p->length = pba->length;
    }

    retval = int_new(p->length, &pn);
    NATIVE_SET_TOS(pn);

    tx_packet(p);

    return retval;
    """
    pass


def rx_packet():
    """__NATIVE__
    PmReturn_t retval = PM_RET_OK;
    volatile packet_t *p;
    pPmBytearray_t pba;
    pPmInt_t pn;
    uint8_t objid, objid2;
    pPmObj_t pbaclass;
    pPmObj_t pcli;

    p = rx_packet();
    if (!p)
    {
        NATIVE_SET_TOS(PM_NONE);
        return retval;
    }

    /* Allocate a bytearray */
    retval = int_new(p->length, (pPmObj_t *)&pn);
    if (retval != PM_RET_OK)
    {
        free_packet(p);
        return retval;
    }

    heap_gcPushTempRoot((pPmObj_t)pn, &objid);
    retval = bytearray_new(pn, (pPmObj_t *)&pba);
    heap_gcPopTempRoot(objid);
    if (retval != PM_RET_OK)
    {
        free_packet(p);
        return retval;
    }
    heap_freeChunk(pn);

    /* Copy packet payload to bytearray */
    sli_memcpy((unsigned char *)&(pba->val->val[0]),
               (unsigned char *)&(p->data[p->offset]),
               (unsigned int)p->length);
    free_packet(p);

    /* Create an instance of bytearray to hold the bytearray struct */
    retval = dict_getItem(PM_PBUILTINS, PM_BYTEARRAY_STR, &pbaclass);
    PM_RETURN_IF_ERROR(retval);
    heap_gcPushTempRoot((pPmObj_t)pba, &objid);
    retval = class_instantiate(pbaclass, &pcli);
    if (retval != PM_RET_OK)
    {
        heap_gcPopTempRoot(objid);
        return retval;
    }

    /* Store bytearray struct in the instance's None attribute */
    heap_gcPushTempRoot(pcli, &objid2);
    retval = dict_setItem((pPmObj_t)((pPmInstance_t)pcli)->cli_attrs,
                          PM_NONE,
                          (pPmObj_t)pba);
    heap_gcPopTempRoot(objid);

    NATIVE_SET_TOS(pcli);
    return retval;
    """
    pass


def random():
    """__NATIVE__
    PmReturn_t retval;
    pPmObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    retval = int_new(*MACA_RANDOM, &pr);
    NATIVE_SET_TOS(pr);
    return retval;
    """
    pass


# :mode=c:
