# This file contains wrappers for the basic
# functions in maapi.

# If a function or constant is missing, look in ma_gen.py, it
# might be there.

"""__NATIVE__
#include <ma.h>

#define POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid) \
    do \
    { \
        if ((retval) != PM_RET_OK) \
        { \
            heap_gcPopTempRoot((objid)); \
            return (retval); \
        } \
    } \
    while (0)

"""

TRANS_NONE = 0
TRANS_ROT90 = 5
TRANS_ROT180 = 3
TRANS_ROT270 = 6
TRANS_MIRROR = 2
TRANS_MIRROR_ROT90 = 7
TRANS_MIRROR_ROT180 = 1
TRANS_MIRROR_ROT270 = 4

EVENT_TYPE_CLOSE = 1
EVENT_TYPE_KEY_PRESSED = 2
EVENT_TYPE_KEY_RELEASED = 3
EVENT_TYPE_POINTER_PRESSED = 8
EVENT_TYPE_POINTER_RELEASED = 9
EVENT_TYPE_POINTER_DRAGGED = 10

MAK_0 = 48
MAK_1 = 49
MAK_2 = 50
MAK_3 = 51
MAK_4 = 52
MAK_5 = 53
MAK_6 = 54
MAK_7 = 55
MAK_8 = 56
MAK_9 = 57
MAK_HASH = 35
MAK_STAR = 42

MAK_UP = 273
MAK_DOWN = 274
MAK_RIGHT = 275
MAK_LEFT = 276
MAK_FIRE = 284
MAK_SOFTLEFT = 285
MAK_SOFTRIGHT = 286

MAKB_LEFT = 0x00001
MAKB_UP = 0x00002
MAKB_RIGHT = 0x00004
MAKB_DOWN = 0x00008
MAKB_FIRE = 0x00010
MAKB_SOFTLEFT = 0x00020
MAKB_SOFTRIGHT = 0x00040
MAKB_0 = 0x00080
MAKB_1 = 0x00100
MAKB_2 = 0x00200
MAKB_3 = 0x00400
MAKB_4 = 0x00800
MAKB_5 = 0x01000
MAKB_6 = 0x02000
MAKB_7 = 0x04000
MAKB_8 = 0x08000
MAKB_9 = 0x10000
MAKB_ASTERISK = 0x20000
MAKB_STAR = 0x20000
MAKB_HASH = 0x40000
MAKB_POUND = 0x40000
MAKB_GRID = 0x40000
MAKB_CLEAR = 0x80000

