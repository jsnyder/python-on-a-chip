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
