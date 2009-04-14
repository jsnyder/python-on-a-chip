#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Provides PyMite's interactive interface for the target.
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
    pPmCodeImgObj_t pimg;
    uint16_t i;
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

    /* Get the image size (little endien) */
    retval = plat_getByte(&b);
    PM_RETURN_IF_ERROR(retval);
    imgSize = b;
    retval = plat_getByte(&b);
    PM_RETURN_IF_ERROR(retval);
    imgSize |= (b << 8);

    /* Get space for CodeImgObj */
    retval = heap_getChunk(sizeof(PmCodeImgObj_t) + imgSize, &pchunk);
    PM_RETURN_IF_ERROR(retval);
    pimg = (pPmCodeImgObj_t)pchunk;
    OBJ_SET_TYPE(pimg, OBJ_TYPE_CIO);

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
def ipm(g={}):
    while 1:
        # Wait for a code image, make a code object from it
        # and evaluate the code object.
        # #180: One-liner turned into 3 so that objects get bound to roots
        s = _getImg()
        co = Co(s)
        rv = eval(co, g)

        # Send a byte to indicate completion of evaluation
        print '\x04',

# :mode=c:
