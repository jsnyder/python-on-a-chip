# This file contains wrappers that has been automatically
# generated from the maapi.h. Some of these has been moved
# to ma.py, sometimes they have changed into more a more
# Pythonic format.

# When some function or constant is missing from ma.h,
# it might be here.

"""__NATIVE__
#include <ma.h>
"""


TRANS_NONE = 0

TRANS_ROT90 = 5

TRANS_ROT180 = 3

TRANS_ROT270 = 6

TRANS_MIRROR = 2

TRANS_MIRROR_ROT90 = 7

TRANS_MIRROR_ROT180 = 1

TRANS_MIRROR_ROT270 = 4

HANDLE_SCREEN = 0

HANDLE_LOCAL = 0

RES_OUT_OF_MEMORY = 1

RES_BAD_INPUT = 2

RES_OK = 1

MAS_CREATE_IF_NECESSARY = 1

STERR_GENERIC = 2

STERR_FULL = 3

STERR_NONEXISTENT = 5

CONNERR_GENERIC = 2

CONNERR_MAX = 3

CONNERR_DNS = 4

CONNERR_INTERNAL = 5

CONNERR_CLOSED = 6

CONNERR_READONLY = 7

CONNERR_FORBIDDEN = 8

CONNERR_UNINITIALIZED = 9

CONNERR_CONLEN = 10

CONNERR_URL = 11

CONNERR_UNAVAILABLE = 12

CONNERR_CANCELED = 13

CONNERR_PROTOCOL = 14

CONNERR_NETWORK = 15

CONNERR_NOHEADER = 16

CONNERR_NOTFOUND = 17

CONNERR_USER = 1000000

CONNOP_READ = 1

CONNOP_WRITE = 2

CONNOP_CONNECT = 5

CONNOP_FINISH = 11

CONNOP_ACCEPT = 16

CONN_MAX = 32

BTADDR_LEN = 6

CONN_FAMILY_INET4 = 1

CONN_FAMILY_BT = 2

HTTP_GET = 1

HTTP_POST = 2

HTTP_HEAD = 3

MAK_UNKNOWN = 0

MAK_FIRST = 0

MAK_BACKSPACE = 8

MAK_TAB = 9

MAK_CLEAR = 12

MAK_RETURN = 13

MAK_PAUSE = 19

MAK_ESCAPE = 27

MAK_SPACE = 32

MAK_EXCLAIM = 33

MAK_QUOTEDBL = 34

MAK_POUND = 35

MAK_HASH = 35

MAK_GRID = 35

MAK_DOLLAR = 36

MAK_AMPERSAND = 38

MAK_QUOTE = 39

MAK_LEFTPAREN = 40

MAK_RIGHTPAREN = 41

MAK_ASTERISK = 42

MAK_STAR = 42

MAK_PLUS = 43

MAK_COMMA = 44

MAK_MINUS = 45

MAK_PERIOD = 46

MAK_SLASH = 47

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

MAK_COLON = 58

MAK_SEMICOLON = 59

MAK_LESS = 60

MAK_EQUALS = 61

MAK_GREATER = 62

MAK_QUESTION = 63

MAK_AT = 64

MAK_LEFTBRACKET = 91

MAK_BACKSLASH = 92

MAK_RIGHTBRACKET = 93

MAK_CARET = 94

MAK_UNDERSCORE = 95

MAK_BACKQUOTE = 96

MAK_A = 97

MAK_B = 98

MAK_C = 99

MAK_D = 100

MAK_E = 101

MAK_F = 102

MAK_G = 103

MAK_H = 104

MAK_I = 105

MAK_J = 106

MAK_K = 107

MAK_L = 108

MAK_M = 109

MAK_N = 110

MAK_O = 111

MAK_P = 112

MAK_Q = 113

MAK_R = 114

MAK_S = 115

MAK_T = 116

MAK_U = 117

MAK_V = 118

MAK_W = 119

MAK_X = 120

MAK_Y = 121

MAK_Z = 122

MAK_DELETE = 127

MAK_KP0 = 256

MAK_KP1 = 257

MAK_KP2 = 258

MAK_KP3 = 259

MAK_KP4 = 260

MAK_KP5 = 261

MAK_KP6 = 262

MAK_KP7 = 263

MAK_KP8 = 264

MAK_KP9 = 265

MAK_KP_PERIOD = 266

MAK_KP_DIVIDE = 267

MAK_KP_MULTIPLY = 268

MAK_KP_MINUS = 269

MAK_KP_PLUS = 270

MAK_KP_ENTER = 271

MAK_KP_EQUALS = 272

MAK_UP = 273

