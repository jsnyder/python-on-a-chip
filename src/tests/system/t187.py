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