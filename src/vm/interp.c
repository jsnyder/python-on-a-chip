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

#undef __FILE_ID__
#define __FILE_ID__ 0x09

/**
 * VM Interpreter
 *
 * VM interpreter operations.
 *
 * Log
 * ---
 *
 * 2007/04/14   #102: Implement the remaining IMPORT_ bytecodes
 * 2007/01/29   #80: Fix DUP_TOPX bytecode
 * 2007/01/17   #76: Print will differentiate on strings and print tuples
 * 2007/01/09   #75: Changed IMPORT_NAME, printing (P.Adelt)
 * 2007/01/09   #75: Restructed for green threading (P.Adelt)
 * 2006/09/29   #45: Finish interpret loop edits
 * 2006/09/10   #20: Implement assert statement
 * 2006/08/31   #9: Fix BINARY_SUBSCR for case stringobj[intobj]
 * 2006/08/30   #6: Have pmImgCreator append a null terminator to image list
 * 2006/08/29   #12: Make mem_*() funcs use RAM when target is DESKTOP
 * 2006/08/29   #15 - All mem_*() funcs and pointers in the vm should use
 *              unsigned not signed or void
 * 2002/12/08   Print statement support removed,
 *              use platform native function to print instead.
 * 2002/11/10   Fixed BREAK_LOOP to jump to handler.
 * 2002/05/04   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

#include "pm.h"


/***************************************************************
 * Macros
 **************************************************************/

/** if retval is not OK, break from the interpreter */
#define PM_BREAK_IF_ERROR(retval) if((retval) != PM_RET_OK)break


/***************************************************************
 * Prototypes
 **************************************************************/

extern PmReturn_t (*std_nat_fxn_table[]) (pPmFrame_t *);
extern PmReturn_t (*usr_nat_fxn_table[]) (pPmFrame_t *);


/***************************************************************
 * Functions
 **************************************************************/

