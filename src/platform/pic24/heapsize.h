/*
# This file is Copyright 2010 Dean Hall.
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
*/

#ifndef _HEAPSIZE_H_
#define _HEAPSIZE_H_

#define HS 6892
// Make room for the debugger if necessary
#ifdef __DEBUG
#define HEAP_SIZE (HS - 80)
#else
#define HEAP_SIZE HS
#endif

#endif /* _HEAPSIZE_H_ */
