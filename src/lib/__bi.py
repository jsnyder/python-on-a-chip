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
# Provides PyMite's builtins module, __bi.
#
# USAGE
# -----
#
# The builtins are loaded by the interpreter.
# The user must not import this module directly.
#
# LOG
# ---
#
# 2006/08/21    #28: Adapt native libs to use the changed func calls
# 2002/12/20    Added globals, locals, range.
# 2002/12/19    Created.
#


#### CONSTS

C = "Copyright 2001 Dean W. Hall.  All rights reserved."


#### FUNCS

def globals():
    """__NATIVE__
    pPyObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        return PY_RET_EX_TYPE;
    }

    /* Return calling frame's globals dict  on stack*/
    pr = (pPyObj_t)NATIVE_GET_PFRAME()->fo_globals;
    NATIVE_SET_TOS(pr);

    return PY_RET_OK;
    """
    pass


def id(o):
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        return PY_RET_EX_TYPE;
    }

    /* Return object's address as an int on the stack */
#ifdef TARGET_AVR
    retval = int_new((S32)(S16)NATIVE_GET_LOCAL(0), &pr);
#elif defined(TARGET_DESKTOP)
    retval = int_new((S32)NATIVE_GET_LOCAL(0), &pr);
#else
#error Code is not implemented for the desired target
#endif
    NATIVE_SET_TOS(pr);

    return retval;
    """
    pass


def len(s):
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t ps = C_NULL;
    pPyObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        return PY_RET_EX_TYPE;
    }

    /* Get first arg */
    ps = NATIVE_GET_LOCAL(0);

    /* Get the length of the arg based on its type */
    switch (ps->od.od_type)
    {
        case OBJ_TYPE_STR:
            retval = int_new(((pPyString_t)ps)->length, &pr);
            break;

        case OBJ_TYPE_TUP:
            retval = int_new(((pPyTuple_t)ps)->length, &pr);
            break;

        case OBJ_TYPE_LST:
            retval = int_new(((pPyList_t)ps)->length, &pr);
            break;

        case OBJ_TYPE_DIC:
            retval = int_new(((pPyDict_t)ps)->length, &pr);
            break;

        default:
            /* If not a string or sequence type, raise TypeError */
            retval = PY_RET_EX_TYPE;
    }

    NATIVE_SET_TOS(pr);
    return retval;
    """
    pass


def locals():
    """__NATIVE__
    pPyObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 0)
    {
        return PY_RET_EX_TYPE;
    }

    /* Return calling frame's local attrs dict on the stack */
    pr = (pPyObj_t)NATIVE_GET_PFRAME()->fo_attrs;
    NATIVE_SET_TOS(pr);

    return PY_RET_OK;
    """
    pass


def map(f, s):
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t pf = C_NULL;
    pPyObj_t ps = C_NULL;
    pPyObj_t pr = C_NULL;
    S8 length = 0;
    S8 i = 0;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 2)
    {
        return PY_RET_EX_TYPE;
    }

    /* Get args */
    pf = NATIVE_GET_LOCAL(0);
    ps = NATIVE_GET_LOCAL(1);

    /* If args are wrong type, raise TypeError */
    if (pf->od.od_type != OBJ_TYPE_FXN)
    {
        return PY_RET_EX_TYPE;
    }

    /* Get the sequence length based on type */
    switch (ps->od.od_type)
    {
        case OBJ_TYPE_TUP:
            length = ((pPyTuple_t)ps)->length;
            break;

        case OBJ_TYPE_LST:
            length = ((pPyList_t)ps)->length;
            break;

        case OBJ_TYPE_STR:
            length = ((pPyString_t)ps)->length;
            break;

        default:
            return PY_RET_EX_TYPE;
    }

    /* XXX: Do a dummy map, fill func with Nones */
    retval = list_new(&pr);
    PY_RETURN_IF_ERROR(retval);

    for (i = 0; i < length; i++)
    {
        retval = list_append(pr, PY_NONE);
        PY_RETURN_IF_ERROR(retval);
    }

    return retval;
    """
    pass


def range(a, b, c):
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t pa = C_NULL;
    pPyObj_t pb = C_NULL;
    pPyObj_t pc = C_NULL;
    pPyObj_t pi = C_NULL;
    pPyObj_t pr = C_NULL;
    U16 i = 0;

    switch (NATIVE_GET_NUM_ARGS())
    {
        case 1:
            pa = PY_ZERO;
            pb = NATIVE_GET_LOCAL(0);
            pc = PY_ONE;
            break;

        case 2:
            pa = NATIVE_GET_LOCAL(0);
            pb = NATIVE_GET_LOCAL(1);
            pc = PY_ONE;
            break;

        case 3:
            pa = NATIVE_GET_LOCAL(0);
            pb = NATIVE_GET_LOCAL(1);
            pc = NATIVE_GET_LOCAL(2);

            /* If 3rd arg is 0, ValueError */
            if (((pPyInt_t)pc)->val == 0)
            {
                return PY_RET_EX_VAL;
            }
            break;

        default:
            /* If wrong number of args, raise TypeError */
            return PY_RET_EX_TYPE;
    }

    /* Allocate list */
    retval = list_new(&pr);
    PY_RETURN_IF_ERROR(retval);

    /* Iterate depending on counting direction */
    if (((pPyInt_t)pc)->val > 0)
    {
        for (i = ((pPyInt_t)pa)->val;
             i < ((pPyInt_t)pb)->val;
             i += ((pPyInt_t)pc)->val)
        {
            retval = int_new(i, &pi);
            PY_RETURN_IF_ERROR(retval);

            retval = list_append(pr, pi);
            PY_RETURN_IF_ERROR(retval);
        }
    }
    else
    {
        for (i = ((pPyInt_t)pa)->val;
             i > ((pPyInt_t)pb)->val;
             i += ((pPyInt_t)pc)->val)
        {
            retval = int_new(i, &pi);
            PY_RETURN_IF_ERROR(retval);

            list_append(pr, pi);
            PY_RETURN_IF_ERROR(retval);
        }
    }

    /* Return list */
    NATIVE_SET_TOS(pr);
    return retval;
    """
    pass


def type(o):
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t po = C_NULL;
    pPyObj_t pr = C_NULL;

    /* If wrong number of args, raise TypeError */
    if (NATIVE_GET_NUM_ARGS() != 1)
    {
        return PY_RET_EX_TYPE;
    }

    /* Get arg */
    po = NATIVE_GET_LOCAL(0);

    /* Create int from type enum */
    retval = int_new(po->od.od_type, &pr);
    NATIVE_SET_TOS(pr);
    return retval;
    """
    pass


#
# Allocates an exception class object
#
def _exn():
    """__NATIVE__
    PyReturn_t retval;
    pPyClass_t pexn;
    P_U8 pchunk;

    /* Alloc a class object with attributes dict */
    retval = heap_getChunk(sizeof(PyClass_t), &pchunk);
    PY_RETURN_IF_ERROR(retval);
    pexn = (pPyClass_t)pchunk;
    pexn->od.od_type = OBJ_TYPE_EXN;
    retval = dict_new((pPyObj_t *)&pexn->cl_attrs);

    NATIVE_SET_TOS((pPyObj_t)pexn);

    return retval;
    """
    pass


#
# Exception classes
#
AssertionError = _exn()
AssertionError.code = 0xE4

#:mode=c:
