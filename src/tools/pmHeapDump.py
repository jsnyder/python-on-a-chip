#!/usr/bin/env python

# This file is Copyright 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
#
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING in this directory.

"""
PyMite Heap Dump
================

Parses a heap dump into human-readable format.

The heap dump file is created by inserting a calls to heap_dump()
inside heap_gcRun().  Using two calls, a before and after, is ideal.

The dump format is:

=========== ==========================================
NumBytes    Contents
=========== ==========================================
4           int: HEAP_SIZE
4           Pointer to heap_base
HEAP_SIZE   contents of heap (byte array)
4           int: NUM_ROOTS
NUM_ROOTS*4 Pointers to roots
=========== ==========================================

The heap_dump() function names files incrementally starting from:

    pmheapdump00.bin
    pmheapdump01.bin
    ...
    pmheapdumpNN.bin
"""

## @file
#  @copybrief pmHeapDump

## @package pmHeapDump
#  @brief PyMite Heap Dump
#
#  See the source docstring for details.

__usage__ = """USAGE:
pmHeapDump.py [filename]
"""


import os, struct, sys, types, UserDict


class PmObject(UserDict.UserDict):
    """A model of an object.
    """

    PM_TYPES = (
        "NON", "INT", "FLT", "STR", "TUP", "COB", "MOD", "CLO",
        "FXN", "CLI", "CIM", "NIM", "NOB", "THR", "EXN", "BOL",
        "CIO", "MTH", "LST", "DIC", "x",   "x",   "x",   "x",
        "x",   "FRM", "BLK", "SEG", "SGL", "SQI", "NFM", )


    def _parse_int(self,):
        addr = self.addr + 4
        self.data['val'] = struct.unpack("i", self.heap[addr : addr + 4])[0]


    def _parse_str(self,):
        d = self.data
        addr = self.addr + 2
        d['len'] = strlen = struct.unpack("H", self.heap[addr : addr + 2])[0]
        d['cache_next'] = struct.unpack("P", self.heap[addr + 2 : addr + 6])[0]
        d['val'] = self.heap[addr + 6: addr + 6 + strlen]


    def _parse_tup(self,):
        d = self.data
        addr = self.addr + 2
        d['len'] = strlen = struct.unpack("H", self.heap[addr : addr + 2])[0]


    def _parse_lst(self,):
        addr = self.addr + 2
        self.data['len'] = struct.unpack("H", self.heap[addr : addr + 2])[0]
        self.data['sgl'] = struct.unpack("P", self.heap[addr + 2 : addr + 6])[0]


    def _parse_free(self,):
        addr = self.addr + 2
        self.data['prev'] = struct.unpack("P", self.heap[addr : addr + 4])[0]
        self.data['next'] = struct.unpack("P", self.heap[addr + 4 : addr + 8])[0]


    _parse_nul = lambda x: x
    parse = (_parse_nul, _parse_int, _parse_nul, _parse_str,
             _parse_tup, _parse_nul, _parse_nul, _parse_nul,
             _parse_nul, _parse_nul, _parse_nul, _parse_nul,
             _parse_nul, _parse_nul, _parse_nul, _parse_nul,
             _parse_lst, _parse_nul, _parse_nul, _parse_nul,
             _parse_nul, _parse_nul, _parse_nul, _parse_nul,
             _parse_nul, _parse_nul, _parse_nul, _parse_nul,
             _parse_nul, _parse_nul, _parse_nul, _parse_nul, )


    def __init__(self, heap, addr):
        """Initialize the object based on the given string from the dump file.
        """
        UserDict.UserDict.__init__(self)

        d = self.data

        self.heap = heap
        self.addr = addr

        od = struct.unpack("H", heap[addr : addr + 2])[0]
        d['mark'] = (' ','M')[(od & 0x4000) == 0x4000]
        d['free'] = (' ','F')[(od & 0x8000) == 0x8000]
        d['val'] = None

        if d['free'] == 'F':
            d['size'] = (od & 0x3FFF) << 2
            d['type'] = "fre"
            PmObject._parse_free(self)

        else:
            size = (od & 0x01FF) << 2
            assert size > 0
            typeindex = (od >> 9) & 0x1f
            objtype = PmObject.PM_TYPES[typeindex]
            d['size'] = size
            d['type'] = objtype
            PmObject.parse[typeindex](self)


    def __str__(self,):
        """The printable representation of the object.
        """
        d = self.data
        result = []
        result.append("%s %s %d %s%s: " % (
            hex(self.addr),
            d['type'],
            d['size'],
            d['mark'],
            d['free'],))

        if d['type'] == "fre":
            result.append("next=%s, prev=%s" % (hex(d['next']), hex(d['prev'])))

        elif d['type'] == "INT":
            result.append("%d" % d['val'])

        elif d['type'] == "STR":
            result.append("cache_next=%s : %s" % (hex(d['cache_next']), str(d['val'])))

        elif d['type'] == "TUP":
            result.append("len=%s" % (str(d['len'])))

        return "".join(result)


class PmHeap(UserDict.UserDict):
    """A model of the heap.
    """

    def __init__(self, fn):
        """Initialize the heap based on the given dump file.
        """
        UserDict.UserDict.__init__(self)

        self.is_parsed = False

        fp = open(fn, "rb")
        s = fp.read()
        fp.close()

        self.size = size = struct.unpack("i", s[:4])[0]
        self.base = struct.unpack("P", s[4 : 8])[0]
        self.rawheap = s[8 : size + 8]

        num_roots = struct.unpack("i", s[size + 8 : size + 12])[0]
        roots = {}
        (roots['None'],
         roots['False'],
         roots['True'],
         roots['Zero'],
         roots['One'],
         roots['NegOne'],
         roots['CodeStr'],
         roots['Builtins'],
         roots['NativeFrame'],
         roots['ThreadList']) = struct.unpack("%dP" % num_roots, s[size + 12:])
        self.roots = roots


    def __getitem__(self, indx):
        """Returns the object at the given address
        or the string of bytes defined by the slice.
        """
        # Return the object at the given address
        if type(indx) == types.IntType:
            if is_parsed:
                return self.data[indx]
            else:
                return PmObject(self, indx)

        # Return the string of bytes defined by the slice
        elif type(indx) == types.SliceType:
            return self.rawheap[indx.start - self.base : indx.stop - self.base]

        else:
            assert False, "Bad type to heap[%s]" % type(indx)


    def parse_heap(self,):
        """Parse the heap into a dict of key=address, value=object items
        """
        d = self.data

        addr = self.base
        end = addr + self.size
        while addr < end:
            d[addr] = obj = PmObject(self, addr)
            d[addr] = obj
            addr += obj['size']
            print obj
        self.is_parsed = True


def main():
    if len(sys.argv) < 2:
        fn = os.path.join(os.path.curdir, "pmheapdump00.bin")
    elif len(sys.argv) == 2:
        fn = sys.argv[1]
    else:
        print __usage__
        sys.exit()

    heap0 = PmHeap(fn)
    heap0.parse_heap()

if __name__ == "__main__":
    main()
