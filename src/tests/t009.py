#
# t009.py
#
# Tests issue #009 - Fix BINARY_SUBSCRIPT opcode for string.
#

import sys

s = "test"
if s[0] != 't':
    sys.exit(1)
