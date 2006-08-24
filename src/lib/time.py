#!/usr/bin/env python
#
# Provides PyMite's time module, time
#
# Copyright 2002 Dean Hall.
#
# USAGE
# -----
#
# import time
# t1 = time.clock()
# doStuff()
# t2 = time.clock()
# print t2 - t1
#
# LOG
# ---
#
# 2006/08/21    #28: Adapt native libs to use the changed func calls
# 2002/05/25    Created.
#


#### CONSTS


#### FUNCS

#
# Returns the current time in (?milli?)seconds
#
def clock():
    """__NATIVE__
    PyReturn_t retval;
    pPyObj_t ptime;
    
    /* Create int obj with current time */
#ifdef TARGET_DESKTOP
    retval = int_new((int)time(C_NULL), &ptime);
#else
# error time.clock is unimplemented for non-DESKTOP builds
    retval = int_new(0, &ptime);
#endif

    /* return time via stack */
    NATIVE_SET_TOS(ptime);
    return retval;
    """
    pass