MAK_DOWN = 274

MAK_RIGHT = 275

MAK_LEFT = 276

MAK_INSERT = 277

MAK_HOME = 278

MAK_END = 279

MAK_PAGEUP = 280

MAK_PAGEDOWN = 281

MAK_FIRE = 284

MAK_SOFTLEFT = 285

MAK_SOFTRIGHT = 286

MAK_PEN = 291

MAK_BACK = 292

MAK_MENU = 293

MAK_RSHIFT = 303

MAK_LSHIFT = 304

MAK_RCTRL = 305

MAK_LCTRL = 306

MAK_RALT = 307

MAK_LALT = 308

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

EVENT_BUFFER_SIZE = 128

EVENT_CLOSE_TIMEOUT = 2000

EVENT_TYPE_CLOSE = 1

EVENT_TYPE_KEY_PRESSED = 2

EVENT_TYPE_KEY_RELEASED = 3

EVENT_TYPE_CONN = 4

EVENT_TYPE_BT = 5

EVENT_TYPE_POINTER_PRESSED = 8

EVENT_TYPE_POINTER_RELEASED = 9

EVENT_TYPE_POINTER_DRAGGED = 10

EVENT_TYPE_FOCUS_LOST = 13

EVENT_TYPE_FOCUS_GAINED = 14

EVENT_TYPE_LOCATION = 16

EVENT_TYPE_LOCATION_PROVIDER = 17

EVENT_TYPE_SCREEN_CHANGED = 21

EVENT_TYPE_CHAR = 22

EVENT_TYPE_TEXTBOX = 23

RUNTIME_MORE = 1

RUNTIME_JAVA = 2

RUNTIME_SYMBIAN = 3

RUNTIME_WINCE = 4

REPORT_PANIC = 1

REPORT_EXCEPTION = 2

REPORT_PLATFORM_CODE = 3

REPORT_USER_PANIC = 4

REPORT_TIMEOUT = 5

MA_LOC_NONE = 1

MA_LOC_INVALID = 2

MA_LOC_UNQUALIFIED = 3

MA_LOC_QUALIFIED = 4

MA_LPS_AVAILABLE = 1

MA_LPS_TEMPORARILY_UNAVAILABLE = 2

MA_LPS_OUT_OF_SERVICE = 3

MA_TB_TYPE_ANY = 0

MA_TB_TYPE_EMAILADDR = 1

MA_TB_TYPE_NUMERIC = 2

MA_TB_TYPE_PHONENUMBER = 3

MA_TB_TYPE_URL = 4

MA_TB_TYPE_DECIMAL = 5

MA_TB_RES_OK = 1

MA_TB_RES_CANCEL = 2

MA_TB_FLAG_PASSWORD = 0x1000

MA_TB_FLAG_UNEDITABLE = 0x2000

MA_TB_FLAG_SENSITIVE = 0x4000

MA_TB_FLAG_NON_PREDICTIVE = 0x8000

MA_TB_FLAG_INITIAL_CAPS_WORD = 0x10000

MA_TB_FLAG_INITIAL_CAPS_SENTENCE = 0x20000

IOCTL_UNAVAILABLE = 1

def maCheckInterfaceVersion(hash):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maCheckInterfaceVersion(int hash); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int hash;
    pPmObj_t p_hash = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_hash = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_hash) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    hash = ((pPmInt_t)p_hash)->val;

    func_retval = maCheckInterfaceVersion(hash);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#void ATTRIBUTE(noreturn, maExit(int result));

# No wrapper for
#void ATTRIBUTE(noreturn, maPanic(int result, const char* message));

# No wrapper for
#void* memset(void* dst, int val, ulong size);

# No wrapper for
#void* memcpy(void* dst, const void* src, ulong size);

def strcmp(str1, str2):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int strcmp(const char* str1, const char* str2); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    const char* str1;
    pPmObj_t p_str1 = C_NULL;

    const char* str2;
    pPmObj_t p_str2 = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_str1 = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_str1) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_str2 = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_str2) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    str1 = (char const *)&(((pPmString_t)p_str1)->val);
    str2 = (char const *)&(((pPmString_t)p_str2)->val);

    func_retval = strcmp(str1, str2);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#char* strcpy(char* dst, const char* src);

