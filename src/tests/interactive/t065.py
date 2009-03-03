#
# PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
# Copyright 2002 Dean Hall.  All rights reserved.
# PyMite is offered through one of two licenses: commercial or open-source.
# See the LICENSE file at the root of this package for licensing details.
#

#
# Interactive Test 065
# Tests plat module's putb and getb functions
#

import plat

plat.puts("Type a letter: ")
c = plat.getb()

plat.puts("Echo: ")
plat.putb(c)
plat.putb(c+1)
plat.putb(c+2)
plat.putb(ord("\n"))
