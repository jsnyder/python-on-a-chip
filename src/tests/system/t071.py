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
# System Test 071
# Tests implementation of builtin function eval()
#

# Create the code image blow by following these steps::
#
#   >>> pic = pmImgCreator.PmImgCreator()
#   >>> codestr = "import sys; sys.putb(0x34); n=42; sys.putb(0x32)"
#   >>> co = compile(codestr, "", "single")
#   >>> codeimg = pic.co_to_str(co)
#   >>> print codeimg
#

# The variable "n" does not exist
# "n" will be initialized by the code contained in the image below
# The image below is an image of the following code snippet::
#
#   ipm> import sys; sys.putb(0x34); n=42; sys.putb(0x32)
#
img = '\nc\x00\x00\x03\x00\x04\x04\x03\x03\x00sys\x03\x04\x00putb\x03\x01\x00n\x03\x00\x00\x04\x05\x01\xff\xff\xff\xff\x00\x014\x00\x00\x00\x01*\x00\x00\x00\x012\x00\x00\x00d\x00\x00d\x01\x00k\x00\x00Z\x00\x00e\x00\x00i\x01\x00d\x02\x00\x83\x01\x00Fd\x03\x00Z\x02\x00e\x00\x00i\x01\x00d\x04\x00\x83\x01\x00Fd\x01\x00S'

# Convert the image to a code object and evaluate it
co = Co(img)
eval(co)

# Assert that "n" is now set to the predetermined value
assert n == 42