def __adddf3(a, b):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __adddf3(double a, double b); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    double b;
    pPmObj_t p_b = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);
    b = (double)(((pPmFloat_t)p_b)->val);

    func_retval = __adddf3(a, b);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def __subdf3(a, b):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __subdf3(double a, double b); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    double b;
    pPmObj_t p_b = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);
    b = (double)(((pPmFloat_t)p_b)->val);

    func_retval = __subdf3(a, b);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def __muldf3(a, b):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __muldf3(double a, double b); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    double b;
    pPmObj_t p_b = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);
    b = (double)(((pPmFloat_t)p_b)->val);

    func_retval = __muldf3(a, b);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def __divdf3(a, b):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __divdf3(double a, double b); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    double b;
    pPmObj_t p_b = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);
    b = (double)(((pPmFloat_t)p_b)->val);

    func_retval = __divdf3(a, b);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def __negdf2(a):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __negdf2(double a); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);

    func_retval = __negdf2(a);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def __fixdfsi(a):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int __fixdfsi(double a); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);

    func_retval = __fixdfsi(a);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#uint __fixunsdfsi(double a);

def __floatsidf(a):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double __floatsidf(int a); */

    PmReturn_t retval = PM_RET_OK;

    double func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int a;
    pPmObj_t p_a = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = ((pPmInt_t)p_a)->val;

    func_retval = __floatsidf(a);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#double __extendsfdf2(float a);

def dcmp(a, b):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int dcmp(double a, double b); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    double a;
    pPmObj_t p_a = C_NULL;

    double b;
    pPmObj_t p_b = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_FLT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    a = (double)(((pPmFloat_t)p_a)->val);
    b = (double)(((pPmFloat_t)p_b)->val);

    func_retval = dcmp(a, b);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#float __addsf3(float a, float b);

# No wrapper for
#float __subsf3(float a, float b);

# No wrapper for
#float __mulsf3(float a, float b);

# No wrapper for
#float __divsf3(float a, float b);

# No wrapper for
#float __negsf2(float a);

# No wrapper for
#int __fixsfsi(float a);

# No wrapper for
#uint __fixunssfsi(float a);

# No wrapper for
#float __floatsisf(int a);

# No wrapper for
#float __truncdfsf2(double a);

# No wrapper for
#int fcmp(float a, float b);

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


def cos(x):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double cos(double x); */

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

    func_retval = cos(x);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def tan(x):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double tan(double x); */

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

    func_retval = tan(x);
    retval = float_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def sqrt(x):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   double sqrt(double x); */

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

    func_retval = sqrt(x);
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


# No wrapper for
#void maGetClipRect(MARect* out);

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

def maGetTextSize(str):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetTextSize(const char* str); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

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

    func_retval = maGetTextSize(str);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#MAExtent maGetTextSizeW(const wchar* str);

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


# No wrapper for
#void maDrawTextW(int left, int top, const wchar* str);

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


def maResetBacklight():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maResetBacklight(void); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    maResetBacklight();

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maGetScrSize():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetScrSize(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maGetScrSize();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

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

# No wrapper for
#void maDrawImageRegion(MAHandle image, const MARect* srcRect, const MAPoint2d* dstPoint, int transformMode);

def maGetImageSize(image):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAExtent maGetImageSize(MAHandle image); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

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

    func_retval = maGetImageSize(image);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#void maGetImageData(MAHandle image, void* dst, const MARect* srcRect, int scanlength);

def maSetDrawTarget(image):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAHandle maSetDrawTarget(MAHandle image); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

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

    func_retval = maSetDrawTarget(image);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maFindLabel(name):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maFindLabel(const char* name); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    const char* name;
    pPmObj_t p_name = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_name = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_name) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    name = (char const *)&(((pPmString_t)p_name)->val);

    func_retval = maFindLabel(name);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maCreateImageFromData(placeholder, data, offset, size):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maCreateImageFromData(MAHandle placeholder, MAHandle data, int offset, int size); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int placeholder;
    pPmObj_t p_placeholder = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    int offset;
    pPmObj_t p_offset = C_NULL;

    int size;
    pPmObj_t p_size = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_placeholder = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_placeholder) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_offset = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_offset) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_size = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_size) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    placeholder = ((pPmInt_t)p_placeholder)->val;
    data = ((pPmInt_t)p_data)->val;
    offset = ((pPmInt_t)p_offset)->val;
    size = ((pPmInt_t)p_size)->val;

    func_retval = maCreateImageFromData(placeholder, data, offset, size);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#int maCreateImageRaw(MAHandle placeholder, const void* src, MAExtent size, int alpha);

