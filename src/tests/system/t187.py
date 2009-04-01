#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 187
# Remove module-level docstring
#
"""NOT__NATIVE__
/* Inserted this so there is a module-level __doc__ string in the code object */
"""

b = "__doc__" in globals()
print "__doc__ in globals == ", b
if b:
    print "len(__doc__) == ", len(globals()["__doc__"])