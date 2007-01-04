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

# TODO: Need #67 to convert image to co so I can feed co to eval().

# See that "n" does not yet exist
# "n" will be initialized by the code contained in this image
#img = "\n$\x00\x00\x01\x00\x04\x02\x03\x01n\x03\x05<ipm>\x04\x02\x01*\x00\x00\x00\x00d\x00\x00Z\x00\x00d\x01\x00S"

# Convert the image to a code object and evaluate it
#eval(Co(img))

# Assert that "n" is now set to the predetermined value
#assert n == 42
