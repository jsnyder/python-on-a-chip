#
# tests003.py
#
# A module that has two simple functions,
# and calls them via main().
# This file is used with tests003.py
# to test pymite.
#


def a(a1, a2):
    """
    Return the sum of a1 and a2.
    """
    return a1 + a2


def b(b1, b2):
    """
    Return the difference between b1 and b2.
    """
    return b1 - b2


def main():
    a(2, 5)
    b(2, 6)
    return


main()
