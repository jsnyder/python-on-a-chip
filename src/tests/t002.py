#
# Feature Test for Issue #2
# Regression Test for Issue #28
#
# Separate stdlib from user app
#
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
    pPyObj_t pint = C_NULL;
    PyReturn_t retval;

    retval = int_new((S32)42, &pint);
    NATIVE_SET_TOS(pint);

    return retval;
    """
    pass

foo = push42()
bar = 6 * 7
assert foo == bar
