#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Feature Test for Issue #50
#
# Integrate __LINE__ into PM_RAISE
#
# To check that PM_RAISE works, I made a simple code snippet below that
# will exercise specific functions in int.c
#

n = 1

n0 = +n
assert n0 == 1

n1 = ~n
assert n1 == -2

n2 = -n
assert n2 == -1
