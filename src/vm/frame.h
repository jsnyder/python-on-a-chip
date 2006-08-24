#ifndef __FRAME_H__
#define __FRAME_H__
/**
 * VM Frame
 *
 * VM frame header.
 *
 * @author      Dean Hall
 * @file        frame.h
 *
 * Log:
 *
 * 2002/12/15   Frame's memspace set to use one byte.
 * 2002/04/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/***************************************************************
 * Constants
 **************************************************************/

/** 
 * the maximum number of local variables 
 * a native function can have.
 * This defines the length of the locals array
 * in the native frame struct.
 */
#define NATIVE_NUM_LOCALS   8


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/**
 * Block Type
 *
 * Numerical values to put in the 'b_type' field
 * of the tPyBlockType struct.
 */
typedef enum PyBlockType_e
{
    /** invalide block type */
    B_INVALID = 0,
    /** loop type */
    B_LOOP,
    /** try type */
    B_TRY
} PyBlockType_t, *pPyBlockType_t;


/**
 * Block
 *
 * Extra info for loops and trys (others?)
 * Frames use linked list of blocks to handle
 * nested loops and try-catch blocks.
 */
typedef struct PyBlock_s
{
    /** obligatory obj descriptor */
    PyObjDesc_t     od;
    /** ptr to backup stack ptr */
    pPyObj_t       *b_sp;
    /** handler fxn obj */
    P_S8            b_handler;
    /** block type */
    PyBlockType_t   b_type:8;
    /** next block in stack */
    struct PyBlock_s *next;
} PyBlock_t, *pPyBlock_t;


/**
 * Frame
 *
 * A struct that holds the execution frame
 * of a function, including the stack, local vars
 * and pointer to the code object.
 *
 * This struct doesn't declare the stack.
 * frame_new() is responsible for allocating the extra memory
 * at the tail of fo_locals[] to hold both the locals and stack.
 */
typedef struct PyFrame_s
{
    /** obligatory obj descriptor */
    PyObjDesc_t     od;
    /** ptr to previous frame obj */
    struct PyFrame_s *fo_back;
    /** ptr to fxn obj */
    pPyFunc_t       fo_func;
    /** mem space where func's CO comes from */
    PyMemSpace_t    fo_memspace:8;
    /** instrxn ptr (pts into memspace) */
    P_S8            fo_ip;
    /** current source line num */
    U16             fo_line;
    /** linked list of blocks */
    pPyBlock_t      fo_blockstack;
    /** local attributes dict (non-fast locals) */
    pPyDict_t       fo_attrs;
    /** global attributes dict (pts to root frame's globals */
    pPyDict_t       fo_globals;
    /** points to next empty slot in fo_locals (1 past TOS) */
    pPyObj_t       *fo_sp;
    /** array of local vars and stack (space appended at alloc) */
    pPyObj_t        fo_locals[0];
} PyFrame_t, *pPyFrame_t;

/**
 * Native Frame
 *
 * A struct that holds the execution frame
 * of a native function, including the args and
 * single stack slot, and pointer to the code object.
 *
 * This struct doesn't need an OD because it is only
 * used statically in the globals struct.
 * There's only one native frame, the global one.
 * This happens because a native function is a leaf node
 * in the call tree (a native func can't call python funcs).
 */
typedef struct PyNativeFrame_s
{
    /** ptr to previous frame obj */
    struct PyFrame_s *nf_back;
    /** ptr to fxn obj */
    pPyFunc_t       nf_func;
    /** single stack slot */
    pPyObj_t        nf_stack;
    /** local vars */
    pPyObj_t        nf_locals[NATIVE_NUM_LOCALS];
} PyNativeFrame_t, *pPyNativeFrame_t;


/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

/**
 * Allocate space for a new frame, fill its fields
 * with respect to the given function object.
 * Return pointer to the new frame.
 *
 * @param   pfunc ptr to Function object.
 * @param   r_pobj Return value; the new frame.
 * @return  Return status.
 */
PyReturn_t frame_new(pPyObj_t pfunc, pPyObj_t * r_pobj);

/**
 * TODO
 * #define PY_FRAME_GET_CONST(pfo, indx)
 * #define PY_FRAME_GET_LOCAL(pfo, indx)
 * #define PY_FRAME_SET_LOCAL(pfo, indx, pod)
 * #define PY_FRAME_GET_ATTR(pfo, namei)
 * #define PY_FRAME_SET_ATTR(pfo, namei, pod)
 */

#endif /* __FRAME_H__ */