PmReturn_t
interpret(const uint8_t returnOnNoThreads)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj1 = C_NULL;
    pPmObj_t pobj2 = C_NULL;
    pPmObj_t pobj3 = C_NULL;
    int16_t t16 = 0;
    int8_t t8 = 0;
    uint8_t bc;

    /* Activate a thread the first time */
    retval = interp_reschedule();
    PM_RETURN_IF_ERROR(retval);

    /* Interpret loop */
    while (1)
    {
        if (gVmGlobal.pthread == C_NULL)
        {
            if (returnOnNoThreads)
            {
                /* User chose to return on no threads left */
                return retval;
            }

            /*
             * Without a frame there is nothing to execute, so reschedule
             * (possibly activating a recently added thread).
             */
            retval = interp_reschedule();
            PM_BREAK_IF_ERROR(retval);
            continue;
        }

        /* Reschedule threads if flag is true?*/
        if (gVmGlobal.reschedule)
        {
            retval = interp_reschedule();
            PM_BREAK_IF_ERROR(retval);
        }

        /* Get byte; the func post-incrs IP */
        bc = mem_getByte(MS, &IP);
        switch (bc)
        {
            case POP_TOP:
                pobj1 = PM_POP();
                continue;

            case ROT_TWO:
                pobj1 = TOS;
                TOS = TOS1;
                TOS1 = pobj1;
                continue;

            case ROT_THREE:
                pobj1 = TOS;
                TOS = TOS1;
                TOS1 = TOS2;
                TOS2 = pobj1;
                continue;

            case DUP_TOP:
                pobj1 = TOS;
                PM_PUSH(pobj1);
                continue;

            case ROT_FOUR:
                pobj1 = TOS;
                TOS = TOS1;
                TOS1 = TOS2;
                TOS2 = TOS3;
                TOS3 = pobj1;
                continue;

            case NOP:
                continue;

            case UNARY_POSITIVE:
                /* Raise TypeError if TOS is not an int */
                if (OBJ_GET_TYPE(TOS) != OBJ_TYPE_INT)
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* When TOS is an int, this is a no-op */
                continue;

            case UNARY_NEGATIVE:
                pobj1 = PM_POP();
                retval = int_negative(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case UNARY_NOT:
                pobj1 = PM_POP();
                if (obj_isFalse(pobj1))
                {
                    PM_PUSH(PM_TRUE);
                }
                else
                {
                    PM_PUSH(PM_FALSE);
                }
                continue;

            case UNARY_INVERT:
                /* Raise TypeError if it's not an int */
                if (OBJ_GET_TYPE(TOS) != OBJ_TYPE_INT)
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* Otherwise perform bit-wise complement */
                pobj1 = PM_POP();
                retval = int_bitInvert(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case BINARY_POWER:
            case INPLACE_POWER:
                /* Pop args right to left */
                pobj2 = PM_POP();
                pobj1 = TOS;

                /* Calculate integer power */
                retval = int_pow(pobj1, pobj2, &pobj3);
                PM_BREAK_IF_ERROR(retval);

                /* Set return value */
                TOS = pobj3;
                continue;

            case GET_ITER:
                /* Get the sequence from the top of stack */
                pobj1 = TOS;

                /* Convert sequence to sequence-iterator */
                retval = seqiter_new(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);

                /* Put sequence-iterator on top of stack */
                TOS = pobj2;
                continue;

            case BINARY_MULTIPLY:
            case INPLACE_MULTIPLY:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val *
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* If it's a list replication operation */
                else if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                         && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_LST))
                {
                    /* Int number of times to duplicate */
                    pobj1 = PM_POP();
                    if (OBJ_GET_TYPE(pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }
                    t16 = (int16_t)((pPmInt_t)pobj1)->val;

                    /* List that is copied */
                    pobj2 = PM_POP();
                    retval = list_replicate(pobj2, t16, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_DIVIDE:
            case INPLACE_DIVIDE:
            case BINARY_FLOOR_DIVIDE:
            case INPLACE_FLOOR_DIVIDE:
                /* Raise TypeError if args aren't ints */
                if ((OBJ_GET_TYPE(TOS) != OBJ_TYPE_INT)
                    || (OBJ_GET_TYPE(TOS1) != OBJ_TYPE_INT))
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* Raise ZeroDivisionError if denominator is zero */
                if (((pPmInt_t)TOS)->val == 0)
                {
                    PM_RAISE(retval, PM_RET_EX_ZDIV);
                    break;
                }

                /* Otherwise perform operation */
                pobj1 = PM_POP();
                pobj2 = PM_POP();
                retval = int_new(((pPmInt_t)pobj2)->val /
                                 ((pPmInt_t)pobj1)->val, &pobj3);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case BINARY_MODULO:
            case INPLACE_MODULO:
                /* Raise TypeError if args aren't ints */
                if ((OBJ_GET_TYPE(TOS) != OBJ_TYPE_INT)
                    || (OBJ_GET_TYPE(TOS1) != OBJ_TYPE_INT))
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* Raise ZeroDivisionError if denominator is zero */
                if (((pPmInt_t)TOS)->val == 0)
                {
                    PM_RAISE(retval, PM_RET_EX_ZDIV);
                    break;
                }

                /* Otherwise perform operation */
                pobj1 = PM_POP();
                pobj2 = PM_POP();
                retval = int_new(((pPmInt_t)pobj2)->val %
                                 ((pPmInt_t)pobj1)->val, &pobj3);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case BINARY_ADD:
            case INPLACE_ADD:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val +
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_SUBTRACT:
            case INPLACE_SUBTRACT:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val -
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_SUBSCR:
                /* Implements TOS = TOS1[TOS]. */

                /* Get index */
                pobj1 = PM_POP();

                /* Get sequence */
                pobj2 = PM_POP();

                if (OBJ_GET_TYPE(pobj2) == OBJ_TYPE_DIC)
                {
                    retval = dict_getItem(pobj2, pobj1, &pobj3);
                }
                else
                {
                    /* Raise a TypeError if index is not an Integer */
                    if (OBJ_GET_TYPE(pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }

                    /* Ensure the index doesn't overflow */
                    C_ASSERT(((pPmInt_t)pobj1)->val <= 0x0000FFFF);
                    t16 = (int16_t)((pPmInt_t)pobj1)->val;

                    retval = seq_getSubscript(pobj2, t16, &pobj3);
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case SLICE_0:
                /* Implements TOS = TOS[:], push a copy of the sequence */

                /* Get sequence */
                pobj1 = PM_POP();

                /* If it's a string */
                if (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_STR)
                {
                    /* Just copy the pointer, since Strings are immutable */
                    pobj2 = pobj1;
                }

                /* If it's a tuple */
                else if (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_TUP)
                {
                    retval = tuple_copy(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* If it's a list */
                else if (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_LST)
                {
                    retval = list_copy(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* TypeError; unhashable type */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                PM_PUSH(pobj2);
                continue;

            case STORE_SUBSCR:
                /* Implements TOS1[TOS] = TOS2 */
                pobj1 = PM_POP();
                pobj2 = PM_POP();
                pobj3 = PM_POP();

                /* If it's a list */
                if (OBJ_GET_TYPE(pobj2) == OBJ_TYPE_LST)
                {
                    /* Ensure subscr is an int */
                    if (OBJ_GET_TYPE(pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }
                    /* Set the list item */
                    retval = list_setItem(pobj2,
                                          (int16_t)(((pPmInt_t)pobj1)->val),
                                          pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* If it's a dict */
                if (OBJ_GET_TYPE(pobj2) == OBJ_TYPE_DIC)
                {
                    /* Set the dict item */
                    retval = dict_setItem(pobj2, pobj1, pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* TypeError for all else */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_LSHIFT:
            case INPLACE_LSHIFT:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val <<
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_RSHIFT:
            case INPLACE_RSHIFT:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val >>
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_AND:
            case INPLACE_AND:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val &
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_XOR:
            case INPLACE_XOR:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val ^
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_OR:
            case INPLACE_OR:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val |
                                     ((pPmInt_t)pobj1)->val, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

#ifdef HAVE_PRINT
            case PRINT_EXPR:
                /* Print interactive expression */
                /* Fallthrough */

            case PRINT_ITEM:
                /* Print out topmost stack element */
                pobj1 = PM_POP();
                retval = obj_print(pobj1, (uint8_t)0);
                PM_BREAK_IF_ERROR(retval);
                if (bc != PRINT_EXPR)
                {
                    continue;
                }
                /* If PRINT_EXPR, Fallthrough to print a newline */

            case PRINT_NEWLINE:
                retval = plat_putByte('\n');
                PM_BREAK_IF_ERROR(retval);
                continue;
#endif /* HAVE_PRINT */

            case BREAK_LOOP:
            {
                pPmBlock_t pb1 = FP->fo_blockstack;

                /* Ensure there's a block */
                C_ASSERT(pb1 != C_NULL);

                /* Delete blocks until first loop block */
                while ((pb1->b_type != B_LOOP) && (pb1->next != C_NULL))
                {
                    pobj2 = (pPmObj_t)pb1;
                    pb1 = pb1->next;
                    retval = heap_freeChunk(pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* Test again outside while loop */
                PM_BREAK_IF_ERROR(retval);

                /* Restore SP */
                SP = pb1->b_sp;

                /* Goto handler */
                IP = pb1->b_handler;

                /* Pop and delete this block */
                FP->fo_blockstack = pb1->next;
                retval = heap_freeChunk((pPmObj_t)pb1);
                PM_BREAK_IF_ERROR(retval);
            }
                continue;

            case LOAD_LOCALS:
                /* Pushes local attrs dict of current frame */
                /* WARNING: does not copy fo_locals to attrs */
                PM_PUSH((pPmObj_t)FP->fo_attrs);
                continue;

            case RETURN_VALUE:
                /* Get expiring frame's TOS */
                pobj2 = PM_POP();

#if __DEBUG__
                /* #109: Check that stack should now be empty */
                /* Get the number of local variables for this code obj */
                uint8_t const *paddr = FP->fo_func->f_co->co_codeimgaddr
                                       + CI_STACKSIZE_FIELD + 1;
                t8 = mem_getByte(FP->fo_func->f_co->co_memspace, &paddr);

                /* SP should point to one past the end of the locals */
/*                C_ASSERT(SP == &(FP->fo_locals[t8]));*/
#endif

                /* Keep ref of expiring frame */
                pobj1 = (pPmObj_t)FP;

                /* If no previous frame, quit thread */
                if (FP->fo_back == C_NULL)
                {
                    gVmGlobal.pthread->interpctrl = INTERP_CTRL_EXIT;
                    retval = PM_RET_OK;
                    break;
                }

                /* Otherwise return to previous frame */
                FP = FP->fo_back;

                /*
                 * Push frame's return val, except if the expiring frame
                 * was due to an import statement
                 */
                if (!(((pPmFrame_t)pobj1)->fo_isImport))
                {
                    PM_PUSH(pobj2);
                }

                /* Deallocate expired frame */
                PM_BREAK_IF_ERROR(heap_freeChunk(pobj1));
                continue;

            case IMPORT_STAR:
                /* #102: Implement the remaining IMPORT_ bytecodes */
                /* Expect a module on the top of the stack */
                C_ASSERT(OBJ_GET_TYPE(TOS) == OBJ_TYPE_MOD);
                pobj1 = PM_POP();

                /* Update FP's attrs with those of the module on the stack */
                retval = dict_update((pPmObj_t)FP->fo_attrs,
                                     (pPmObj_t)((pPmFunc_t)pobj1)->f_attrs);
                PM_BREAK_IF_ERROR(retval);
                continue;

            case POP_BLOCK:
            {
                /* Get ptr to top block */
                pPmBlock_t pb = FP->fo_blockstack;

                /* If there's no block, raise SystemError */
                C_ASSERT(pb != C_NULL);

                /* Pop block */
                FP->fo_blockstack = pb->next;

                /* Set stack to previous level */
                SP = pb->b_sp;

                /* Delete block */
                PM_BREAK_IF_ERROR(heap_freeChunk((pPmObj_t)pb));
                continue;

            }

            /***************************************************
             * All bytecodes after 90 (0x5A) have a 2-byte arg
             * that needs to be swallowed using GET_ARG().
             **************************************************/

            case STORE_NAME:
                /* Get name index */
                t16 = GET_ARG();

                /* Get value */
                pobj1 = PM_POP();

                /* Get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];

                /* Set key=val in current frame's attrs dict */
                retval = dict_setItem((pPmObj_t)FP->fo_attrs, pobj2, pobj1);
                PM_BREAK_IF_ERROR(retval);
                continue;

            case UNPACK_SEQUENCE:
                /* Get ptr to sequence */
                pobj1 = PM_POP();

                /*
                 * Get the length of the sequence; this will
                 * raise TypeError if obj is not a sequence.
                 *
                 * #59: Unpacking to a Dict shall not be supported
                 */
                retval = seq_getLength(pobj1, &t16);
                if (retval != PM_RET_OK)
                {
                    GET_ARG();
                    break;
                }

                /* Raise ValueError if seq length does not match num args */
                if (t16 != GET_ARG())
                {
                    PM_RAISE(retval, PM_RET_EX_VAL);
                    break;
                }

                /* Push sequence's objs onto stack */
                for (; --t16 >= 0;)
                {
                    retval = seq_getSubscript(pobj1, t16, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj2);
                }

                /* Test again outside the for loop */
                PM_BREAK_IF_ERROR(retval);
                continue;

            case FOR_ITER:
                t16 = GET_ARG();
                pobj1 = TOS;

                /* Get the next item in the sequence iterator */
                retval = seqiter_getNext(pobj1, &pobj2);

                /* If StopIteration, pop iterator and jump outside loop */
                if (retval == PM_RET_EX_STOP)
                {
                    pobj1 = PM_POP();
                    retval = PM_RET_OK;
                    IP += t16;
                    continue;
                }

                /* Push the next item onto the stack */
                PM_PUSH(pobj2);
                continue;

            case STORE_ATTR:
                /* TOS.name = TOS1 */
                /* Get names index */
                t16 = GET_ARG();

                /* Get obj */
                pobj1 = PM_POP();

                /* Get attrs dict from obj */
                if ((OBJ_GET_TYPE(pobj1) == OBJ_TYPE_FXN)
                    || (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_MOD))
                {
                    pobj2 = (pPmObj_t)((pPmFunc_t)pobj1)->f_attrs;
                }
                else if ((OBJ_GET_TYPE(pobj1) == OBJ_TYPE_CLO)
                         || (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_CLI)
                         || (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_EXN))
                {
                    pobj2 = (pPmObj_t)((pPmClass_t)pobj1)->cl_attrs;
                }

                /* Other types result in an AttributeError */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_ATTR);
                    break;
                }

                /* If attrs is not a dict, raise SystemError */
                if (OBJ_GET_TYPE(pobj2) != OBJ_TYPE_DIC)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }

                /* Get name/key obj */
                pobj3 = FP->fo_func->f_co->co_names->val[t16];

                /* Set key=val in obj's dict */
                retval = dict_setItem(pobj2, pobj3, PM_POP());
                PM_BREAK_IF_ERROR(retval);
                continue;

            case STORE_GLOBAL:
                /* Get name index */
                t16 = GET_ARG();

                /* Get value */
                pobj1 = PM_POP();

                /* Get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];

                /* Set key=val in global dict */
                retval = dict_setItem((pPmObj_t)FP->fo_globals, pobj2, pobj1);
                PM_BREAK_IF_ERROR(retval);
                continue;

            case DUP_TOPX:
                t16 = GET_ARG();
                if (t16 == 1)
                {
                    pobj1 = TOS;
                    PM_PUSH(pobj1);
                }
                else if (t16 == 2)
                {
                    pobj1 = TOS;
                    pobj2 = TOS1;
                    PM_PUSH(pobj2);
                    PM_PUSH(pobj1);
                }
                else if (t16 == 3)
                {
                    pobj1 = TOS;
                    pobj2 = TOS1;
                    pobj3 = TOS2;
                    PM_PUSH(pobj3);
                    PM_PUSH(pobj2);
                    PM_PUSH(pobj1);
                }
                else
                {
                    /* Python compiler is responsible for keeping arg <= 3 */
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }
                continue;

            case LOAD_CONST:
                /* Get const's index in CO */
                t16 = GET_ARG();

                /* Push const on stack */
                PM_PUSH(FP->fo_func->f_co->co_consts->val[t16]);
                continue;

            case LOAD_NAME:
                /* Get name index */
                t16 = GET_ARG();

                /* Get name from names tuple */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];

                /* Get value from frame's attrs dict */
                retval = dict_getItem((pPmObj_t)FP->fo_attrs, pobj1, &pobj2);
                if (retval == PM_RET_EX_KEY)
                {
                    /* Get val from globals */
                    retval = dict_getItem((pPmObj_t)FP->fo_globals,
                                          pobj1, &pobj2);
                    if (retval == PM_RET_EX_KEY)
                    {
                        /* Get val from builtins */
                        retval = dict_getItem(PM_PBUILTINS, pobj1, &pobj2);
                        if (retval == PM_RET_EX_KEY)
                        {
                            /* Name not defined, raise NameError */
                            PM_RAISE(retval, PM_RET_EX_NAME);
                            break;
                        }
                    }
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case BUILD_TUPLE:
                /* Get num items */
                t16 = GET_ARG();
                retval = tuple_new(t16, &pobj1);
                PM_BREAK_IF_ERROR(retval);

                /* Fill tuple with ptrs to objs */
                for (; --t16 >= 0;)
                {
                    ((pPmTuple_t)pobj1)->val[t16] = PM_POP();
                }
                PM_PUSH(pobj1);
                continue;

            case BUILD_LIST:
                t16 = GET_ARG();
                retval = list_new(&pobj1);
                PM_BREAK_IF_ERROR(retval);
                for (; --t16 >= 0;)
                {
                    /* Get obj */
                    pobj2 = PM_POP();

                    /* Insert obj into list */
                    retval = list_insert(pobj1, 0, pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }
                /* Test again outside for loop */
                PM_BREAK_IF_ERROR(retval);

                /* push list onto stack */
                PM_PUSH(pobj1);
                continue;

            case BUILD_MAP:
                /* Argument is ignored */
                t16 = GET_ARG();
                retval = dict_new(&pobj1);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj1);
                continue;

            case LOAD_ATTR:
                t16 = GET_ARG();

                /* Get obj that has the attrs */
                pobj1 = PM_POP();

                /* Get attrs dict from obj */
                if ((OBJ_GET_TYPE(pobj1) == OBJ_TYPE_FXN) ||
                    (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_MOD))
                {
                    pobj1 = (pPmObj_t)((pPmFunc_t)pobj1)->f_attrs;
                }
                else if ((OBJ_GET_TYPE(pobj1) == OBJ_TYPE_CLO)
                         || (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_CLI)
                         || (OBJ_GET_TYPE(pobj1) == OBJ_TYPE_EXN))
                {
                    pobj1 = (pPmObj_t)((pPmClass_t)pobj1)->cl_attrs;
                }

                /* Other types result in an AttributeError */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_ATTR);
                    break;
                }

                /* If attrs is not a dict, raise SystemError */
                if (OBJ_GET_TYPE(pobj1) != OBJ_TYPE_DIC)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }

                /* Get name */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];

                /* Push attr with given name onto stack */
                retval = dict_getItem(pobj1, pobj2, &pobj3);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case COMPARE_OP:
                retval = PM_RET_OK;
                pobj1 = PM_POP();
                pobj2 = PM_POP();
                t16 = GET_ARG();

                /* Handle all integer-to-integer comparisons */
                if ((OBJ_GET_TYPE(pobj1) == OBJ_TYPE_INT) &&
                    (OBJ_GET_TYPE(pobj2) == OBJ_TYPE_INT))
                {
                    int32_t a = ((pPmInt_t)pobj2)->val;
                    int32_t b = ((pPmInt_t)pobj1)->val;

                    switch (t16)
                    {
                        /* *INDENT-OFF* */
                        case COMP_LT: t8 = (int8_t)(a <  b); break;
                        case COMP_LE: t8 = (int8_t)(a <= b); break;
                        case COMP_EQ: t8 = (int8_t)(a == b); break;
                        case COMP_NE: t8 = (int8_t)(a != b); break;
                        case COMP_GT: t8 = (int8_t)(a >  b); break;
                        case COMP_GE: t8 = (int8_t)(a >= b); break;
                        case COMP_IS: t8 = (int8_t)(pobj1 == pobj2); break;
                        case COMP_IS_NOT: t8 = (int8_t)(pobj1 != pobj2);break;
                        case COMP_IN:
                        case COMP_NOT_IN:
                            PM_RAISE(retval, PM_RET_EX_TYPE);
                            break;

                        default:
                            /* Other compares are not yet supported */
                            PM_RAISE(retval, PM_RET_EX_SYS);
                            break;
                        /* *INDENT-ON* */
                    }
                    PM_BREAK_IF_ERROR(retval);
                    pobj3 = (t8) ? PM_TRUE : PM_FALSE;
                }

                /* Handle non-integer comparisons */
                else
                {
                    retval = PM_RET_OK;
                    switch (t16)
                    {
                        case COMP_EQ:
                        case COMP_NE:
                            /* Handle equality for non-int types */
                            pobj3 = PM_FALSE;
                            t8 = obj_compare(pobj1, pobj2);
                            if (((t8 == C_SAME) && (t16 == COMP_EQ))
                                || ((t8 == C_DIFFER) && (t16 == COMP_NE)))
                            {
                                pobj3 = PM_TRUE;
                            }
                            else
                            {
                                pobj3 = PM_FALSE;
                            }
                            break;

                        case COMP_IN:
                        case COMP_NOT_IN:
                            /* Handle membership comparisons */
                            pobj3 = PM_FALSE;
                            retval = obj_isIn(pobj1, pobj2);
                            if (retval == PM_RET_OK)
                            {
                                if (t16 == COMP_IN)
                                {
                                    pobj3 = PM_TRUE;
                                }
                            }
                            else if (retval == PM_RET_NO)
                            {
                                retval = PM_RET_OK;
                                if (t16 == COMP_NOT_IN)
                                {
                                    pobj3 = PM_TRUE;
                                }
                            }
                            break;

                        default:
                            /* Other comparisons are not implemented */
                            PM_RAISE(retval, PM_RET_EX_SYS);
                            break;
                    }
                    PM_BREAK_IF_ERROR(retval);
                }
                PM_PUSH(pobj3);
                continue;

            case IMPORT_NAME:
                /* Get name index */
                t16 = GET_ARG();

                /* Get name String obj */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];

                /* Pop unused None object */
                pobj3 = PM_POP();

                /* Ensure "level" is -1; no support for relative import yet */
                pobj3 = TOS;
                C_ASSERT(obj_compare(pobj3, PM_NEGONE) == C_SAME);

                /* #110: Prevent importing previously-loaded module */
                /* If the named module is in globals, put it on the stack */
                retval = dict_getItem((pPmObj_t)FP->fo_globals, pobj1, &pobj2);
                if ((retval == PM_RET_OK)
                    && (OBJ_GET_TYPE(pobj2) == OBJ_TYPE_MOD))
                {
                    TOS = pobj2;
                    continue;
                }

                /* Load module from image */
                retval = mod_import(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);

                /* Put Module on top of stack */
                TOS = pobj2;

                /* Code after here is a duplicate of CALL_FUNCTION */
                /* Make frame object to interpret the module's root code */
                retval = frame_new(pobj2, &pobj3);
                PM_BREAK_IF_ERROR(retval);

                /* No arguments to pass */

                /* Keep ref to current frame */
                ((pPmFrame_t)pobj3)->fo_back = FP;

                /* Handle to have None popped on return */
                ((pPmFrame_t)pobj3)->fo_isImport = (uint8_t)1;

                /* Set new frame */
                FP = (pPmFrame_t)pobj3;
                continue;

            case IMPORT_FROM:
                /* #102: Implement the remaining IMPORT_ bytecodes */
                /* Expect the module on the top of the stack */
                C_ASSERT(OBJ_GET_TYPE(TOS) == OBJ_TYPE_MOD);
                pobj1 = TOS;

                /* Get the name of the object to import */
                t16 = GET_ARG();
                pobj2 = FP->fo_func->f_co->co_names->val[t16];

                /* Get the object from the module's attributes */
                retval = dict_getItem((pPmObj_t)((pPmFunc_t)pobj1)->f_attrs,
                                      pobj2, &pobj3);
                PM_BREAK_IF_ERROR(retval);

                /* Push the object onto the top of the stack */
                PM_PUSH(pobj3);
                continue;

            case JUMP_FORWARD:
                t16 = GET_ARG();
                IP += t16;
                continue;

            case JUMP_IF_FALSE:
                t16 = GET_ARG();
                if (obj_isFalse(TOS))
                {
                    IP += t16;
                }
                continue;

            case JUMP_IF_TRUE:
                t16 = GET_ARG();
                if (!obj_isFalse(TOS))
                {
                    IP += t16;
                }
                continue;

            case JUMP_ABSOLUTE:
            case CONTINUE_LOOP:
                /* Get target offset (bytes) */
                t16 = GET_ARG();

                /* Jump to base_ip + arg */
                IP = FP->fo_func->f_co->co_codeaddr + t16;
                continue;

            case LOAD_GLOBAL:
                /* Get name */
                t16 = GET_ARG();
                pobj1 = FP->fo_func->f_co->co_names->val[t16];

                /* Try globals first */
                retval = dict_getItem((pPmObj_t)FP->fo_globals,
                                      pobj1, &pobj2);

                /* If that didn't work, try builtins */
                if (retval == PM_RET_EX_KEY)
                {
                    retval = dict_getItem(PM_PBUILTINS, pobj1, &pobj2);

                    /* No such global, raise NameError */
                    if (retval == PM_RET_EX_KEY)
                    {
                        PM_RAISE(retval, PM_RET_EX_NAME);
                        break;
                    }
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case SETUP_LOOP:
            {
                uint8_t *pchunk;

                /* Get block span (bytes) */
                t16 = GET_ARG();

                /* Create block */
                retval = heap_getChunk(sizeof(PmBlock_t), &pchunk);
                PM_BREAK_IF_ERROR(retval);
                pobj1 = (pPmObj_t)pchunk;
                OBJ_SET_TYPE(pobj1, OBJ_TYPE_BLK);

                /* Store current stack pointer */
                ((pPmBlock_t)pobj1)->b_sp = SP;

                /* Default handler is to exit block/loop */
                ((pPmBlock_t)pobj1)->b_handler = IP + t16;
                ((pPmBlock_t)pobj1)->b_type = B_LOOP;

                /* Insert block into blockstack */
                ((pPmBlock_t)pobj1)->next = FP->fo_blockstack;
                FP->fo_blockstack = (pPmBlock_t)pobj1;
                continue;
            }

            case LOAD_FAST:
                t16 = GET_ARG();
                PM_PUSH(FP->fo_locals[t16]);
                continue;

            case STORE_FAST:
                t16 = GET_ARG();
                FP->fo_locals[t16] = PM_POP();
                continue;

            case RAISE_VARARGS:
                t16 = GET_ARG();

                /* Only supports taking 1 arg for now */
                if (t16 != 1)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }

                /* Raise type error if TOS is not an exception object */
                pobj1 = PM_POP();
                if (OBJ_GET_TYPE(pobj1) != OBJ_TYPE_EXN)
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* Push the traceback, parameter and exception object */
                PM_PUSH(PM_NONE);
                PM_PUSH(PM_NONE);
                PM_PUSH(pobj1);

                /* Get the exception's code attr */
                retval = dict_getItem((pPmObj_t)((pPmClass_t)pobj1)->cl_attrs,
                                      PM_CODE_STR, &pobj2);
                PM_BREAK_IF_ERROR(retval);

                /* Raise exception by breaking with retval set to code */
                PM_RAISE(retval, (PmReturn_t)(((pPmInt_t)pobj2)->val & 0xFF));
                break;

            case CALL_FUNCTION:
                /* Get num args */
                t16 = GET_ARG();

                /* Ensure no keyword args */
                if ((t16 & (uint16_t)0xFF00) != 0)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }

                /* Get the func */
                pobj1 = STACK(t16);

                C_ASSERT(OBJ_GET_TYPE(pobj1) == OBJ_TYPE_FXN);

                /* If it's regular func (not native) */
                if (OBJ_GET_TYPE(((pPmFunc_t)pobj1)->f_co) == OBJ_TYPE_COB)
                {
                    /*
                     * #132 Raise TypeError if num args does not match the
                     * code object's expected argcount
                     */
                    if ((t16 & ((uint8_t)0xFF)) !=
                        ((pPmFunc_t)pobj1)->f_co->co_argcount)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }

                    /* Make frame object to run the func object */
                    retval = frame_new(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);

                    /* Pass args to new frame */
                    while (--t16 >= 0)
                    {
                        /*
                         * Pop args from stack right to left,
                         * since args are pushed left to right,
                         */
                        ((pPmFrame_t)pobj2)->fo_locals[t16] = PM_POP();
                    }

                    /* Pop func obj */
                    pobj3 = PM_POP();

                    /* Keep ref to current frame */
                    ((pPmFrame_t)pobj2)->fo_back = FP;

                    /* Set new frame */
                    FP = (pPmFrame_t)pobj2;
                }

                /* If it's native func */
                else if (OBJ_GET_TYPE(((pPmFunc_t)pobj1)->f_co) ==
                         OBJ_TYPE_NOB)
                {
                    /* Ensure num args fits in native frame */
                    if (t16 > NATIVE_MAX_NUM_LOCALS)
                    {
                        PM_RAISE(retval, PM_RET_EX_SYS);
                        break;
                    }

                    /* Set number of locals (arguments) */
                    gVmGlobal.nativeframe.nf_numlocals = (uint8_t)t16;

                    /* Pop args from stack */
                    while (--t16 >= 0)
                    {
                        gVmGlobal.nativeframe.nf_locals[t16] = PM_POP();
                    }

#ifdef HAVE_GC
                    /* If the heap is low on memory, run the GC */
                    if (heap_getAvail() < HEAP_GC_NF_THRESHOLD)
                    {
                        retval = heap_gcRun();
                        PM_BREAK_IF_ERROR(retval);
                    }
#endif /* HAVE_GC */

                    /* Pop the function object (pobj2 is unused) */
                    pobj2 = PM_POP();

                    /* Get native function index */
                    pobj2 = (pPmObj_t)((pPmFunc_t)pobj1)->f_co;
                    t16 = ((pPmNo_t)pobj2)->no_funcindx;

                    /* Set flag, so the GC knows a native session is active */
                    gVmGlobal.nativeframe.nf_active = C_TRUE;

                    /*
                     * CALL NATIVE FXN: pass caller's frame and numargs
                     */
                    /* Positive index is a stdlib func */
                    if (t16 >= 0)
                    {
                        retval = std_nat_fxn_table[t16] (&FP);
                    }

                    /* Negative index is a usrlib func */
                    else
                    {
                        retval = usr_nat_fxn_table[-t16] (&FP);
                    }

                    /*
                     * RETURN FROM NATIVE FXN
                     */

                    /* Clear flag, so frame will not be marked by the GC */
                    gVmGlobal.nativeframe.nf_active = C_FALSE;

                    /* If the frame pointer was switched, do nothing to TOS */
                    if (retval == PM_RET_FRAME_SWITCH)
                    {
                        retval = PM_RET_OK;
                    }

                    /* Otherwise, return the result from the native function */
                    else
                    {
                        PM_PUSH(gVmGlobal.nativeframe.nf_stack);
                    }
                    PM_BREAK_IF_ERROR(retval);
                }
                continue;

            case MAKE_FUNCTION:
                /* Get num default args to fxn */
                t16 = GET_ARG();

                /* Load func from CO */
                pobj1 = PM_POP();

                /*
                 * The current frame's globals become the function object's
                 * globals.  The current frame is the container object
                 * of this new function object
                 */
                retval = func_new(pobj1, (pPmObj_t)FP->fo_globals, &pobj2);
                PM_BREAK_IF_ERROR(retval);

                /* Put any default args in a tuple */
                if (t16 > 0)
                {
                    retval = tuple_new(t16, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    while (--t16 >= 0)
                    {
                        ((pPmTuple_t)pobj3)->val[t16] = PM_POP();
                    }

                    /* Set func's default args */
                    ((pPmFunc_t)pobj2)->f_defaultargs = (pPmTuple_t)pobj3;
                }

                /* Push func obj */
                PM_PUSH(pobj2);
                continue;

            default:
                /* SystemError, unknown or unimplemented opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;
        }

        /*
         * If execution reaches this point, it is because
         * a return value (from above) is not OK or we should exit the thread
         * (return of the function). In any case, remove the
         * current thread and reschedule.
         */
        PM_REPORT_IF_ERROR(retval);

        /* If this is the last thread, return the error code */
        if ((gVmGlobal.threadList->length <= 1) && (retval != PM_RET_OK))
        {
            break;
        }

        retval = list_remove((pPmObj_t)gVmGlobal.threadList,
                             (pPmObj_t)gVmGlobal.pthread);
        gVmGlobal.pthread = C_NULL;
        PM_BREAK_IF_ERROR(retval);

        retval = interp_reschedule();
        PM_BREAK_IF_ERROR(retval);
    }

    return retval;
}

PmReturn_t
interp_reschedule(void)
{
    PmReturn_t retval = PM_RET_OK;
    static uint8_t threadIndex = (uint8_t)0;
    pPmObj_t pobj;

    /* If there are no threads in the runnable list, null the active thread */
    if (gVmGlobal.threadList->length == 0)
    {
        gVmGlobal.pthread = C_NULL;
    }

    /* Otherwise, get the next thread in the list (round robin) */
    else
    {
        if (++threadIndex >= gVmGlobal.threadList->length)
        {
            threadIndex = (uint8_t)0;
        }
        retval = list_getItem((pPmObj_t)gVmGlobal.threadList, threadIndex,
                              &pobj);
        gVmGlobal.pthread = (pPmThread_t)pobj;
        PM_RETURN_IF_ERROR(retval);
    }

    /* Clear flag to indicate a reschedule has occurred */
    interp_setRescheduleFlag(0);
    return retval;
}

PmReturn_t
interp_addThread(pPmFunc_t pfunc)
{
    PmReturn_t retval;
    pPmObj_t pframe;
    pPmObj_t pthread;

    /* Create a frame for the func */
    retval = frame_new((pPmObj_t)pfunc, &pframe);
    PM_RETURN_IF_ERROR(retval);

    /* Create a thread with this new frame */
    retval = thread_new(pframe, &pthread);
    PM_RETURN_IF_ERROR(retval);

    /* Add thread to end of list */
    return list_append((pPmObj_t)gVmGlobal.threadList, pthread);
}

void
interp_setRescheduleFlag(uint8_t boolean)
{
    gVmGlobal.reschedule = boolean;
}
