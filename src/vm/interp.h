/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2002 Dean Hall
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __INTERP_H__
#define __INTERP_H__
/**
 * VM Interpreter
 *
 * VM interpreter header.
 *
 * Log
 * ---
 *
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/** frame pointer ; currently for single thread */
/* XXX not valid cuz interpret() is reentrant and FP is set at top of interp */
/*#define FP              (gVmGlobal.pframe)*/
#define FP              pframe
/** main module pointer (referred to by root frame) */
#define MP              (gVmGlobal.pmod)
/** instruction pointer */
#define IP              (FP->fo_ip)
/** argument stack pointer */
#undef SP
#define SP              (FP->fo_sp)
/** memspace where the frame's func's CO came from */
#define MS              (FP->fo_memspace)

/** top of stack */
#define TOS             (*(SP - 1))
/** one under TOS */
#define TOS1            (*(SP - 2))
/** two under TOS */
#define TOS2            (*(SP - 3))
/** three under TOS */
#define TOS3            (*(SP - 4))
/** index into stack; 0 is top, 1 is next */
#define STACK(n)        (*(SP - ((n) + 1)))
/** pops an obj from the stack */
#define PM_POP()        (*(--SP))
/** pushes an obj on the stack */
#define PM_PUSH(pobj)   (*(SP++) = (pobj))
/** gets the argument (S16) from the instruction stream */
#define GET_ARG()       mem_getWord(MS, &IP)

/** pushes an obj in the only stack slot of the native frame */
#define NATIVE_SET_TOS(pobj) (gVmGlobal.nativeframe.nf_stack = \
                        (pobj))
/** gets the nth local var from the native frame locals */
#define NATIVE_GET_LOCAL(n) (gVmGlobal.nativeframe.nf_locals[n])
/** gets a pointer to the frame that called this native fxn */
#define NATIVE_GET_PFRAME()   (pframe)
/** gets the number of args passed to the native fxn */
#define NATIVE_GET_NUM_ARGS() (numargs)


/***************************************************************
 * Types
 **************************************************************/

/**
 * COMPARE_OP enum.
 * Used by the COMPARE_OP bytecode to determine
 * which type of compare to perform.
 * Must match those defined in Python.
 */
typedef enum PmCompare_e
{
    COMP_LT = 0,            /**< less than */
    COMP_LE,                /**< less than or equal */
    COMP_EQ,                /**< equal */
    COMP_NE,                /**< not equal */
    COMP_GT,                /**< greater than */
    COMP_GE,                /**< greater than or equal */
    COMP_IN,                /**< is in */
    COMP_NOT_IN,            /**< is not in */
    COMP_IS,                /**< is */
    COMP_IS_NOT,            /**< is not */
    COMP_EXN_MATCH          /**< do exceptions match */
} PmCompare_t, *pPmCompare_t;

/**
 * Interpreter return values
 *
 * Used to control interpreter loop
 * and indicate return value.
 * Negative values indicate erroneous results.
 * Positive values indicate "continue interpreting",
 * but first do something special like reschedule threads
 * or (TBD) sweep the heap.
 */
typedef enum PmInterpCtrl_e
{
    /* other erroneous exits go here with negative values */
    INTERP_CTRL_ERR = -1,   /**< Generic error causes exit */
    INTERP_CTRL_EXIT = 0,   /**< Normal execution exit */
    INTERP_CTRL_CONT = 1,   /**< Continue interpreting */
    INTERP_CTRL_RESCHED = 2, /**< Reschedule threads */
    /* all positive values indicate "continue interpreting" */
} PmInterpCtrl_t, *pPmInterpCtrl_t;

/**
 * Byte code enumeration
 */
typedef enum PmBcode_e
{
    /*
     * Python source to create this list:
     * import dis
     * o = dis.opname
     * for i in range(256):
     *     if o[i][0] != '<':
     *         print "\t%s," % o[i]
     *     else:
     *         print "\tUNUSED_%02X," % i
     */
    STOP_CODE = 0,              /* 0x00 */
    POP_TOP,
    ROT_TWO,
    ROT_THREE,
    DUP_TOP,
    ROT_FOUR,
    UNUSED_06,
    UNUSED_07,
    UNUSED_08,
    UNUSED_09,
    UNARY_POSITIVE,             /* d010 */
    UNARY_NEGATIVE,
    UNARY_NOT,
    UNARY_CONVERT,
    UNUSED_0E,
    UNARY_INVERT,
    UNUSED_10,                  /* 0x10 */
    UNUSED_11,
    UNUSED_12,
    BINARY_POWER,
    BINARY_MULTIPLY,            /* d020 */
    BINARY_DIVIDE,
    BINARY_MODULO,
    BINARY_ADD,
    BINARY_SUBTRACT,
    BINARY_SUBSCR,
    UNUSED_1A,
    UNUSED_1B,
    UNUSED_1C,
    UNUSED_1D,
    SLICE_0,                    /* d030 */
    SLICE_1,
    SLICE_2,                    /* 0x20 */
    SLICE_3,
    UNUSED_22,
    UNUSED_23,
    UNUSED_24,
    UNUSED_25,
    UNUSED_26,
    UNUSED_27,
    STORE_SLICE_0,              /* d040 */
    STORE_SLICE_1,
    STORE_SLICE_2,
    STORE_SLICE_3,
    UNUSED_2C,
    UNUSED_2D,
    UNUSED_2E,
    UNUSED_2F,
    UNUSED_30,                  /* 0x30 */
    UNUSED_31,
    DELETE_SLICE_0,             /* d050 */
    DELETE_SLICE_1,
    DELETE_SLICE_2,
    DELETE_SLICE_3,
    UNUSED_36,
    INPLACE_ADD,
    INPLACE_SUBTRACT,
    INPLACE_MULTIPLY,
    INPLACE_DIVIDE,
    INPLACE_MODULO,
    STORE_SUBSCR,               /* d060 */
    DELETE_SUBSCR,
    BINARY_LSHIFT,
    BINARY_RSHIFT,
    BINARY_AND,                 /* 0x40 */
    BINARY_XOR,
    BINARY_OR,
    INPLACE_POWER,
    UNUSED_44,
    UNUSED_45,
    PRINT_EXPR,                 /* d070 */
    PRINT_ITEM,
    PRINT_NEWLINE,
    PRINT_ITEM_TO,
    PRINT_NEWLINE_TO,
    INPLACE_LSHIFT,
    INPLACE_RSHIFT,
    INPLACE_AND,
    INPLACE_XOR,
    INPLACE_OR,
    BREAK_LOOP,                 /* 0x50 *//* d080 */
    UNUSED_51,
    LOAD_LOCALS,
    RETURN_VALUE,
    IMPORT_STAR,
    EXEC_STMT,
    UNUSED_56,
    POP_BLOCK,
    END_FINALLY,
    BUILD_CLASS,
    STORE_NAME,                 /* d090 */
    DELETE_NAME,
    UNPACK_SEQUENCE,
    UNUSED_5D,
    UNUSED_5E,
    STORE_ATTR,
    DELETE_ATTR,                /* 0x60 */
    STORE_GLOBAL,
    DELETE_GLOBAL,
    DUP_TOPX,
    LOAD_CONST,                 /* d100 */
    LOAD_NAME,
    BUILD_TUPLE,
    BUILD_LIST,
    BUILD_MAP,
    LOAD_ATTR,
    COMPARE_OP,
    IMPORT_NAME,
    IMPORT_FROM,
    UNUSED_6D,
    JUMP_FORWARD,               /* d110 */
    JUMP_IF_FALSE,
    JUMP_IF_TRUE,               /* 0x70 */
    JUMP_ABSOLUTE,
    FOR_LOOP,
    UNUSED_73,
    LOAD_GLOBAL,
    UNUSED_75,
    UNUSED_76,
    CONTINUE_LOOP,
    SETUP_LOOP,                 /* d120 */
    SETUP_EXCEPT,
    SETUP_FINALLY,
    UNUSED_7B,
    LOAD_FAST,
    STORE_FAST,
    DELETE_FAST,
    SET_LINENO,
    UNUSED_80,                  /* 0x80 */
    UNUSED_81,
    RAISE_VARARGS,              /* d130 */
    CALL_FUNCTION,
    MAKE_FUNCTION,
    BUILD_SLICE,
    MAKE_CLOSURE,
    LOAD_CLOSURE,
    LOAD_DEREF,
    STORE_DEREF,
    UNUSED_8A,
    UNUSED_8B,
    CALL_FUNCTION_VAR,          /* d140 */
    CALL_FUNCTION_KW,
    CALL_FUNCTION_VAR_KW,
    EXTENDED_ARG,
    UNUSED_90, UNUSED_91, UNUSED_92, UNUSED_93,
    UNUSED_94, UNUSED_95, UNUSED_96, UNUSED_97,
    UNUSED_98, UNUSED_99, UNUSED_9A, UNUSED_9B,
    UNUSED_9C, UNUSED_9D, UNUSED_9E, UNUSED_9F,
    UNUSED_A0, UNUSED_A1, UNUSED_A2, UNUSED_A3,
    UNUSED_A4, UNUSED_A5, UNUSED_A6, UNUSED_A7,
    UNUSED_A8, UNUSED_A9, UNUSED_AA, UNUSED_AB,
    UNUSED_AC, UNUSED_AD, UNUSED_AE, UNUSED_AF,
    UNUSED_B0, UNUSED_B1, UNUSED_B2, UNUSED_B3,
    UNUSED_B4, UNUSED_B5, UNUSED_B6, UNUSED_B7,
    UNUSED_B8, UNUSED_B9, UNUSED_BA, UNUSED_BB,
    UNUSED_BC, UNUSED_BD, UNUSED_BE, UNUSED_BF,
    UNUSED_C0, UNUSED_C1, UNUSED_C2, UNUSED_C3,
    UNUSED_C4, UNUSED_C5, UNUSED_C6, UNUSED_C7,
    UNUSED_C8, UNUSED_C9, UNUSED_CA, UNUSED_CB,
    UNUSED_CC, UNUSED_CD, UNUSED_CE, UNUSED_CF,
    UNUSED_D0, UNUSED_D1, UNUSED_D2, UNUSED_D3,
    UNUSED_D4, UNUSED_D5, UNUSED_D6, UNUSED_D7,
    UNUSED_D8, UNUSED_D9, UNUSED_DA, UNUSED_DB,
    UNUSED_DC, UNUSED_DD, UNUSED_DE, UNUSED_DF,
    UNUSED_E0, UNUSED_E1, UNUSED_E2, UNUSED_E3,
    UNUSED_E4, UNUSED_E5, UNUSED_E6, UNUSED_E7,
    UNUSED_E8, UNUSED_E9, UNUSED_EA, UNUSED_EB,
    UNUSED_EC, UNUSED_ED, UNUSED_EE, UNUSED_EF,
    UNUSED_F0, UNUSED_F1, UNUSED_F2, UNUSED_F3,
    UNUSED_F4, UNUSED_F5, UNUSED_F6, UNUSED_F7,
    UNUSED_F8, UNUSED_F9, UNUSED_FA, UNUSED_FB,
    UNUSED_FC, UNUSED_FD, UNUSED_FE, UNUSED_FF
} PmBcode_t, *pPmBcode_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * System error, immediate halt with report.
 *
 * @param   release ID of the interpreter release.
 * @param   file ID of the interpreter file reporting the error.
 * @param   line Line number of the interpreter file 
 *               reporting the error.
 */
void py_err(S16 release, S16 file, S16 line);


/**
 * Interpret the function's bcode.
 *
 * The given obj may be a function, module, or class.
 * Create a frame for the given function and begin to interpret
 * the bytecode to which it refers.
 *
 * @param   pfunc Ptr to function object to interpret.
 * @return  nothing.
 */
PmReturn_t interpret(pPmFunc_t pfunc);

#endif /* __INTERP_H__ */