def maCreateDrawableImage(placeholder, width, height):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maCreateDrawableImage(MAHandle placeholder, int width, int height); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int placeholder;
    pPmObj_t p_placeholder = C_NULL;

    int width;
    pPmObj_t p_width = C_NULL;

    int height;
    pPmObj_t p_height = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 3)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_placeholder = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_placeholder) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_width = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_width) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_height = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_height) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    placeholder = ((pPmInt_t)p_placeholder)->val;
    width = ((pPmInt_t)p_width)->val;
    height = ((pPmInt_t)p_height)->val;

    func_retval = maCreateDrawableImage(placeholder, width, height);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maCreateData(placeholder, size):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maCreateData(MAHandle placeholder, int size); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int placeholder;
    pPmObj_t p_placeholder = C_NULL;

    int size;
    pPmObj_t p_size = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_placeholder = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_placeholder) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_size = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_size) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    placeholder = ((pPmInt_t)p_placeholder)->val;
    size = ((pPmInt_t)p_size)->val;

    func_retval = maCreateData(placeholder, size);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maCreatePlaceholder():
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAHandle maCreatePlaceholder(void); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }


    func_retval = maCreatePlaceholder();
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maDestroyObject(handle):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maDestroyObject(MAHandle handle); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int handle;
    pPmObj_t p_handle = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_handle = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_handle) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    handle = ((pPmInt_t)p_handle)->val;

    maDestroyObject(handle);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maGetDataSize(data):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maGetDataSize(MAHandle data); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    data = ((pPmInt_t)p_data)->val;

    func_retval = maGetDataSize(data);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#void maReadData(MAHandle data, void* dst, int offset, int size);

# No wrapper for
#void maWriteData(MAHandle data, const void* src, int offset, int size);

# No wrapper for
#void maCopyData(const MACopyData* params);

def maOpenStore(name, flags):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAHandle maOpenStore(const char* name, int flags); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    const char* name;
    pPmObj_t p_name = C_NULL;

    int flags;
    pPmObj_t p_flags = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_name = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_name) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_flags = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_flags) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    name = (char const *)&(((pPmString_t)p_name)->val);
    flags = ((pPmInt_t)p_flags)->val;

    func_retval = maOpenStore(name, flags);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maWriteStore(store, data):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maWriteStore(MAHandle store, MAHandle data); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int store;
    pPmObj_t p_store = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_store = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_store) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    store = ((pPmInt_t)p_store)->val;
    data = ((pPmInt_t)p_data)->val;

    func_retval = maWriteStore(store, data);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maReadStore(store, placeholder):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maReadStore(MAHandle store, MAHandle placeholder); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int store;
    pPmObj_t p_store = C_NULL;

    int placeholder;
    pPmObj_t p_placeholder = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_store = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_store) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_placeholder = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_placeholder) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    store = ((pPmInt_t)p_store)->val;
    placeholder = ((pPmInt_t)p_placeholder)->val;

    func_retval = maReadStore(store, placeholder);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maCloseStore(store, _remove):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maCloseStore(MAHandle store, int _remove); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int store;
    pPmObj_t p_store = C_NULL;

    int _remove;
    pPmObj_t p__remove = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_store = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_store) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p__remove = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p__remove) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    store = ((pPmInt_t)p_store)->val;
    _remove = ((pPmInt_t)p__remove)->val;

    maCloseStore(store, _remove);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maConnect(url):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAHandle maConnect(const char* url); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    const char* url;
    pPmObj_t p_url = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_url = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_url) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    url = (char const *)&(((pPmString_t)p_url)->val);

    func_retval = maConnect(url);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maConnClose(conn):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maConnClose(MAHandle conn); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int conn;
    pPmObj_t p_conn = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_conn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_conn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    conn = ((pPmInt_t)p_conn)->val;

    maConnClose(conn);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


# No wrapper for
#void maConnRead(MAHandle conn, void* dst, int size);

# No wrapper for
#void maConnWrite(MAHandle conn, const void* src, int size);

def maConnReadToData(conn, data, offset, size):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maConnReadToData(MAHandle conn, MAHandle data, int offset, int size); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int conn;
    pPmObj_t p_conn = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    int offset;
    pPmObj_t p_offset = C_NULL;

    int size;
    pPmObj_t p_size = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_conn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_conn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_offset = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_offset) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_size = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_size) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    conn = ((pPmInt_t)p_conn)->val;
    data = ((pPmInt_t)p_data)->val;
    offset = ((pPmInt_t)p_offset)->val;
    size = ((pPmInt_t)p_size)->val;

    maConnReadToData(conn, data, offset, size);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maConnWriteFromData(conn, data, offset, size):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maConnWriteFromData(MAHandle conn, MAHandle data, int offset, int size); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int conn;
    pPmObj_t p_conn = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    int offset;
    pPmObj_t p_offset = C_NULL;

    int size;
    pPmObj_t p_size = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_conn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_conn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_offset = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_offset) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_size = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_size) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    conn = ((pPmInt_t)p_conn)->val;
    data = ((pPmInt_t)p_data)->val;
    offset = ((pPmInt_t)p_offset)->val;
    size = ((pPmInt_t)p_size)->val;

    maConnWriteFromData(conn, data, offset, size);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


