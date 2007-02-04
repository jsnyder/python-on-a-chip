# PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
# Copyright 2002 Dean Hall
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#

#
# System Test 071
# Tests implementation of builtin function eval()
#

# The variable "n" does not exist
# "n" will be initialized by the code contained in the image below
# The image below is an image of the following code snippet::
#
#   ipm> import sys; sys.putb(0x34); n=42; sys.putb(0x32)
#
img = '\nd\x00\x00\x03\x00\x04\x04\x03\x03sys\x03\x04putb\x03\x01n\x03\x05<ipm>\x04\x05\x01\xff\xff\xff\xff\x00\x014\x00\x00\x00\x01*\x00\x00\x00\x012\x00\x00\x00d\x00\x00d\x01\x00k\x00\x00Z\x00\x00e\x00\x00i\x01\x00d\x02\x00\x83\x01\x00Fd\x03\x00Z\x02\x00e\x00\x00i\x01\x00d\x04\x00\x83\x01\x00Fd\x01\x00S'

# Convert the image to a code object and evaluate it
co = Co(img)
eval(co)

# Assert that "n" is now set to the predetermined value
assert n == 42
