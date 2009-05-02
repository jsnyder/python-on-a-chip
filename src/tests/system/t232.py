#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 232
# Fix pmImgCreator so two classes can have same method name
# An error during C compiling indicates a regression
#


class A():
    def __init__(self,):
        """__NATIVE__
        NATIVE_SET_TOS(PM_NONE);
        return PM_RET_OK;
        """
        pass


class B():
    def __init__(self,):
        """__NATIVE__
        NATIVE_SET_TOS(PM_NONE);
        return PM_RET_OK;
        """
        pass
