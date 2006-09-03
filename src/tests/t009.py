#
# Regression Test for Issue #9
#
# Fix BINARY_SUBSCR for case stringobj[intobj]
#

import sys

s = "test"
if s[0] != 't':
    sys.exit(1)