# No wrapper for
#int maConnGetAddr(MAHandle conn, MAConnAddr* addr);

def maHttpCreate(url, method):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   MAHandle maHttpCreate(const char* url, int method); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    const char* url;
    pPmObj_t p_url = C_NULL;

    int method;
    pPmObj_t p_method = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_url = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_url) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_method = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_method) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    url = (char const *)&(((pPmString_t)p_url)->val);
    method = ((pPmInt_t)p_method)->val;

    func_retval = maHttpCreate(url, method);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maHttpSetRequestHeader(conn, key, value):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maHttpSetRequestHeader(MAHandle conn, const char* key, const char* value); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int conn;
    pPmObj_t p_conn = C_NULL;

    const char* key;
    pPmObj_t p_key = C_NULL;

    const char* value;
    pPmObj_t p_value = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 3)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_conn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_conn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_key = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_key) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_value = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_value) != OBJ_TYPE_STR)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    conn = ((pPmInt_t)p_conn)->val;
    key = (char const *)&(((pPmString_t)p_key)->val);
    value = (char const *)&(((pPmString_t)p_value)->val);

    maHttpSetRequestHeader(conn, key, value);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


# No wrapper for
#int maHttpGetResponseHeader(MAHandle conn, const char* key, char* buffer, int bufSize);

def maHttpFinish(conn):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maHttpFinish(MAHandle conn); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int conn;
    pPmObj_t p_conn = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_conn = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_conn) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    conn = ((pPmInt_t)p_conn)->val;

    maHttpFinish(conn);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


def maLoadResources(data):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maLoadResources(MAHandle data); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    data = ((pPmInt_t)p_data)->val;

    func_retval = maLoadResources(data);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


def maLoadProgram(data, reload):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   void maLoadProgram(MAHandle data, int reload); */

    PmReturn_t retval = PM_RET_OK;

    pPmObj_t p_func_retval = C_NULL;

    int data;
    pPmObj_t p_data = C_NULL;

    int reload;
    pPmObj_t p_reload = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_data = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_data) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_reload = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_reload) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    data = ((pPmInt_t)p_data)->val;
    reload = ((pPmInt_t)p_reload)->val;

    maLoadProgram(data, reload);

    NATIVE_SET_TOS(PM_NONE);

    return retval;
    """
    pass


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


# No wrapper for
#int maGetEvent(MAEvent* event);

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


def maInvokeExtension(function, a, b, c):
    """__NATIVE__
    /* Wrapper generated for: */
    /*   int maInvokeExtension(int function, int a, int b, int c); */

    PmReturn_t retval = PM_RET_OK;

    int func_retval;
    pPmObj_t p_func_retval = C_NULL;

    int function;
    pPmObj_t p_function = C_NULL;

    int a;
    pPmObj_t p_a = C_NULL;

    int b;
    pPmObj_t p_b = C_NULL;

    int c;
    pPmObj_t p_c = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 4)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_function = NATIVE_GET_LOCAL(0);
    if (OBJ_GET_TYPE(p_function) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_a = NATIVE_GET_LOCAL(1);
    if (OBJ_GET_TYPE(p_a) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_b = NATIVE_GET_LOCAL(2);
    if (OBJ_GET_TYPE(p_b) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    /* Raise TypeError if arg is not correct type */
    p_c = NATIVE_GET_LOCAL(3);
    if (OBJ_GET_TYPE(p_c) != OBJ_TYPE_INT)
    {
        PM_RAISE(retval, PM_RET_EX_TYPE);
        return retval;
    }

    function = ((pPmInt_t)p_function)->val;
    a = ((pPmInt_t)p_a)->val;
    b = ((pPmInt_t)p_b)->val;
    c = ((pPmInt_t)p_c)->val;

    func_retval = maInvokeExtension(function, a, b, c);
    retval = int_new(func_retval, &p_func_retval);

    NATIVE_SET_TOS(p_func_retval);

    return retval;
    """
    pass


# No wrapper for
#longlong maIOCtl(int function, int a, int b, int c MA_IOCTL_ELLIPSIS);

# No wrapper for
#(void) maIOCtl(3, (int)start, length, 0);

# No wrapper for
#(void) maIOCtl(4, (int)start, length, 0);

# No wrapper for
#(void) maIOCtl(5, enable, 0, 0);
