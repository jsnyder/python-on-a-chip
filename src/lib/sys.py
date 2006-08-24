#!/usr/bin/env python
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
# 2006/08/21    #28: Adapt native libs to use the changed func calls
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
    PyReturn_t retval = 0;
    pPyObj_t pval = C_NULL;
    
    /* Get the given exit value */
    pval = NATIVE_GET_LOCAL(0);
    NATIVE_SET_TOS(pval);
    retval = (S16)((pPyInt_t)pval)->val;
    
    /* Set the interpreter to exit */
    gVmGlobal.interpctrl = INTERP_CTRL_EXIT;
    return retval;
    """
    pass
