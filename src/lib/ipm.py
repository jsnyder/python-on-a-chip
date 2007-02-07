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
# Provides PyMite's interactive interface for the target.
#
# LOG
# ---
#
# 2006/12/30    Created.
#


#### FUNCS

#
# Receives an image over the platform's standard connection.
# Returns the image in a string object
#
def _getImg():
    """__NATIVE__
    PmReturn_t retval;
    uint8_t imgType;
    uint8_t imgSize;
    uint8_t *pchunk;
    pPmString_t pimg;
    uint8_t i;
    uint8_t b;

    /* Get the image type */
    retval = plat_getByte(&imgType);
    PM_RETURN_IF_ERROR(retval);

    /* Quit if a code image type was not received */
    if (imgType != OBJ_TYPE_CIM)
    {
        PM_RAISE(retval, PM_RET_EX_STOP);
        return retval;
    }

    /* Get the image size */
    retval = plat_getByte(&imgSize);
    PM_RETURN_IF_ERROR(retval);

    /* Get space for String obj */
    retval = heap_getChunk(sizeof(PmString_t) + imgSize, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pimg = (pPmString_t)pchunk;

    /* Set the string object's fields */
    OBJ_SET_TYPE(*pimg, OBJ_TYPE_STR);
    pimg->length = imgSize;

    /* Start the image with the bytes that have already been received */
    i = 0;
    pimg->val[i++] = imgType;
    pimg->val[i++] = imgSize;

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
import sys
def ipm():
    while 1:
        # Wait for a code image, make a code object from it
        # and evaluate the code object.
        rv = eval(Co(_getImg()))

        # Send a byte to indicate completion of evaluation
        sys.putb(0x04)

#:mode=c:
