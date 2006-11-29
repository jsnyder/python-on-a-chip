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
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/** if retval is not OK, break from the interpreter */
#define PM_BREAK_IF_ERROR(retval) if((retval) != PM_RET_OK)break


/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

extern PmReturn_t (* std_nat_fxn_table[])(pPmFrame_t, signed char);
extern PmReturn_t (* usr_nat_fxn_table[])(pPmFrame_t, signed char);
PmReturn_t nat___bi_pow(pPmFrame_t pframe, signed char numargs);

/***************************************************************
 * Functions
 **************************************************************/

PmReturn_t
interpret(pPmFunc_t pfunc)
{
    PmReturn_t retval = PM_RET_OK;
    pPmObj_t pobj1 = C_NULL;
    pPmObj_t pobj2 = C_NULL;
    pPmObj_t pobj3 = C_NULL;
    int16_t t16 = 0;
    int8_t t8 = 0;
    pPmFrame_t pframe = C_NULL; /* tmp: until thread contains fp */

    /* create a frame for the func */
    retval = frame_new((pPmObj_t)pfunc, &pobj1);
    PM_RETURN_IF_ERROR(retval);
    FP = (pPmFrame_t)pobj1;

    /*
     * set globals dict to same as root frame's attrs.
     * root frame's attrs points to root func's attrs,
     * which contains builtins.
     */
    FP->fo_globals = FP->fo_attrs;

    /* interpret loop */
    while(gVmGlobal.interpctrl > INTERP_CTRL_EXIT)
    {
        /* get byte; the func post-incrs IP */
        switch(mem_getByte(MS, &IP))
        {
            case STOP_CODE:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case POP_TOP:
                pobj1 = PM_POP();
                continue;

            case ROT_TWO:
                pobj1 = TOS;
                TOS  = TOS1;
                TOS1 = pobj1;
                continue;

            case ROT_THREE:
                pobj1 = TOS;
                TOS  = TOS1;
                TOS1 = TOS2;
                TOS2 = pobj1;
                continue;

            case DUP_TOP:
                pobj1 = TOS;
                PM_PUSH(pobj1);
                continue;

            case ROT_FOUR:
                pobj1 = TOS;
                TOS  = TOS1;
                TOS1 = TOS2;
                TOS2 = TOS3;
                TOS3 = pobj1;
                continue;

            case UNARY_POSITIVE:
                /* TypeError if TOS is not an int */
                if (OBJ_GET_TYPE(*TOS) != OBJ_TYPE_INT)
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }
                /* when TOS is an int, this is a no-op */
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

            case UNARY_CONVERT:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case UNARY_INVERT:
                /* TypeError if it's not an int */
                if (OBJ_GET_TYPE(*TOS) != OBJ_TYPE_INT)
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }
                /* else perform bit-wise complement */
                pobj1 = PM_POP();
                retval = int_bitInvert(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case BINARY_POWER:
            case INPLACE_POWER:
                /* Put args in native frame */
                gVmGlobal.nativeframe.nf_locals[1] = PM_POP();
                gVmGlobal.nativeframe.nf_locals[0] = TOS;

                /* CALL NATIVE FXN */
                retval = nat___bi_pow(FP, 2);
                /* RETURN FROM NATIVE FXN */

                /* Put result on stack */
                TOS = gVmGlobal.nativeframe.nf_stack;
                PM_BREAK_IF_ERROR(retval);
                continue;

            case BINARY_MULTIPLY:
            case INPLACE_MULTIPLY:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val *
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* If it's a list replication operation */
                else if ((OBJ_GET_TYPE(*TOS)  == OBJ_TYPE_INT)
                         && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_LST))
                {
                    /* int number of times to duplicate */
                    pobj1 = PM_POP();
                    if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }
                    t16 = (int16_t)((pPmInt_t)pobj1)->val;

                    /* list that is copied */
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
                /* Raise TypeError if args aren't ints */
                if ((OBJ_GET_TYPE(*TOS) != OBJ_TYPE_INT)
                    || (OBJ_GET_TYPE(*TOS1) != OBJ_TYPE_INT))
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
                                 ((pPmInt_t)pobj1)->val,
                                 &pobj3);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case BINARY_MODULO:
            case INPLACE_MODULO:
                /* Raise TypeError if args aren't ints */
                if ((OBJ_GET_TYPE(*TOS) != OBJ_TYPE_INT)
                    || (OBJ_GET_TYPE(*TOS1) != OBJ_TYPE_INT))
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
                                 ((pPmInt_t)pobj1)->val,
                                 &pobj3);
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case BINARY_ADD:
            case INPLACE_ADD:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val +
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
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
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val -
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case BINARY_SUBSCR:
                /* Implements TOS = TOS1[TOS]. */

                /* get index */
                pobj1 = PM_POP();
                /* get sequence */
                pobj2 = PM_POP();

                if (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_DIC)
                {
                    retval = dict_getItem(pobj2, pobj1, &pobj3);
                }
                else
                {
                    /* Raise a TypeError if index is not an Integer */
                    if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }
                    t16 = ((pPmInt_t)pobj1)->val;
                    retval = seq_getSubscript(pobj2, t16, &pobj3);
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj3);
                continue;

            case SLICE_0:
                /*
                 * Implements TOS = TOS[:],
                 * push a copy of the sequence
                 */

                /* get sequence */
                pobj1 = PM_POP();

                /* XXX if there's an seq_copy(), use here */
                /* if it's a string */
                if (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_STR)
                {
                    retval = string_copy(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* if it's a tuple */
                else if (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_TUP)
                {
                    retval = tuple_copy(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* if it's a list */
                else if (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_LST)
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

            case SLICE_1:
            case SLICE_2:
            case SLICE_3:
            case STORE_SLICE_0:
            case STORE_SLICE_1:
            case STORE_SLICE_2:
            case STORE_SLICE_3:
            case DELETE_SLICE_0:
            case DELETE_SLICE_1:
            case DELETE_SLICE_2:
            case DELETE_SLICE_3:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case STORE_SUBSCR:
                /* implements TOS1[TOS] = TOS2 */
                pobj1 = PM_POP();
                pobj2 = PM_POP();
                pobj3 = PM_POP();

                /* if it's a list */
                if (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_LST)
                {
                    /* ensure subscr is an int */
                    if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_INT)
                    {
                        PM_RAISE(retval, PM_RET_EX_TYPE);
                        break;
                    }
                    /* set the list item */
                    retval = list_setItem(pobj2,
                                          (int16_t)(((pPmInt_t)pobj1)->val),
                                          pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* if it's a dict */
                if (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_DIC)
                {
                    /* set the dict item */
                    retval = dict_setItem(pobj2, pobj1, pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* TypeError for all else */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case DELETE_SUBSCR:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case BINARY_LSHIFT:
            case INPLACE_LSHIFT:
                /* If both objs are ints, perform the op */
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val <<
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
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
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val >>
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
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
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val &
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
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
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val ^
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
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
                if ((OBJ_GET_TYPE(*TOS) == OBJ_TYPE_INT)
                    && (OBJ_GET_TYPE(*TOS1) == OBJ_TYPE_INT))
                {
                    pobj1 = PM_POP();
                    pobj2 = PM_POP();
                    retval = int_new(((pPmInt_t)pobj2)->val |
                                     ((pPmInt_t)pobj1)->val,
                                     &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    PM_PUSH(pobj3);
                    continue;
                }

                /* Otherwise raise a TypeError */
                PM_RAISE(retval, PM_RET_EX_TYPE);
                break;

            case PRINT_EXPR:
            case PRINT_ITEM:
            case PRINT_NEWLINE:
            case PRINT_ITEM_TO:
            case PRINT_NEWLINE_TO:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case BREAK_LOOP:
                {
                    pPmBlock_t pb1 = FP->fo_blockstack;

                    /* ensure there's a block */
                    C_ASSERT(pb1 != C_NULL);

                    /* delete blocks until first loop block */
                    while ((pb1->b_type != B_LOOP)
                           && (pb1->next != C_NULL))
                    {
                        pobj2 = (pPmObj_t)pb1;
                        pb1 = pb1->next;
                        retval = heap_freeChunk(pobj2);
                        PM_BREAK_IF_ERROR(retval);
                    }
                    /* Test again outside while loop */
                    PM_BREAK_IF_ERROR(retval);

                    /* restore SP */
                    SP = pb1->b_sp;
                    /* goto handler */
                    IP = pb1->b_handler;
                    /* pop and delete this block */
                    FP->fo_blockstack = pb1->next;
                    retval = heap_freeChunk((pPmObj_t)pb1);
                    PM_BREAK_IF_ERROR(retval);
                }
                continue;

            case LOAD_LOCALS:
                /* pushes local attrs dict of current frame */
                /* XXX does not copy fo_locals to attrs */
                PM_PUSH((pPmObj_t)FP->fo_attrs);
                continue;

            case RETURN_VALUE:
                /* XXX error check: stack should be empty */
                /* get expiring frame's TOS */
                pobj2 = PM_POP();
                /* keep ref of expiring frame */
                pobj1 = (pPmObj_t)FP;
                /* if no previous frame, quit interpreter */
                if (FP->fo_back == C_NULL)
                {
                    gVmGlobal.interpctrl = INTERP_CTRL_EXIT;
                    retval = PM_RET_OK;
                    break;
                }
                /* else return to previous frame */
                FP = FP->fo_back;
                /* push frame's return val */
                PM_PUSH(pobj2);
                /* deallocate expired frame */
                PM_BREAK_IF_ERROR(heap_freeChunk(pobj1));
                continue;

            case IMPORT_STAR:
            case EXEC_STMT:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case POP_BLOCK:
                {
                    /* get ptr to top block */
                    pPmBlock_t pb = FP->fo_blockstack;
                    /* If there's no block, raise SystemError */
                    C_ASSERT(pb != C_NULL);

                    /* pop block */
                    FP->fo_blockstack = pb->next;
                    /* set stack to previous level */
                    SP = pb->b_sp;
                    /* delete block */
                    PM_BREAK_IF_ERROR(heap_freeChunk((pPmObj_t)pb));
                    continue;

                }

            case END_FINALLY:
            case BUILD_CLASS:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;


            /***************************************************
             * All bytecodes after 90 (0x5A) have a 2-byte arg
             * that needs to be swallowed using GET_ARG().
             **************************************************/

            case STORE_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get value */
                pobj1 = PM_POP();
                /* get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in current frame's attrs dict */
                retval = dict_setItem((pPmObj_t)FP->fo_attrs,
                                      pobj2,
                                      pobj1);
                PM_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_NAME:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case UNPACK_SEQUENCE:
                /* get expected size of the sequence */
                t16 = GET_ARG();
                /* get ptr to sequence */
                pobj1 = PM_POP();

                /* Push sequence's objs onto stack */
                if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_TUP)
                    || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_LST))
                {
                    for (; --t16 >= 0; )
                    {
                        retval = seq_getSubscript(pobj1, t16, &pobj2);
                        PM_BREAK_IF_ERROR(retval);
                        PM_PUSH(pobj2);
                    }
                    /* Test again outside the for loop */
                    PM_BREAK_IF_ERROR(retval);
                }
                continue;

            case STORE_ATTR:
                /* TOS.name = TOS1 */
                /* get names index */
                t16 = GET_ARG();
                /* get obj */
                pobj1 = PM_POP();
                /* get attrs dict from obj */
                if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_FXN)
                    || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_MOD))
                {
                    pobj2 = (pPmObj_t)((pPmFunc_t)pobj1)->
                                    f_attrs;
                }
                else if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_CLO)
                         || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_CLI)
                         || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_EXN))
                {
                    pobj2 = (pPmObj_t)((pPmClass_t)pobj1)->cl_attrs;
                }
                /* Other types result in an AttributeError */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_ATTR);
                    break;
                }
                /* if attrs is not a dict, raise SystemError */
                if (OBJ_GET_TYPE(*pobj2) != OBJ_TYPE_DIC)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }
                /* get name/key obj */
                pobj3 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in obj's dict */
                retval = dict_setItem(pobj2, pobj3, PM_POP());
                PM_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_ATTR:
                /* SystemError, unimplemented opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case STORE_GLOBAL:
                /* get name index */
                t16 = GET_ARG();
                /* get value */
                pobj1 = PM_POP();
                /* get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in global dict */
                retval = dict_setItem((pPmObj_t)FP->fo_globals,
                                      pobj2,
                                      pobj1);
                PM_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_GLOBAL:
                /* SystemError, unimplemented opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

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
                    PM_PUSH(pobj1);
                    PM_PUSH(pobj2);
                }
                else if (t16 == 3)
                {
                    pobj1 = TOS;
                    pobj2 = TOS1;
                    pobj3 = TOS2;
                    PM_PUSH(pobj1);
                    PM_PUSH(pobj2);
                    PM_PUSH(pobj3);
                }
                else
                {
                    /* Python compiler is responsible for keeping arg <= 3 */
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }
                continue;

            case LOAD_CONST:
                /* get const's index in CO */
                t16 = GET_ARG();
                /* push const on stack */
                PM_PUSH(FP->fo_func->f_co->co_consts->val[t16]);
                continue;

            case LOAD_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get name from names tuple */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* get value from frame's attrs dict */
                retval = dict_getItem((pPmObj_t)FP->fo_attrs,
                                     pobj1,
                                     &pobj2);
                if (retval == PM_RET_EX_KEY)
                {
                    /* get val from globals */
                    retval = dict_getItem(
                                (pPmObj_t)FP->fo_globals,
                                pobj1,
                                &pobj2);
                    if (retval == PM_RET_EX_KEY)
                    {
                        /* get val from builtins */
                        retval = dict_getItem(PM_PBUILTINS, pobj1, &pobj2);
                        if (retval == PM_RET_EX_KEY)
                        {
                            /* name not defined, raise NameError */
                            PM_RAISE(retval, PM_RET_EX_NAME);
                            break;
                        }
                    }
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case BUILD_TUPLE:
                /* get num items */
                t16 = GET_ARG();
                retval = tuple_new(t16, &pobj1);
                PM_BREAK_IF_ERROR(retval);

                /* fill tuple with ptrs to objs */
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
                    /* get obj */
                    pobj2 = PM_POP();
                    /* insert obj into list */
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
                /* get obj that has the attrs */
                pobj1 = PM_POP();
                /* get attrs dict from obj */
                if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_FXN) ||
                    (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_MOD))
                {
                    pobj1 = (pPmObj_t)((pPmFunc_t)pobj1)->
                                    f_attrs;
                }
                else if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_CLO)
                         || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_CLI)
                         || (OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_EXN))
                {
                    pobj1 = (pPmObj_t)((pPmClass_t)pobj1)->cl_attrs;
                }
                /* Other types result in an AttributeError */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_ATTR);
                    break;
                }
                /* if attrs is not a dict, raise SystemError */
                if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_DIC)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }
                /* get name */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* push attr with given name onto stack */
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
                if ((OBJ_GET_TYPE(*pobj1) == OBJ_TYPE_INT) &&
                    (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_INT))
                {
                    int32_t a = ((pPmInt_t)pobj2)->val;
                    int32_t b = ((pPmInt_t)pobj1)->val;

                    switch (t16)
                    {
                        case COMP_LT: t8 = (a <  b); break;
                        case COMP_LE: t8 = (a <= b); break;
                        case COMP_EQ: t8 = (a == b); break;
                        case COMP_NE: t8 = (a != b); break;
                        case COMP_GT: t8 = (a >  b); break;
                        case COMP_GE: t8 = (a >= b); break;
                        case COMP_IN: /* fallthrough */
                        case COMP_NOT_IN:
                            PM_RAISE(retval, PM_RET_EX_TYPE);
                            break;
                        case COMP_IS: t8 = (pobj1 == pobj2); break;
                        case COMP_IS_NOT: t8 = (pobj1 != pobj2); break;
                        /* Other compares are not yet supported */
                        default:
                            PM_RAISE(retval, PM_RET_EX_SYS);
                            break;
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
                        /* Handle equality comparisons for non-intger types */
                        case COMP_EQ:
                        case COMP_NE:
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

                        /* Handle membership comparisons */
                        case COMP_IN:
                        case COMP_NOT_IN:
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

                        /* Other comparisons are not implemented */
                        default:
                            PM_RAISE(retval, PM_RET_EX_SYS);
                            break;
                    }
                    PM_BREAK_IF_ERROR(retval);
                }
                PM_PUSH(pobj3);
                continue;

            case IMPORT_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get name String obj */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* XXX check if module is already loaded */
                /* load module from image */
                retval = mod_import(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);
                /* module overwrites None on stack */
                TOS = pobj2;

                /*
                 * XXX recursion into interpreter.
                 * This must happen like this because the
                 * root code of the imported module returns
                 * with a None object on the stack, and the
                 * interpreter does not know to pop it
                 * for cleanup.
                 * Solutions are: A. to create a state var
                 * to track when interp is in import_name-code
                 * and pop on return.  B. to replace
                 * the push(none)return from the module's root
                 * bytecode with new RETURN_EMPTY bcode.
                 * or C. recurse into interp...
                 */
                retval = interpret((pPmFunc_t)pobj2);
                PM_BREAK_IF_ERROR(retval);
                gVmGlobal.interpctrl = INTERP_CTRL_CONT;
                continue;

            case IMPORT_FROM:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

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
                t16 = GET_ARG();
                /* jump to base_ip + arg */
                IP = FP->fo_func->f_co->co_codeaddr + t16;
                continue;

            case FOR_LOOP:
                /* get skip bytes */
                t16 = GET_ARG();
                /* get current index */
                pobj1 = PM_POP();
                /* get the sequence */
                pobj2 = PM_POP();

                /* ensure index is an int */
                if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_INT)
                {
                    PM_RAISE(retval, PM_RET_EX_INDX);
                    break;
                }
                /* dup a const int to allow it to incr (TRASH)*/
                if (OBJ_IS_CONST(*pobj1))
                {
                    retval = int_dup(pobj1, &pobj1);
                    PM_BREAK_IF_ERROR(retval);
                }

                /* if it's a tuple */
                if (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_TUP)
                {
                    /* if tup is exhausted, incr IP by delta */
                    if (((pPmInt_t)pobj1)->val >=
                        ((pPmTuple_t)pobj2)->length)
                    {
                        IP += t16;
                        continue;
                    }

                    /* get item, incr counter */
                    pobj3 = ((pPmTuple_t)pobj2)->val[
                                ((pPmInt_t)pobj1)->val++];
                }

                /* if it's a list */
                else if (OBJ_GET_TYPE(*pobj2) == OBJ_TYPE_LST)
                {
                    /* if list is exhausted, incr IP by delta */
                    if (((pPmInt_t)pobj1)->val >=
                        ((pPmList_t)pobj2)->length)
                    {
                        IP += t16;
                        continue;
                    }

                    /* get item */
                    retval = list_getItem(pobj2,
                                          (int16_t)(((pPmInt_t)pobj1)->val),
                                          &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    /* incr counter */
                    ((pPmInt_t)pobj1)->val++;
                }

                /* XXX if it's a string */

                /* TypeError: loop over non-sequence */
                else
                {
                    PM_RAISE(retval, PM_RET_EX_TYPE);
                    break;
                }

                /* push tup, counter and item */
                PM_PUSH(pobj2);
                PM_PUSH(pobj1);
                PM_PUSH(pobj3);
                continue;

            case LOAD_GLOBAL:
                /* get name */
                t16 = GET_ARG();
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* try globals first */
                retval = dict_getItem((pPmObj_t)FP->fo_globals,
                                      pobj1,
                                      &pobj2);
                /* if that didn't work, try builtins */
                if (retval == PM_RET_EX_KEY)
                {
                    retval = dict_getItem(PM_PBUILTINS, pobj1, &pobj2);
                    /* no such global, raise NameError */
                    if (retval == PM_RET_EX_KEY)
                    {
                        PM_RAISE(retval, PM_RET_EX_NAME);
                        break;
                    }
                }
                PM_BREAK_IF_ERROR(retval);
                PM_PUSH(pobj2);
                continue;

            case CONTINUE_LOOP:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case SETUP_LOOP:
            {
                uint8_t *pchunk;

                /* get block span (bytes) */
                t16 = GET_ARG();
                /* create block */
                retval = heap_getChunk(sizeof(PmBlock_t), &pchunk);
                PM_BREAK_IF_ERROR(retval);
                pobj1 = (pPmObj_t)pchunk;
                OBJ_SET_TYPE(*pobj1, OBJ_TYPE_BLK);
                /* store current stack pointer */
                ((pPmBlock_t)pobj1)->b_sp = SP;
                /* default handler is to exit block/loop */
                ((pPmBlock_t)pobj1)->b_handler = IP + t16;
                ((pPmBlock_t)pobj1)->b_type = B_LOOP;
                /* insert block into blockstack */
                ((pPmBlock_t)pobj1)->next = FP->fo_blockstack;
                FP->fo_blockstack = (pPmBlock_t)pobj1;
                continue;
            }

            case SETUP_EXCEPT:
            case SETUP_FINALLY:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case LOAD_FAST:
                t16 = GET_ARG();
                PM_PUSH(FP->fo_locals[t16]);
                continue;

            case STORE_FAST:
                t16 = GET_ARG();
                FP->fo_locals[t16] = PM_POP();
                continue;

            case DELETE_FAST:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

            case SET_LINENO:
                FP->fo_line = GET_ARG();
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
                if (OBJ_GET_TYPE(*pobj1) != OBJ_TYPE_EXN)
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
                                      PM_CODE_STR,
                                      &pobj2);
                PM_BREAK_IF_ERROR(retval);

                /* Get the value from the code int */
                retval = (PmReturn_t)(((pPmInt_t)pobj2)->val & 0xFF);

                /* Raise exception by breaking with retval set to code */
                break;

            case CALL_FUNCTION:
                /* get num args */
                t16 = GET_ARG();
                /* ensure no keyword args */
                if ((t16 & (uint16_t)0xFF00) != 0)
                {
                    PM_RAISE(retval, PM_RET_EX_SYS);
                    break;
                }
                /* get the func */
                pobj1 = STACK(t16);

                /* if it's regular func (not native) */
                if (OBJ_GET_TYPE(*((pPmFunc_t)pobj1)->f_co) ==
                    OBJ_TYPE_COB)
                {
                    /* make frameObj from pCO */
                    retval = frame_new(pobj1, &pobj2);
                    PM_BREAK_IF_ERROR(retval);
                    /* frame's globals is same as parent's */
                    ((pPmFrame_t)pobj2)->fo_globals =
                            FP->fo_globals;
                    /* pass args to new frame */
                    while (--t16 >= 0)
                    {
                        /*
                         * pop args from stack.
                         * args are pushed left to right,
                         * so pop right to left.
                         */
                        ((pPmFrame_t)pobj2)->fo_locals[t16] =
                                PM_POP();
                    }
                    /* pop func obj */
                    pobj3 = PM_POP();
                    /* keep ref to current frame */
                    ((pPmFrame_t)pobj2)->fo_back = FP;
                    /* set new frame */
                    FP = (pPmFrame_t)pobj2;
                }

                /* if it's native func */
                else if (OBJ_GET_TYPE(*((pPmFunc_t)pobj1)->f_co) ==
                         OBJ_TYPE_NOB)
                {
                    /* ensure num args fits in native frame */
                    if (t16 > NATIVE_NUM_LOCALS)
                    {
                        PM_RAISE(retval, PM_RET_EX_SYS);
                        break;
                    }

                    /* keep numargs */
                    t8 = (int8_t)t16;

                    /* pop args from stack */
                    while (--t16 >= 0)
                    {
                        gVmGlobal.nativeframe.nf_locals[t16] =
                                PM_POP();
                    }
                    /* get native function index */
                    pobj2 = (pPmObj_t)((pPmFunc_t)pobj1)->f_co;
                    t16 = ((pPmNo_t)pobj2)->no_funcindx;

                    /*
                     * CALL NATIVE FXN
                     * pass caller's frame and numargs
                     */
                    /* Positive index is a stdlib func */
                    if (t16 >= 0)
                    {
                        retval = std_nat_fxn_table[t16](FP, t8);
                    }
                    /* Negative index is a usrlib func */
                    else
                    {
                        retval = usr_nat_fxn_table[-t16](FP, t8);
                    }
                    /*
                     * RETURN FROM NATIVE FXN
                     */

                    /* pop func, push result */
                    TOS = gVmGlobal.nativeframe.nf_stack;
                    PM_BREAK_IF_ERROR(retval);
                }
                continue;

            case MAKE_FUNCTION:
                /* get num default args to fxn */
                t16 = GET_ARG();
                /* load func from CO */
                pobj1 = PM_POP();
                retval = func_new(pobj1, &pobj2);
                PM_BREAK_IF_ERROR(retval);
                /* put any default args in a tuple */
                if (t16 > 0)
                {
                    retval = tuple_new(t16, &pobj3);
                    PM_BREAK_IF_ERROR(retval);
                    while (--t16 >= 0)
                    {
                        ((pPmTuple_t)pobj3)->val[t16] =
                                PM_POP();
                    }
                    /* set func's default args */
                    ((pPmFunc_t)pobj2)->f_defaultargs =
                                ((pPmTuple_t)pobj3);
                }
                /* push func obj */
                PM_PUSH(pobj2);
                continue;

            case BUILD_SLICE:
            case MAKE_CLOSURE:
            case LOAD_CLOSURE:
            case LOAD_DEREF:
            case STORE_DEREF:
            case CALL_FUNCTION_VAR:
            case CALL_FUNCTION_KW:
            case CALL_FUNCTION_VAR_KW:
            case EXTENDED_ARG:
            default:
                /* SystemError, unknown opcode */
                PM_RAISE(retval, PM_RET_EX_SYS);
                break;

        } /* switch (interpret) */

        /*
         * If execution reaches this point, it is because
         * either a return value (from above) is not OK
         * (an error or exception), or the return value is OK
         * and the interpreter is exiting.
         */
        return retval;

    } /* while */

    return retval;
}


/***************************************************************
 * Test
 **************************************************************/

/***************************************************************
 * Main
 **************************************************************/