def sin(x):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double sin(double x); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double x;
    pPmObj_t p_x = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_x = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_x) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    x = (double)(((pPmFloat_t)p_x)->val);

    func_retval = sin(x);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSetColor(rgb):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maSetColor(int rgb); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int rgb;
    pPmObj_t p_rgb = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_rgb = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_rgb) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    rgb = ((pPmInt_t)p_rgb)->val;

    func_retval = maSetColor(rgb);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSetClipRect(left, top, width, height):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maSetClipRect(int left, int top, int width, int height); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int left;
    pPmObj_t p_left = C_NULL;

    int top;
    pPmObj_t p_top = C_NULL;

    int width;
    pPmObj_t p_width = C_NULL;

    int height;
    pPmObj_t p_height = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_left = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_left) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_top = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_top) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_width = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_width) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_height = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_height) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    left = ((pPmInt_t)p_left)->val;
    top = ((pPmInt_t)p_top)->val;
    width = ((pPmInt_t)p_width)->val;
    height = ((pPmInt_t)p_height)->val;

    maSetClipRect(left, top, width, height);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maGetClipRect():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maGetClipRect(MARect* out); */

    PmReturn_t retval = PM_RET_OK;

    MARect rect;
    pPmObj_t pn = C_NULL;
    pPmObj_t r_ptuple = C_NULL;
    uint8_t objid;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    maGetClipRect(&rect);
    retval = tuple_new(4, &r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    heap_gcPushTempRoot(r_ptuple, &objid);
    retval = int_new(rect.left, &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[0] = pn;
    retval = int_new(rect.top, &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[1] = pn;
    retval = int_new(rect.width, &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[2] = pn;
    retval = int_new(rect.height, &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[3] = pn;
    heap_gcPopTempRoot(objid);

    NATIVE_SET_TOS(r_ptuple);

    return retval;
    """
    pass


def maPlot(posX, posY):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maPlot(int posX, int posY); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int posX;
    pPmObj_t p_posX = C_NULL;

    int posY;
    pPmObj_t p_posY = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_posX = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_posX) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_posY = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_posY) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    posX = ((pPmInt_t)p_posX)->val;
    posY = ((pPmInt_t)p_posY)->val;

    maPlot(posX, posY);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maLine(startX, startY, endX, endY):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maLine(int startX, int startY, int endX, int endY); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int startX;
    pPmObj_t p_startX = C_NULL;

    int startY;
    pPmObj_t p_startY = C_NULL;

    int endX;
    pPmObj_t p_endX = C_NULL;

    int endY;
    pPmObj_t p_endY = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_startX = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_startX) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_startY = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_startY) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_endX = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_endX) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_endY = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_endY) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    startX = ((pPmInt_t)p_startX)->val;
    startY = ((pPmInt_t)p_startY)->val;
    endX = ((pPmInt_t)p_endX)->val;
    endY = ((pPmInt_t)p_endY)->val;

    maLine(startX, startY, endX, endY);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maFillRect(left, top, width, height):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maFillRect(int left, int top, int width, int height); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int left;
    pPmObj_t p_left = C_NULL;

    int top;
    pPmObj_t p_top = C_NULL;

    int width;
    pPmObj_t p_width = C_NULL;

    int height;
    pPmObj_t p_height = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_left = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_left) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_top = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_top) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_width = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_width) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_height = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_height) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    left = ((pPmInt_t)p_left)->val;
    top = ((pPmInt_t)p_top)->val;
    width = ((pPmInt_t)p_width)->val;
    height = ((pPmInt_t)p_height)->val;

    maFillRect(left, top, width, height);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass

# No wrapper for
#void maFillTriangleStrip(const MAPoint2d* points, int count);

# No wrapper for
#void maFillTriangleFan(const MAPoint2d* points, int count);


def maGetTextSize(s):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetTextSize(const char* str); */

    PmReturn_t retval = PM_RET_OK;

    int extent;
    pPmObj_t pn = C_NULL;
    pPmObj_t r_ptuple = C_NULL;
    uint8_t objid;

    const char* str;
    pPmObj_t p_str = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_str = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_str) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    str = (char const *)&(((pPmString_t)p_str)->val);

    extent = maGetTextSize(str);
    retval = tuple_new(2, &r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    heap_gcPushTempRoot(r_ptuple, &objid);
    retval = int_new(EXTENT_X(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[0] = pn;
    retval = int_new(EXTENT_Y(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[1] = pn;
    heap_gcPopTempRoot(objid);

    NATIVE_SET_TOS(r_ptuple);

    return retval;
    """
    pass


def maDrawText(left, top, s):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maDrawText(int left, int top, const char* str); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int left;
    pPmObj_t p_left = C_NULL;

    int top;
    pPmObj_t p_top = C_NULL;

    const char* str;
    pPmObj_t p_str = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 3)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_left = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_left) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_top = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_top) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_str = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_str) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    left = ((pPmInt_t)p_left)->val;
    top = ((pPmInt_t)p_top)->val;
    str = (char const *)&(((pPmString_t)p_str)->val);

    maDrawText(left, top, str);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maUpdateScreen():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maUpdateScreen(void); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    maUpdateScreen();
    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass


def maGetScrSize():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetScrSize(void); */

    PmReturn_t retval = PM_RET_OK;

    int extent;
    pPmObj_t pn = C_NULL;
    pPmObj_t r_ptuple = C_NULL;
    uint8_t objid;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    extent = maGetScrSize();
    retval = tuple_new(2, &r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    heap_gcPushTempRoot(r_ptuple, &objid);
    retval = int_new(EXTENT_X(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[0] = pn;
    retval = int_new(EXTENT_Y(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[1] = pn;
    heap_gcPopTempRoot(objid);

    NATIVE_SET_TOS(r_ptuple);

    return retval;
    """
    pass


def maDrawImage(image, left, top):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maDrawImage(MAHandle image, int left, int top); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int image;
    pPmObj_t p_image = C_NULL;

    int left;
    pPmObj_t p_left = C_NULL;

    int top;
    pPmObj_t p_top = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 3)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_image = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_image) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_left = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_left) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_top = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_top) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    image = ((pPmInt_t)p_image)->val;
    left = ((pPmInt_t)p_left)->val;
    top = ((pPmInt_t)p_top)->val;

    maDrawImage(image, left, top);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


# No wrapper for
#void maDrawRGB(const MAPoint2d* dstPoint, const void* src, const MARect* srcRect, int scanlength);

def maDrawImageRegion(image, srcRect, dstPoint, transformMode):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maDrawImageRegion(MAHandle image, const MARect* srcRect, 
         const MAPoint2d* dstPoint, int transformMode); */

    PmReturn_t retval = PM_RET_OK;

    int image;
    pPmObj_t p_image = C_NULL;

    pPmObj_t p_srcRect = C_NULL;
    MARect srcRect;
    //int srcLeft;
    //int srcTop;
    //int srcRight;
    //int srcBottom;

    pPmObj_t p_dstPoint = C_NULL;
    MAPoint2d dstPoint;
    //int srcLeft;
    //int srcTop;

    pPmObj_t p_transformMode = C_NULL;
    int transformMode;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_image = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_image) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_srcRect = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_srcRect) != OBJ_TYPE_TUP ||
        ((pPmTuple_t)p_srcRect)->length != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_dstPoint = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_dstPoint) != OBJ_TYPE_TUP ||
        ((pPmTuple_t)p_dstPoint)->length != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_transformMode = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_transformMode) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }
    image = ((pPmInt_t)p_image)->val;
    
    srcRect.left = ((pPmInt_t)(((pPmTuple_t)p_srcRect)->val[0]))->val;
    srcRect.top = ((pPmInt_t)(((pPmTuple_t)p_srcRect)->val[1]))->val;
    srcRect.width = ((pPmInt_t)(((pPmTuple_t)p_srcRect)->val[2]))->val;
    srcRect.height = ((pPmInt_t)(((pPmTuple_t)p_srcRect)->val[3]))->val;

    dstPoint.x = ((pPmInt_t)(((pPmTuple_t)p_dstPoint)->val[0]))->val;
    dstPoint.y = ((pPmInt_t)(((pPmTuple_t)p_dstPoint)->val[1]))->val;

    transformMode = ((pPmInt_t)p_transformMode)->val;

    maDrawImageRegion(image, &srcRect, &dstPoint, transformMode);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maGetImageSize(image):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetImageSize(MAHandle image); */

    PmReturn_t retval = PM_RET_OK;

    int extent;
    pPmObj_t pn = C_NULL;
    pPmObj_t r_ptuple = C_NULL;
    uint8_t objid;

    int image;
    pPmObj_t p_image = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_image = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_image) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    image = ((pPmInt_t)p_image)->val;

    extent = maGetImageSize(image);

    retval = tuple_new(2, &r_ptuple);
    PM_RETURN_IF_ERROR(retval);
    heap_gcPushTempRoot(r_ptuple, &objid);
    retval = int_new(EXTENT_X(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[0] = pn;
    retval = int_new(EXTENT_Y(extent), &pn);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[1] = pn;
    heap_gcPopTempRoot(objid);

    NATIVE_SET_TOS(r_ptuple);

    return retval;
    """
    pass


# No wrapper for
#void maGetImageData(MAHandle image, void* dst, const MARect* srcRect, int scanlength);

#MAHandle maSetDrawTarget(MAHandle image);
#int maFindLabel(const char* name);
#int maCreateImageFromData(MAHandle placeholder, MAHandle data, int offset, int size);

# No wrapper for
#int maCreateImageRaw(MAHandle placeholder, const void* src, MAExtent size, int alpha);

#int maCreateDrawableImage(MAHandle placeholder, int width, int height);
#int maCreateData(MAHandle placeholder, int size);

#MAHandle maCreatePlaceholder(void);
#void maDestroyObject(MAHandle handle);
#int maGetDataSize(MAHandle data);

# No wrapper for
#void maReadData(MAHandle data, void* dst, int offset, int size);

# No wrapper for
#void maWriteData(MAHandle data, const void* src, int offset, int size);

# No wrapper for
#void maCopyData(const MACopyData* params);

#MAHandle maOpenStore(const char* name, int flags);
#int maWriteStore(MAHandle store, MAHandle data);
#int maReadStore(MAHandle store, MAHandle placeholder);
#void maCloseStore(MAHandle store, int _remove);
#MAHandle maConnect(const char* url);
#void maConnClose(MAHandle conn);

# No wrapper for
#void maConnRead(MAHandle conn, void* dst, int size);

# No wrapper for
#void maConnWrite(MAHandle conn, const void* src, int size);

#void maConnReadToData(MAHandle conn, MAHandle data, int offset, int size);
#void maConnWriteFromData(MAHandle conn, MAHandle data, int offset, int size);

# No wrapper for
#int maConnGetAddr(MAHandle conn, MAConnAddr* addr);

#MAHandle maHttpCreate(const char* url, int method);
#void maHttpSetRequestHeader(MAHandle conn, const char* key, const char* value);

# No wrapper for
#int maHttpGetResponseHeader(MAHandle conn, const char* key, char* buffer, int bufSize);

#void maHttpFinish(MAHandle conn);
#int maLoadResources(MAHandle data);
#void maLoadProgram(MAHandle data, int reload);


def maGetKeys():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maGetKeys(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maGetKeys();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

def _maGetEvent():
    """__NATIVE__
    PmReturn_t retval;
    MAEvent event;
    int type;
    int v1;
    int v2;
    pPmObj_t p1;
    pPmObj_t p2;
    pPmObj_t p3;
    pPmObj_t r_ptuple;
    uint8_t objid;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    if (!maGetEvent(&event)) {
        NATIVE_SET_TOS(PM_NONE);
        return retval;
    }

    type = event.type;
    if (type == EVENT_TYPE_KEY_PRESSED ||
        type == EVENT_TYPE_KEY_RELEASED) {
        v1 = event.key;
        v2 = event.nativeKey;
    } else if (type == EVENT_TYPE_POINTER_PRESSED ||
               type == EVENT_TYPE_POINTER_DRAGGED ||
               type == EVENT_TYPE_POINTER_RELEASED) {
        v1 = event.point.x;
        v2 = event.point.y;
    }

    /* Allocate a tuple to store the return values */
    retval = tuple_new(3, &r_ptuple);
    PM_RETURN_IF_ERROR(retval);

    heap_gcPushTempRoot(r_ptuple, &objid);
    retval = int_new(type, &p1);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[0] = p1;
    retval = int_new(v1, &p2);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[1] = p2;
    retval = int_new(v2, &p3);
    POP_TMPROOT_AND_RETURN_IF_ERROR(retval, objid);
    ((pPmTuple_t)r_ptuple)->val[2] = p3;
    heap_gcPopTempRoot(objid);

    /* Return the tuple on the stack */
    NATIVE_SET_TOS(r_ptuple);

    return retval;
    """
    pass

_pointer_events = {EVENT_TYPE_POINTER_PRESSED: 'Pointer Pressed',
                   EVENT_TYPE_POINTER_DRAGGED: 'Pointer Dragged',
                   EVENT_TYPE_POINTER_RELEASED: 'Pointer Released'}

_key_events = {EVENT_TYPE_KEY_PRESSED: 'Key Pressed',
               EVENT_TYPE_KEY_RELEASED: 'Key Released'}

class Event:
    def __init__(self, event_type):
        self.type = event_type
    def __str__(self):
        if self.type in _pointer_events:
            return '%s: x=%d y=%d' % (_pointer_events[self.type], self.x, self.y)
        elif self.type in _key_events:
            return ('%s: key=%d nativekey=%d' % 
                    (_key_events[self.type], self.key, self.nativekey))
        else:
            return 'Event type: %d' % self.type

def maGetEvent():
    t = _maGetEvent()
    if not t:
        return None
    etype, v1, v2 = t
    event = Event(etype)
    if etype in [EVENT_TYPE_POINTER_PRESSED,
                 EVENT_TYPE_POINTER_DRAGGED,
                 EVENT_TYPE_POINTER_RELEASED]:
        event.x = v1
        event.y = v2
    elif etype in [EVENT_TYPE_KEY_PRESSED,
                  EVENT_TYPE_KEY_RELEASED]:
        event.key = v1
        event.nativekey = v2
    return event

def maGetEvents():
    while True:
        event = maGetEvent()
        if event:
            yield event
        else:
            break

def _maGetNone():
    """__NATIVE__
    PmReturn_t retval;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    NATIVE_SET_TOS(PM_NONE);
    return retval;
    """
    pass

def maGetNone():
    return _maGetNone()

def maWait(timeout):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maWait(int timeout); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int timeout;
    pPmObj_t p_timeout = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_timeout = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_timeout) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    timeout = ((pPmInt_t)p_timeout)->val;

    maWait(timeout);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maTime():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maTime(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maTime();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maLocalTime():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maLocalTime(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maLocalTime();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maGetMilliSecondCount():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maGetMilliSecondCount(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maGetMilliSecondCount();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

def maFreeObjectMemory():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maFreeObjectMemory(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maFreeObjectMemory();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

def maTotalObjectMemory():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maTotalObjectMemory(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maTotalObjectMemory();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

def maVibrate(ms):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maVibrate(int ms); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int ms;
    pPmObj_t p_ms = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_ms = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_ms) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    ms = ((pPmInt_t)p_ms)->val;

    func_retval = maVibrate(ms);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSoundPlay(sound_res, offset, size):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maSoundPlay(MAHandle sound_res, int offset, int size); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int sound_res;
    pPmObj_t p_sound_res = C_NULL;

    int offset;
    pPmObj_t p_offset = C_NULL;

    int size;
    pPmObj_t p_size = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 3)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_sound_res = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_sound_res) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_offset = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_offset) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_size = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_size) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    sound_res = ((pPmInt_t)p_sound_res)->val;
    offset = ((pPmInt_t)p_offset)->val;
    size = ((pPmInt_t)p_size)->val;

    func_retval = maSoundPlay(sound_res, offset, size);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSoundStop():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maSoundStop(void); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    maSoundStop();

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maSoundIsPlaying():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maSoundIsPlaying(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maSoundIsPlaying();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSoundGetVolume():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maSoundGetVolume(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maSoundGetVolume();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maSoundSetVolume(vol):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maSoundSetVolume(int vol); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int vol;
    pPmObj_t p_vol = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_vol = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_vol) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    vol = ((pPmInt_t)p_vol)->val;

    maSoundSetVolume(vol);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass

#int maInvokeExtension(int function, int a, int b, int c);

# This doesn't really belong here, but it plenty useful.
def int(v):
    """__NATIVE__

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int int_val;
    pPmObj_t p_float = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_float = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_float) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    int_val = (int)(((pPmFloat_t)p_float)->val);

    retval = int_new(int_val, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

# Relatively cheap 16 bit pseudo randomness
def rand():
    """__NATIVE__
    static unsigned long randx = 0x01234567;
    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    randx *= 1103515245;
    randx += 12345;
    func_retval = (randx >> 16) & 0xffff;
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass

def xrange(n):
    i = 0
    while i < n:
        yield i
        i += 1

