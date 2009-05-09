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
# System Test 003  Unrelated to issue #3.
# A module that has two simple functions, and calls them via main().
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
