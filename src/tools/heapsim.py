#!/bin/env python

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

"""
HeapSim -- Heap Simulator with Garbage Collector

Attempts to simulate a heap and its garbage collector.
Chunk allocation uses a hybrid best-fit algorithm
with bounded internal fragmentation.
Chunk deallocation puts chunks into four sorted free lists.
Chunk reclamation uses a hybrid mark-sweep
with a lazy sweep option.

Simulation is performed by executing traces of memory transactions
that were output from real program execution.
"""


# heap details
HEAPBASE = 0x0200   # realistic heap for 4K RAM
HEAPSIZE = 0x0D00
MINCHUNK = 6        # type1, size1, next2, prev2
MAXCHUNK = 255      # just a guess


# free list bin size delimiters
LIST1LIMIT = 8
LIST2LIMIT = 16
LIST3LIMIT = 24

# chunk field indices
ADDRESS = 0
SIZE = 1
NEXT = 2


class HeapSim:
    """Heap Simulator with Garbage Collector

    The heap is simulated as a dict of {address, chunk} pairs.
    An address is a 16-bit integer.
    An allocated chunk is a list of [address, size]
    A free chunk is a list of [address, size, next]
    """


    def __init__(self,):
        """Initialize the heap and free lists."""

        # init empty free lists
        self.pfreelist1 = NULL
        self.pfreelist2 = NULL
        self.pfreelist3 = NULL
        self.pfreelist4 = NULL

        # init heap with one big chunk
        self.heap = {}
        self.heap[HEAPBASE] = [HEAPBASE, HEAPSIZE, 0, 0]
        self.pcleanheap = HEAPBASE


    def getChunk(self, size):
        """Allocate a chunk of memory using a hybrid best fit algorithm.

        Search in one of 4 sorted free lists for a bestfit chunk
        with constrained internal fragmentation.
        If nothing, carve a new chunk out of the cleanheap.
        If nothing, return the bestfit chunk
        without fragmentation constraint.
        If still nothing, must obtain recycled chunk (perform GC)
        Set values in simulated heap.
        Return address of chunk.
        """

        if size < MINCHUNK or size > MAXCHUNK:
            return NULL

        # optimization
        heap = self.heap

        #### search for chunk in sorted free lists
        if size < LIST1LIMIT and self.pfreelist1 != NULL:
            p = self.pfreelist1
        elif size < LIST2LIMIT and self.pfreelist2 != NULL:
            p = self.pfreelist2
        elif size < LIST3LIMIT and self.pfreelist3 != NULL:
            p = self.pfreelist3
        else:
            p = self.pfreelist4

        if p != NULL:

            # scan free list for first fit
            while (p != NULL) and (heap[p][SIZE] < size):
                p = heap[p][NEXT]

            # if first fit is best fit (meets fragmentation limit)
            # unlink and return this address
            if (p != NULL and heap[p][SIZE] >= size and
			    heap[p][SIZE] <= size + MAX_FRAG):
                heap[heap[p][PREV]][NEXT] = heap[p][NEXT]
                heap[heap[p][NEXT]][PREV] = heap[p][PREV]
                heap[p] = [p, size]
                return p


        #### if nothing in free lists, check cleanheap
        # if cleanheap is big enough, carve chunk out of backside
        if heap[pcleanheap][SIZE] >= size:
            heap[pcleanheap][SIZE] -= size
            addr = pcleanheap + heap[pcleanheap][SIZE]
            heap[addr] = [addr, size]
            return addr

        #### if nothing from cleanheap, try first fit (without frag limit)
		# if first fit is big enough
        if (p != NULL) and (heap[p][SIZE] >= size):

            # unlink and return address
            heap[heap[p][PREV]][NEXT] = heap[p][NEXT]
            heap[heap[p][NEXT]][PREV] = heap[p][PREV]
            heap[p] = [p, size]
            return p

        # if still don't have a chunk, must GC
        self.mark()
        self.sweep()
        # XXX must prevent recursing more than once
        #return self.getChunk(size)

        return NULL


    def delChunk(self, pchunk):
        """Deallocate the given chunk.

        Put chunk in appropriate freelist in sorted order.
        Each list is sorted smallest to largest by chunk size.
        """

        size = heap[pchunk][SIZE]

        # select free list to put chunk in
        if size < LIST1LIMIT:
            p = self.pfreelist1
        elif size < LIST2LIMIT:
            p = self.pfreelist2
        elif size < LIST3LIMIT:
            p = self.pfreelist3
        else:
            p = self.pfreelist4

        # if list is empty
        if p == NULL:
            pass

        # else if chunk is first in list
        elif size <= heap[p][SIZE]:

            # insert chunk at 0th index
            heap[pchunk].append(p)
            heap[pchunk].append(NULL)
            self.pfreelist1 = pchunk
            return

        # otherwise, scan list for insertion position
        while ((heap[p][NEXT] != NULL) and
               (heap[p][SIZE] < size)):
            p = p[NEXT]

        # insert chunk here
        heap[p].append()

    def mark(self,):
        """Mark all live objects in the heap.
        
        Recursively mark starting from each root.
        """
        pass


    def sweep(self,):
        """Sweep the heap and reclaim unmarked chunks.
        
        Linearly traverse the heap, insorting unused chunks
        in the free lists.
        """
        pass
    
    
    def lazySweep(self, size):
        """Return the first reclaimed chunk
        that meets the requested size.
        """
        pass
