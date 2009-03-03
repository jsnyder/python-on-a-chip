#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# System Test 153
# Fix dict.clear() which fails to free the seglists
#

import dict

# Clear a dict and then make sure it can be used afterward
d = {0:"zero", "one":1}
dict.clear(d)

d["zero"] = 0
d[1] = "one"

print d
