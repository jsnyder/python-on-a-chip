/*
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
# is seen in the file COPYING up one directory from this.
*/


/** 
 * @file
 * @brief VM feature configuration for the PIC24/dsPIC33
 *
 * These compile time switches include features or save space.
 *
 * IMPORTANT: All of the HAVE_* items in this file should also exist in the
 * PM_FEATURES dict in src/tools/pmImgCreator.py.  If the item is defined here,
 * the corresponding dict value should be True; False otherwise.
 */


#ifndef FEATURES_H_
#define FEATURES_H_


/** Defines the size of the static heap */
// Note: for unit testing, no Python heap is needed, so make it tiny.
// The unit tests need lots of heap and stack, so a small Python heap
// allows that.
#ifdef UNIT_TEST
#define PM_HEAP_SIZE 100
#else
#define PM_HEAP_SIZE 6800
#endif

/**
 * When defined, bytecodes PRINT_ITEM and PRINT_NEWLINE are supported. Along
 * with these, helper routines in the object type are compiled in that allow
 * printing of the object.
 * REQUIRES stdio.h to have snprintf()
 */
#define HAVE_PRINT


/**
 * When defined, the code to perform mark-sweep garbage collection is included
 * in the build and automatic GC is enabled.  When undefined the allocator
 * will distribute memory until none is left, after which a memory exception
 * will occur.
 */
#define HAVE_GC


/* #148 Create configurable float datatype */
/**
 * When defined, the code to support floating point objects is included
 * in the build.
 */
#define HAVE_FLOAT

/**
 * If \ref HAVE_FLOAT is defined, then define the storage scheme for 
 * floating-point numbers by uncommenting only one of the two options below.
 */
#define PM_FLOAT_LITTLE_ENDIAN
// #define PM_FLOAT_BIG_ENDIAN

/**
 * When defined, the code to support the keyword del is included in the build.
 * This involves the bytecodes: DELETE_SUBSCR, DELETE_NAME, DELETE_ATTR,
 * DELETE_GLOBAL and DELETE_FAST.
 */
#define HAVE_DEL // Saves 813 bytes

/**
 * When defined, the code to support the IMPORT_FROM and IMPORT_STAR styles
 * is included in the build.
 */
#define HAVE_IMPORTS // Saves 207 bytes

/* #157 Support default args */
/**
 * When defined, the code to support default arguments to functions is included
 * in the build.
 */
#define HAVE_DEFAULTARGS

/* #160 Add support for string and tuple replication */
/**
 * When defined, the code to support sequence (list, tuple, string) replcation
 * is included in the build.
 * This feature is required by the builtin function __bi.map().
 */
#define HAVE_REPLICATION // Saves 330 bytes

/* #202 Implement classes in the vm */
/**
 * When defined, the code to support classes, instances, methods, etc.
 * is included in the build.
 */
#define HAVE_CLASSES

/**
 * When defined, the code to support the assert statement is included
 * in the build.
 */
#define HAVE_ASSERT
#if defined(HAVE_ASSERT) && !defined(HAVE_CLASSES)
#error HAVE_ASSERT requires HAVE_CLASSES
#endif

/* #207 Add support for the yield keyword */
/**
 * When defined, the code to support the yield keyword's use for 
 * generator-iterators is included in the build.
 */
#define HAVE_GENERATORS // Saves  1014 bytes
#if defined(HAVE_GENERATORS) && !defined(HAVE_CLASSES)
#error HAVE_GENERATORS requires HAVE_CLASSES
#endif

/* #244 Add support for the backtick operation (UNARY_CONVERT) */
/**
 * When defined, the code to support the backtick operation (`x`) is included
 * in the build.
 * REQUIRES stdio.h to have snprintf()
 */
#define HAVE_BACKTICK // Saves about 216 bytes

/* #205 Add support for string format operation */
/**
 * When defined, the code to perform string formatting using the binary modulo
 * operator is included in the build.
 * REQUIRES stdio.h to have snprintf()
 */
#define HAVE_STRING_FORMAT

/* #256 Add support for closures */
/**
 * When defined, the code to support function closures is included in the 
 * build.
 */
#define HAVE_CLOSURES // Saves 738 bytes
#if defined(HAVE_CLOSURES) && !defined(HAVE_DEFAULTARGS)
#error HAVE_CLOSURES requires HAVE_DEFAULTARGS
#endif

/* #289 Create bytearray datatype */
/**
 * When defined, the code to support the bytearray type is included in the
 * build.
 */
/*#define HAVE_BYTEARRAY*/
#if defined(HAVE_BYTEARRAY) && !defined(HAVE_CLASSES)
#error HAVE_BYTEARRAY requires HAVE_CLASSES
#endif

/* Issue #103 Add debug info to exception reports */
/**
 * When defined, the code to support debug information in exception reports
 * is included in the build.
 */
/*#define HAVE_DEBUG_INFO*/


/*
 * Platform-specific definitions that are used in the VM
 */

/**
 * Define a processor-specific specifier for use in declaring the heap.
 * See <code>pmHeap</code> in heap.c for its use, which is:<br>
 * <code>static PmHeap_t pmHeap PM_PLAT_HEAP_ATTR;</code>
 */
#define PM_PLAT_HEAP_ATTR __attribute__((far)) __attribute__((aligned ((4))))

#endif /* FEATURES_H_ */
