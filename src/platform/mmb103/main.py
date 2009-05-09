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
# This is a sample application that calls native functions.
#


"""__NATIVE__
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "libmmb103.h"
"""


#
# Do this at the very start to show that PyMite is running
#
if False:
    import sys
    print sys.heap() # (1762,3328)

    s = "It's alive!"
    print s

    import mmb
    mmb.lcd_print("PyMite on MMB103")

    while True:
        mmb.lcd_set_line(1)
        if mmb.dip_get(1):
            mmb.lcd_print("dip1 = ON ")
        else:
            mmb.lcd_print("dip1 = OFF")
        mmb.sleepms(50)
        mmb.sleepms(50)
        mmb.sleepms(50)
        mmb.sleepms(50)
        mmb.sleepms(50)


#
# Duplicating ipm functions here so I do not have to import ipm (spend heap)
#

#
# Receives an image over the platform's standard connection.
# Returns the image in a string object
#
def _getImg():
    """__NATIVE__
    PmReturn_t retval;
    uint8_t imgType;
    uint16_t imgSize;
    uint8_t *pchunk;
    pPmString_t pimg;
    uint16_t i;
    uint8_t b;

    /* Get the image type (skip any trash at beginning) */
    do
    {
        retval = plat_getByte(&imgType);
        PM_RETURN_IF_ERROR(retval);
    }
    while (imgType != OBJ_TYPE_CIM);

    /* Quit if a code image type was not received */
    if (imgType != OBJ_TYPE_CIM)
    {
        PM_RAISE(retval, PM_RET_EX_STOP);
        return retval;
    }

    /* Get the image size (little endien) */
    retval = plat_getByte(&b);
    PM_RETURN_IF_ERROR(retval);
    imgSize = b;
    retval = plat_getByte(&b);
    PM_RETURN_IF_ERROR(retval);
    imgSize |= (b << 8);

    /* Get space for String obj */
    retval = heap_getChunk(sizeof(PmString_t) + imgSize, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pimg = (pPmString_t)pchunk;

    /* Set the string object's fields */
    OBJ_SET_TYPE(pimg, OBJ_TYPE_STR);
    pimg->length = imgSize;

    /* Start the image with the bytes that have already been received */
    i = 0;
    pimg->val[i++] = imgType;
    pimg->val[i++] = imgSize & 0xFF;
    pimg->val[i++] = (imgSize >> 8) & 0xFF;

    /* Get the remaining bytes in the image */
    for(; i < imgSize; i++)
    {
        retval = plat_getByte(&b);
        PM_RETURN_IF_ERROR(retval);

        pimg->val[i] = b;
    }

    /* Return the image as a string object on the stack */
    NATIVE_SET_TOS((pPmObj_t)pimg);
    return retval;
    """
    pass


#
# Runs the target device-side interactive session.
#
#def ipm():
g = {}
while 1:
    # Wait for a code image, make a code object from it
    # and evaluate the code object.
    rv = eval(Co(_getImg()), g)

    # Send a byte to indicate completion of evaluation
    print '\x04',



# :mode=c:
