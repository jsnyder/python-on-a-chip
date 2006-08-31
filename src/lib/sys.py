#!/usr/bin/env python
# :mode=c:
#
# Provides PyMite's system module, sys
#
# Copyright 2002 Dean Hall.
#
# USAGE
# -----
#
# import sys
#
# LOG
# ---
#
# 2006/08/31    #9: Fix BINARY_SUBSCR for case stringobj[intobj]
# 2006/08/21    Adapt native libs to use the changed func calls
# 2002/09/07    Created.
#

#### TODO
#modules = None #set ptr to dict w/native func
#platform = None #obtain from aux lib: platform.py
#memfree, platform/device, stdout, type (type consts?), rand
#ver = "0.1"            # XXX compile date & platform?
# Example: sys.version = '2.4.1 (#1, Feb 26 2006, 16:26:36) \n[GCC 4.0.0 20041026 (Apple Computer, Inc. build 4061)]'

#### CONSTS

maxint = 0x7FFFFFFF     # 2147483647


#### FUNCS

def exit(val):
    """__NATIVE__
    pPyObj_t pval = C_NULL;

    /* If no arg given, assume return 0 */
    if (NATIVE_GET_NUM_ARGS() == 0)
    {
        NATIVE_SET_TOS(PY_ZERO);
    }
    
    /* If 1 arg given, put it on stack */
    else if (NATIVE_GET_NUM_ARGS() == 1)
    {
        pval = NATIVE_GET_LOCAL(0);
        NATIVE_SET_TOS(pval);
    }

    /* If wrong number of args, raise TypeError */
    else
    {
        return PY_RET_EX_TYPE;
    }

    /* Raise the SystemExit exception */
    return PY_RET_EX_EXIT;
    """
    pass
