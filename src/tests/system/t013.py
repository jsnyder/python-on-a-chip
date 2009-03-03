#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 013
# Implement the equivalent of '__name__ == "__main__"' in module attrs
#

if ismain():
    print "In main."
else:
    print "Not in main."
