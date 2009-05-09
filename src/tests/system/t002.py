# This file is Copyright 2003, 2006, 2007, 2009 Dean Hall.
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
# Feature Test for Issue #2
# Regression Test for Issue #28
# Separate stdlib from user app
# The test below proves that push42() was called from the usrlib native code
# and assert was called from the stdlib native code.
#
"""__NATIVE__
/*
 * This is a regression test for issue #28.
 * Having this doc-level native block should not affect
 * the index of the native func below.
 */
"""

#
# Pushes the int, 42, onto the stack
#
def push42():
    """__NATIVE__
    pPmObj_t pint = C_NULL;
    PmReturn_t retval;

    retval = int_new((int32_t)42, &pint);
    NATIVE_SET_TOS(pint);

    return retval;
    """
    pass

foo = push42()
bar = 6 * 7
assert foo == bar
