#undef __FILE_ID__
#define __FILE_ID__ 0x09
/**
 * VM Interpreter
 *
 * VM interpreter operations.
 *
 * @author      Dean Hall
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 * @file        interp.c
 *
 * Log
 * ---
 *
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

#include "py.h"


/***************************************************************
 * Constants
 **************************************************************/

/***************************************************************
 * Macros
 **************************************************************/

/** if retval is not OK, break from the interpreter */
#define PY_BREAK_IF_ERROR(retval) if((retval) != PY_RET_OK)break


/***************************************************************
 * Types
 **************************************************************/

/***************************************************************
 * Globals
 **************************************************************/

/***************************************************************
 * Prototypes
 **************************************************************/

extern PyReturn_t (* nat_fxn_table[])(pPyFrame_t, signed char);

/***************************************************************
 * Functions
 **************************************************************/

/*
 * Halts via infinite loop.
 * Error report is in the registers containing
 * the parameters.  In avr-gcc these are regs R25-20.
 * TODO print values out SCI or on LCD
 */
void
py_err(S16 release, S16 file, S16 line)
{
    for(;;);
}


PyReturn_t
interpret(pPyFunc_t pfunc)
{
    PyReturn_t retval = PY_RET_OK;
    pPyObj_t pobj1 = C_NULL;
    pPyObj_t pobj2 = C_NULL;
    pPyObj_t pobj3 = C_NULL;
    S16 t16 = 0;
    S8 t8 = 0;
    pPyFrame_t pframe = C_NULL; /* tmp: until thread contains fp */

    /* create a frame for the func */
    retval = frame_new((pPyObj_t)pfunc, (pPyObj_t *)&FP);
    PY_RETURN_IF_ERROR(retval);

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
        switch((U8)mem_getByte(MS, &IP))
        {
            case STOP_CODE:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case POP_TOP:
                pobj1 = PY_POP();
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
                PY_PUSH(pobj1);
                continue;

            case ROT_FOUR:
                pobj1 = TOS;
                TOS  = TOS1;
                TOS1 = TOS2;
                TOS2 = TOS3;
                TOS3 = pobj1;
                continue;

            case UNUSED_06:
            case UNUSED_07:
            case UNUSED_08:
            case UNUSED_09:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case UNARY_POSITIVE:
                /* TypeError if TOS is not an int */
                if (TOS->od.od_type != OBJ_TYPE_INT)
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }
                /* when TOS is an int, this is a no-op */
                continue;

            case UNARY_NEGATIVE:
                pobj1 = PY_POP();
                retval = int_negative(pobj1, &pobj2);
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj2);
                if (pobj2 == C_NULL)
                {
                    /* memory error? */
                    PY_ERR(__LINE__);
                }
                continue;

            case UNARY_NOT:
                pobj1 = PY_POP();
                if (obj_isFalse(pobj1))
                {
                    PY_PUSH(PY_TRUE);
                }
                else
                {
                    PY_PUSH(PY_FALSE);
                }
                continue;

            case UNARY_CONVERT:
            case UNUSED_0E:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case UNARY_INVERT:
                /* TypeError if it's not an int */
                if (TOS->od.od_type != OBJ_TYPE_INT)
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }
                /* else perform bit-wise complement */
                pobj1 = PY_POP();
                retval = int_bitInvert(pobj1, &pobj2);
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj2);
                if (pobj2 == C_NULL)
                {
                    /* memory error? */
                    PY_ERR(__LINE__);
                }
                continue;

            case UNUSED_10:
            case UNUSED_11:
            case UNUSED_12:
            case BINARY_POWER:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case BINARY_MULTIPLY:
                /* if both objs are ints, simple multiply */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val *
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* if it's a list replication operation */
                else if ((TOS->od.od_type  == OBJ_TYPE_INT)
                         && (TOS1->od.od_type == OBJ_TYPE_LST))
                {
                    /* int number of times to duplicate */
                    pobj1 = PY_POP();
                    /* list that is copied */
                    pobj2 = PY_POP();
                    retval = list_replicate(pobj2,
                                            pobj1,
                                            &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj3);
                    continue;
                }

                /* else it's a TypeError */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case BINARY_DIVIDE:
                /* if both objs are ints, simple divide */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();

                    /* ZeroDivisionError */
                    if (((pPyInt_t)pobj1)->val == 0)
                    {
                        retval = PY_RET_EX_ZDIV;
                        break;
                    }
                    /* perform division */
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val /
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case BINARY_MODULO:
                /* if both objs are ints, perform modulo */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    /* ZeroDivisionError */
                    if (((pPyInt_t)pobj1)->val == 0)
                    {
                        retval = PY_RET_EX_ZDIV;
                        break;
                    }
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val %
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case BINARY_ADD:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val +
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case BINARY_SUBTRACT:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val -
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case BINARY_SUBSCR:
                /* Implements TOS = TOS1[TOS]. */
                /* get subscr */
                pobj1 = PY_POP();
                /* get sequence */
                pobj2 = PY_POP();

                /* XXX issue #10: create seq_getSubscript(); */
                /* XXX index out of range exception? */

                /* if it's a string */
                if (pobj2->od.od_type == OBJ_TYPE_STR)
                {
                    /* TypeError; sequence index must be int */
                    if (pobj1->od.od_type != OBJ_TYPE_INT)
                    {
                        retval = PY_RET_EX_TYPE;
                        break;
                    }

                    /* Get the character from the string */
                    t8 = (U8)((pPyString_t)pobj2)->
                                 val[((pPyInt_t)pobj1)->val];

                    /* Create a new string from the character */
                    retval = string_newFromChar(t8, &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* if it's a tuple */
                else if (pobj2->od.od_type == OBJ_TYPE_TUP)
                {
                    /* TypeError; sequence index must be int */
                    if (pobj1->od.od_type != OBJ_TYPE_INT)
                    {
                        retval = PY_RET_EX_TYPE;
                        break;
                    }
                    /* get the tuple item */
                    /* XXX index out of range exception? */
                    pobj3 = ((pPyTuple_t)pobj2)->val[
                                ((pPyInt_t)pobj1)->val];
                }

                /* if it's a list */
                else if (pobj2->od.od_type == OBJ_TYPE_LST)
                {
                    /* TypeError; sequence index must be int */
                    if (pobj1->od.od_type != OBJ_TYPE_INT)
                    {
                        retval = PY_RET_EX_TYPE;
                        break;
                    }
                    /* get the list item */
                    retval = list_getItem(pobj2,
                                          (S16)(((pPyInt_t)
                                                pobj1)->val),
                                          &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* if it's a dict */
                else if (pobj2->od.od_type == OBJ_TYPE_DIC)
                {
                    /* get the dict item */
                    retval = dict_getItem(pobj2, pobj1, &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* TypeError; unsubscriptable object */
                else
                {
                    retval = PY_RET_EX_TYPE;
                }

                /* push item and continue */
                PY_PUSH(pobj3);
                continue;

            case UNUSED_1A:
            case UNUSED_1B:
            case UNUSED_1C:
            case UNUSED_1D:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case SLICE_0:
                /*
                 * Implements TOS = TOS[:],
                 * push a copy of the sequence
                 */

                /* get sequence */
                pobj1 = PY_POP();

                /* XXX if there's an obj_copy(), use here */
                /* if it's a string */
                if (pobj1->od.od_type == OBJ_TYPE_STR)
                {
                    retval = string_copy(pobj1, &pobj2);
                }

                /* if it's a tuple */
                else if (pobj1->od.od_type == OBJ_TYPE_TUP)
                {
                    retval = tuple_copy(pobj1, &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* if it's a list */
                else if (pobj1->od.od_type == OBJ_TYPE_LST)
                {
                    retval = list_copy(pobj1, &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* TypeError; unhashable type */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

                PY_PUSH(pobj2);
                continue;

            case SLICE_1:
            case SLICE_2:
            case SLICE_3:
            case UNUSED_22:
            case UNUSED_23:
            case UNUSED_24:
            case UNUSED_25:
            case UNUSED_26:
            case UNUSED_27:
            case STORE_SLICE_0:
            case STORE_SLICE_1:
            case STORE_SLICE_2:
            case STORE_SLICE_3:
            case UNUSED_2C:
            case UNUSED_2D:
            case UNUSED_2E:
            case UNUSED_2F:
            case UNUSED_30:
            case UNUSED_31:
            case DELETE_SLICE_0:
            case DELETE_SLICE_1:
            case DELETE_SLICE_2:
            case DELETE_SLICE_3:
            case UNUSED_36:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case INPLACE_ADD:
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if int is constant, make new result */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val +
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                    }

                    /* else result stores in-place */
                    else
                    {
                        ((pPyInt_t)TOS1)->val +=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                    }
                    continue;
                }

                /* TypeError; unsupported type */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case INPLACE_SUBTRACT:
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val -
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val -=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                    }
                    continue;
                }

                /* TypeError; unsupported type */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case INPLACE_MULTIPLY:
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val *
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val *=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                    }
                    continue;
                }

                /* TypeError; unsupported type */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

            case INPLACE_DIVIDE:
                /* TypeError; unsupported type */
                if ((TOS->od.od_type  != OBJ_TYPE_INT)
                    || (TOS1->od.od_type != OBJ_TYPE_INT))
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

                /* ZeroDivisionError */
                if (((pPyInt_t)TOS)->val == 0)
                {
                    retval = PY_RET_EX_ZDIV;
                    break;
                }

                /* if target obj is a constant obj */
                if (TOS1->od.od_const) {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val /
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                }

                /* otherwise do true in-place operation */
                else
                {
                    ((pPyInt_t)TOS1)->val /=
                            ((pPyInt_t)TOS)->val;
                    SP--;
                }
                continue;

            case INPLACE_MODULO:
                /* TypeError; unsupported type */
                if ((TOS->od.od_type  != OBJ_TYPE_INT)
                    || (TOS1->od.od_type != OBJ_TYPE_INT))
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

                /* ZeroDivisionError */
                if (((pPyInt_t)TOS)->val == 0)
                {
                    retval = PY_RET_EX_ZDIV;
                    break;
                }

                /* if target obj is a constant obj */
                if (TOS1->od.od_const) {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val %
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                }

                /* otherwise do true in-place operation */
                else
                {
                    ((pPyInt_t)TOS1)->val %=
                            ((pPyInt_t)TOS)->val;
                    SP--;
                }
                continue;

            case STORE_SUBSCR:
                /* implements TOS1[TOS] = TOS2 */
                pobj1 = PY_POP();
                pobj2 = PY_POP();
                pobj3 = PY_POP();

                /* if it's a list */
                if (pobj2->od.od_type == OBJ_TYPE_LST)
                {
                    /* ensure subscr is an int */
                    if (pobj1->od.od_type != OBJ_TYPE_INT)
                    {
                        PY_ERR(__LINE__);
                    }
                    /* set the list item */
                    retval = list_setItem(pobj2,
                                 (S16)(((pPyInt_t)pobj1)->val),
                                 pobj3);
                    PY_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* if it's a dict */
                if (pobj2->od.od_type == OBJ_TYPE_DIC)
                {
                    /* set the dict item */
                    retval = dict_setItem(pobj2, pobj1, pobj3);
                    PY_BREAK_IF_ERROR(retval);
                    continue;
                }

                /* TypeError for all else */
                retval = PY_RET_EX_TYPE;
                break;

            case DELETE_SUBSCR:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case BINARY_LSHIFT:
                /* if neither args are ints, TypeError */
                if ((TOS->od.od_type == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val <<
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case BINARY_RSHIFT:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val >>
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case BINARY_AND:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val &
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case BINARY_XOR:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val ^
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case BINARY_OR:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    pobj1 = PY_POP();
                    retval = int_new(
                                ((pPyInt_t)PY_POP())->val |
                                ((pPyInt_t)pobj1)->val,
                                &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    PY_PUSH(pobj2);
                    continue;
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case INPLACE_POWER:
            case UNUSED_44:
            case UNUSED_45:
            case PRINT_EXPR:
            case PRINT_ITEM:
            case PRINT_NEWLINE:
            case PRINT_ITEM_TO:
            case PRINT_NEWLINE_TO:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case INPLACE_LSHIFT:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val <<
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                        continue;
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val <<=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                        continue;
                    }
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case INPLACE_RSHIFT:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val >>
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                        continue;
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val >>=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                        continue;
                    }
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case INPLACE_AND:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val &
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                        continue;
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val &=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                        continue;
                    }
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case INPLACE_XOR:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val ^
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                        continue;
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val ^=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                        continue;
                    }
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case INPLACE_OR:
                /* if both objs are ints, perform the op */
                if ((TOS->od.od_type  == OBJ_TYPE_INT)
                    && (TOS1->od.od_type == OBJ_TYPE_INT))
                {
                    /* if target obj is a constant obj */
                    if (TOS1->od.od_const) {
                        pobj1 = PY_POP();
                        retval = int_new(
                                    ((pPyInt_t)PY_POP())->val |
                                    ((pPyInt_t)pobj1)->val,
                                    &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                        continue;
                    }

                    /* otherwise do true in-place operation */
                    else
                    {
                        ((pPyInt_t)TOS1)->val |=
                                ((pPyInt_t)TOS)->val;
                        SP--;
                        continue;
                    }
                }

                /* else it's a TypeError */
                retval = PY_RET_EX_TYPE;
                break;

            case BREAK_LOOP:
                {
                    pPyBlock_t pb1 = FP->fo_blockstack;

                    /* ensure there's a block */
                    if (pb1 == C_NULL)
                    {
                        PY_ERR(__LINE__);
                    }

                    /* delete blocks until first loop block */
                    while ((pb1->b_type != B_LOOP)
                           && (pb1->next != C_NULL))
                    {
                        pobj2 = (pPyObj_t)pb1;
                        pb1 = pb1->next;
                        heap_freeChunk(pobj2);
                    }
                    /* restore SP */
                    SP = pb1->b_sp;
                    /* goto handler */
                    IP = pb1->b_handler;
                    /* pop and delete this block */
                    FP->fo_blockstack = pb1->next;
                    heap_freeChunk((pPyObj_t)pb1);
                }
                continue;

            case UNUSED_51:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

/*XXXEDITSCOMPLETEUPTOHERE*/
            case LOAD_LOCALS:
                /* pushes local attrs dict of current frame */
                /* XXX does not copy fo_locals to attrs */
                PY_PUSH((pPyObj_t)FP->fo_attrs);
                continue;

            case RETURN_VALUE:
                /* XXX error check: stack should be empty */
                /* get expiring frame's TOS */
                pobj2 = PY_POP();
                /* keep ref of expiring frame */
                pobj1 = (pPyObj_t)FP;
                /* if no previous frame, quit interpreter */
                if (FP->fo_back == C_NULL)
                {
                    gVmGlobal.interpctrl = INTERP_CTRL_EXIT;
                    retval = PY_RET_OK;
                    break;
                }
                /* else return to previous frame */
                FP = FP->fo_back;
                /* push frame's return val */
                PY_PUSH(pobj2);
                /* deallocate expired frame */
                heap_freeChunk(pobj1);
                continue;

            case IMPORT_STAR:
            case EXEC_STMT:
            case UNUSED_56:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case POP_BLOCK:
                {
                    /* get ptr to top block */
                    pPyBlock_t pb = FP->fo_blockstack;
                    /* if there's a block */
                    if (pb != C_NULL)
                    {
                        /* pop block */
                        FP->fo_blockstack = pb->next;
                        /* set stack to previous level */
                        SP = pb->b_sp;
                        /* delete block */
                        heap_freeChunk((pPyObj_t)pb);
                        continue;
                    }

                    /* SystemError, nonexistent block */
                    retval = PY_RET_EX_SYS;
                    break;
                }

            case END_FINALLY:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case BUILD_CLASS:
                pobj1 = PY_POP();
                pobj2 = PY_POP();
                pobj3 = TOS;

                /* create and push new class */
                retval = class_new(pobj1,
                                   pobj2,
                                   pobj3,
                                   &pobj1);
                PY_BREAK_IF_ERROR(retval);
                TOS = pobj1;
                continue;


            /***************************************************
             * All bytecodes after 90 (0x5A) have a 2-byte arg
             * that needs to be swallowed using GET_ARG().
             **************************************************/

            case STORE_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get value */
                pobj1 = PY_POP();
                /* get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in current frame's attrs dict */
                retval = dict_setItem((pPyObj_t)FP->fo_attrs,
                                      pobj2,
                                      pobj1);
                PY_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_NAME:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case UNPACK_SEQUENCE:
                /* get expected size of the sequence */
                t16 = GET_ARG();
                /* get ptr to sequence */
                pobj1 = PY_POP();
                /* push objs onto stack based on type */
                if (pobj1->od.od_type == OBJ_TYPE_TUP)
                {
                    for (; --t16 >= 0; )
                    {
                        /* XXX should copy simple objs ? */
                        PY_PUSH(((pPyTuple_t)pobj1)->val[t16]);
                    }
                }
                else if (pobj1->od.od_type == OBJ_TYPE_LST)
                {
                    for (; --t16 >= 0; )
                    {
                        /* XXX should copy simple objs */
                        retval = list_getItem(pobj1,
                                              t16,
                                              &pobj2);
                        PY_BREAK_IF_ERROR(retval);
                        PY_PUSH(pobj2);
                    }
                }
                continue;

            case UNUSED_5D:
            case UNUSED_5E:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case STORE_ATTR:
                /* TOS.name = TOS1 */
                /* get names index */
                t16 = GET_ARG();
                /* get obj */
                pobj1 = PY_POP();
                /* get attrs dict from obj */
                if ((pobj1->od.od_type == OBJ_TYPE_FXN)
                    || (pobj1->od.od_type == OBJ_TYPE_COB)
                    || (pobj1->od.od_type == OBJ_TYPE_MOD))
                {
                    pobj1 = (pPyObj_t)((pPyFunc_t)pobj1)->
                                    f_attrs;
                }
                /* unhandled type is a SystemError */
                else
                {
                    retval = PY_RET_EX_SYS;
                    break;
                }
                /* if attrs is not a dict, raise SystemError */
                if (pobj1->od.od_type != OBJ_TYPE_DIC)
                {
                    retval = PY_RET_EX_SYS;
                    break;
                }
                /* get name/key obj */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in obj's dict */
                retval = dict_setItem(pobj1, pobj2, PY_POP());
                PY_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_ATTR:
                /* SystemError, unimplemented opcode */
                retval = PY_RET_EX_SYS;
                break;

            case STORE_GLOBAL:
                /* get name index */
                t16 = GET_ARG();
                /* get value */
                pobj1 = PY_POP();
                /* get key */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* set key=val in global dict */
                retval = dict_setItem((pPyObj_t)FP->fo_globals,
                                      pobj2,
                                      pobj1);
                PY_BREAK_IF_ERROR(retval);
                continue;

            case DELETE_GLOBAL:
                /* SystemError, unimplemented opcode */
                retval = PY_RET_EX_SYS;
                break;

            case DUP_TOPX:
                t16 = GET_ARG();
                if (t16 == 1)
                {
                    pobj1 = TOS;
                    PY_PUSH(pobj1);
                }
                else if (t16 == 2)
                {
                    pobj1 = TOS;
                    pobj2 = TOS1;
                    PY_PUSH(pobj1);
                    PY_PUSH(pobj2);
                }
                else if (t16 == 3)
                {
                    pobj1 = TOS;
                    pobj2 = TOS1;
                    pobj3 = TOS2;
                    PY_PUSH(pobj1);
                    PY_PUSH(pobj2);
                    PY_PUSH(pobj3);
                }
                else
                {
                    PY_ERR(ERR_ARG);
                }
                continue;

            case LOAD_CONST:
                /* get const's index in CO */
                t16 = GET_ARG();
                /* push const on stack */
                PY_PUSH(FP->fo_func->f_co->co_consts->val[t16]);
                continue;

            case LOAD_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get name from names tuple */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* get value from frame's attrs dict */
                retval = dict_getItem((pPyObj_t)FP->fo_attrs,
                                     pobj1,
                                     &pobj2);
                if (retval == PY_RET_EX_KEY)
                {
                    /* get val from globals */
                    retval = dict_getItem(
                                (pPyObj_t)FP->fo_globals,
                                pobj1,
                                &pobj2);
                    if (retval == PY_RET_EX_KEY)
                    {
                        /* get val from builtins */
                        retval = dict_getItem(PY_PBUILTINS, pobj1, &pobj2);
                        if (retval == PY_RET_EX_KEY)
                        {
                            /* name not defined, raise NameError */
                            retval = PY_RET_EX_NAME;
                            break;
                        }
                    }
                }
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj2);
                continue;

            case BUILD_TUPLE:
                /* get num items */
                t16 = GET_ARG();
                retval = tuple_new(t16, &pobj1);
                PY_BREAK_IF_ERROR(retval);

                /* fill tuple with ptrs to objs */
                for (; --t16 >= 0;)
                {
                    ((pPyTuple_t)pobj1)->val[t16] = PY_POP();
                }
                PY_PUSH(pobj1);
                continue;

            case BUILD_LIST:
                t16 = GET_ARG();
                retval = list_new(&pobj1);
                PY_BREAK_IF_ERROR(retval);
                for (; --t16 >= 0;)
                {
                    /* get obj */
                    pobj2 = PY_POP();
                    /* insert obj into list */
                    retval = list_insert(pobj1, pobj2, 0);
                    PY_BREAK_IF_ERROR(retval);
                }
                /* push list onto stack */
                PY_PUSH(pobj1);
                continue;

            case BUILD_MAP:
                retval = dict_new(&pobj1);
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj1);
                continue;

            case LOAD_ATTR:
                t16 = GET_ARG();
                /* get obj that has the attrs */
                pobj1 = PY_POP();
                /* get attrs dict from obj */
                if ((pobj1->od.od_type == OBJ_TYPE_FXN) ||
                    (pobj1->od.od_type == OBJ_TYPE_COB) ||
                    (pobj1->od.od_type == OBJ_TYPE_MOD))
                {
                    pobj1 = (pPyObj_t)((pPyFunc_t)pobj1)->
                                    f_attrs;
                }
                else
                {
                    /* Other types result in a TypeError */
                    retval = PY_RET_EX_TYPE;
                    break;
                }
                /* if attrs is not a dict, raise SystemError */
                if (pobj1->od.od_type != OBJ_TYPE_DIC)
                {
                    retval = PY_RET_EX_SYS;
                    break;
                }
                /* get name */
                pobj2 = FP->fo_func->f_co->co_names->val[t16];
                /* push attr with given name onto stack */
                retval = dict_getItem(pobj1, pobj2, &pobj3);
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj3);
                continue;

            case COMPARE_OP:
                pobj1 = PY_POP();
                pobj2 = PY_POP();
                t16 = GET_ARG();
                if ((pobj1->od.od_type == OBJ_TYPE_INT) &&
                    (pobj2->od.od_type == OBJ_TYPE_INT))
                {
                    S32 a = ((pPyInt_t)pobj2)->val;
                    S32 b = ((pPyInt_t)pobj1)->val;

                    switch (t16)
                    {
                        case COMP_LT: t8 = (a <  b); break;
                        case COMP_LE: t8 = (a <= b); break;
                        case COMP_EQ: t8 = (a == b); break;
                        case COMP_NE: t8 = (a != b); break;
                        case COMP_GT: t8 = (a >  b); break;
                        case COMP_GE: t8 = (a >= b); break;
                        /* XXX the next don't really work */
                        case COMP_IS:
                            t8 = (pobj1 == pobj2); break;
                        case COMP_IS_NOT:
                            t8 = (pobj1 != pobj2); break;
                        default:
                            /* XXX goto slow_compare */
                            PY_ERR(ERR_ARG);
                    }
                    pobj3 = (t8) ? PY_TRUE : PY_FALSE;
                }
                else if (t16 == COMP_EQ)
                {
                    if (obj_compare(pobj1, pobj2) == C_SAME)
                    {
                        pobj3 = PY_TRUE;
                    }
                    else
                    {
                        pobj3 = PY_FALSE;
                    }
                }
                else if (t16 == COMP_NE)
                {
                    if (obj_compare(pobj1, pobj2) == C_DIFFER)
                    {
                        pobj3 = PY_TRUE;
                    }
                    else
                    {
                        pobj3 = PY_FALSE;
                    }
                }
                /* XXX TODO: goto slow_compare */
                else
                {
                    PY_ERR(__LINE__);
                }
                PY_PUSH(pobj3);
                continue;

            case IMPORT_NAME:
                /* get name index */
                t16 = GET_ARG();
                /* get name String obj */
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* XXX check if module is already loaded */
                /* load module from image */
                retval = mod_import(pobj1, (pPyFunc_t *)&pobj2);
                PY_BREAK_IF_ERROR(retval);
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
                retval = interpret((pPyFunc_t)pobj2);
                PY_BREAK_IF_ERROR(retval);
                gVmGlobal.interpctrl = INTERP_CTRL_CONT;
                continue;

            case IMPORT_FROM:
            case UNUSED_6D:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
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
                pobj1 = PY_POP();
                /* get the sequence */
                pobj2 = PY_POP();

                /* ensure index is an int */
                if (pobj1->od.od_type != OBJ_TYPE_INT)
                {
                    retval = PY_RET_EX_INDX;
                    break;
                }
                /* dup a const int to allow it to incr (TRASH)*/
                if (pobj1->od.od_const != 0)
                {
                    retval = int_dup(pobj1, &pobj1);
                    PY_BREAK_IF_ERROR(retval);
                }

                /* if it's a tuple */
                if (pobj2->od.od_type == OBJ_TYPE_TUP)
                {
                    /* if tup is exhausted, incr IP by delta */
                    if (((pPyInt_t)pobj1)->val >=
                        ((pPyTuple_t)pobj2)->length)
                    {
                        IP += t16;
                        continue;
                    }

                    /* get item, incr counter */
                    pobj3 = ((pPyTuple_t)pobj2)->val[
                                ((pPyInt_t)pobj1)->val++];
                }

                /* if it's a list */
                else if (pobj2->od.od_type == OBJ_TYPE_LST)
                {
                    /* if list is exhausted, incr IP by delta */
                    if (((pPyInt_t)pobj1)->val >=
                        ((pPyList_t)pobj2)->length)
                    {
                        IP += t16;
                        continue;
                    }

                    /* get item */
                    retval = list_getItem(pobj2,
                                          (S16)(((pPyInt_t)
                                                pobj1)->val),
                                          &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                    /* incr counter */
                    ((pPyInt_t)pobj1)->val++;
                }

                /* XXX if it's a string */

                /* TypeError: loop over non-sequence */
                else
                {
                    retval = PY_RET_EX_TYPE;
                    break;
                }

                /* push tup, counter and item */
                PY_PUSH(pobj2);
                PY_PUSH(pobj1);
                PY_PUSH(pobj3);
                continue;

            case UNUSED_73:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case LOAD_GLOBAL:
                /* get name */
                t16 = GET_ARG();
                pobj1 = FP->fo_func->f_co->co_names->val[t16];
                /* try globals first */
                retval = dict_getItem((pPyObj_t)FP->fo_globals,
                                      pobj1,
                                      &pobj2);
                /* if that didn't work, try builtins */
                if (retval == PY_RET_EX_KEY)
                {
                    retval = dict_getItem(PY_PBUILTINS, pobj1, &pobj2);
                    /* no such global, raise NameError */
                    if (retval == PY_RET_EX_KEY)
                    {
                        retval = PY_RET_EX_NAME;
                        break;
                    }
                }
                PY_BREAK_IF_ERROR(retval);
                PY_PUSH(pobj2);
                continue;

            case UNUSED_75:
            case UNUSED_76:
            case CONTINUE_LOOP:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case SETUP_LOOP:
                /* get block span (bytes) */
                t16 = GET_ARG();
                /* create block */
                retval = heap_getChunk(sizeof(PyBlock_t), (P_U8 *)&pobj1);
                PY_BREAK_IF_ERROR(retval);
                ((pPyBlock_t)pobj1)->od.od_type = OBJ_TYPE_BLK;
                /* store current stack pointer */
                ((pPyBlock_t)pobj1)->b_sp = SP;
                /* default handler is to exit block/loop */
                ((pPyBlock_t)pobj1)->b_handler = IP + t16;
                ((pPyBlock_t)pobj1)->b_type = B_LOOP;
                /* insert block into blockstack */
                ((pPyBlock_t)pobj1)->next = FP->fo_blockstack;
                FP->fo_blockstack = (pPyBlock_t)pobj1;
                continue;

            case SETUP_EXCEPT:
            case SETUP_FINALLY:
            case UNUSED_7B:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case LOAD_FAST:
                t16 = GET_ARG();
                PY_PUSH(FP->fo_locals[t16]);
                continue;

            case STORE_FAST:
                t16 = GET_ARG();
                FP->fo_locals[t16] = PY_POP();
                continue;

            case DELETE_FAST:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case SET_LINENO:
                FP->fo_line = GET_ARG();
                continue;

            case UNUSED_80:
            case UNUSED_81:
            case RAISE_VARARGS:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

            case CALL_FUNCTION:
                /* get num args */
                t16 = GET_ARG();
                /* ensure no keyword args */
                if ((t16 > 255) || (t16 < 0))
                {
                    PY_ERR(__LINE__);
                }
                /* get the func */
                pobj1 = STACK(t16);

                /* if it's regular func (not native) */
                if (((pPyFunc_t)pobj1)->f_co->od.od_type ==
                    OBJ_TYPE_COB)
                {
                    /* make frameObj from pCO */
                    retval = frame_new(pobj1, &pobj2);
                    PY_BREAK_IF_ERROR(retval);
                    /* frame's globals is same as parent's */
                    ((pPyFrame_t)pobj2)->fo_globals =
                            FP->fo_globals;
                    /* pass args to new frame */
                    while (--t16 >= 0)
                    {
                        /*
                         * pop args from stack.
                         * args are pushed left to right,
                         * so pop right to left.
                         */
                        ((pPyFrame_t)pobj2)->fo_locals[t16] =
                                PY_POP();
                    }
                    /* pop func obj */
                    pobj3 = PY_POP();
                    /* keep ref to current frame */
                    ((pPyFrame_t)pobj2)->fo_back = FP;
                    /* set new frame */
                    FP = (pPyFrame_t)pobj2;
                }

                /* if it's native func */
                else if (((pPyFunc_t)pobj1)->f_co->od.od_type ==
                         OBJ_TYPE_NOB)
                {
                    /* ensure num args fits in native frame */
                    if (t16 > NATIVE_NUM_LOCALS)
                    {
                        PY_ERR(__LINE__);
                    }

                    /* keep numargs */
                    t8 = (S8)t16;

                    /* pop args from stack */
                    while (--t16 >= 0)
                    {
                        gVmGlobal.nativeframe.nf_locals[t16] =
                                PY_POP();
                    }
                    /* get native function index */
                    t16 = (S16)((pPyNo_t)((pPyFunc_t)pobj1)->
                                f_co)->no_funcindx;
                    /*
                     * CALL NATIVE FXN
                     * pass caller's frame and numargs
                     */
                    retval = nat_fxn_table[t16](FP, t8);
                    /*
                     * RETURN FROM NATIVE FXN
                     */

                    /* pop func, push result */
                    TOS = gVmGlobal.nativeframe.nf_stack;
                    PY_BREAK_IF_ERROR(retval);
                }
                continue;

            case MAKE_FUNCTION:
                /* get num default args to fxn */
                t16 = GET_ARG();
                /* load func from CO */
                pobj1 = PY_POP();
                retval = func_new(pobj1, &pobj2);
                PY_BREAK_IF_ERROR(retval);
                /* put any default args in a tuple */
                if (t16 > 0)
                {
                    retval = tuple_new(t16, &pobj3);
                    PY_BREAK_IF_ERROR(retval);
                    while (--t16 >= 0)
                    {
                        ((pPyTuple_t)pobj3)->val[t16] =
                                PY_POP();
                    }
                    /* set func's default args */
                    ((pPyFunc_t)pobj2)->f_defaultargs =
                                ((pPyTuple_t)pobj3);
                }
                /* push func obj */
                PY_PUSH(pobj2);
                continue;

            case BUILD_SLICE:
            case MAKE_CLOSURE:
            case LOAD_CLOSURE:
            case LOAD_DEREF:
            case STORE_DEREF:
            case UNUSED_8A:
            case UNUSED_8B:
            case CALL_FUNCTION_VAR:
            case CALL_FUNCTION_KW:
            case CALL_FUNCTION_VAR_KW:
            case EXTENDED_ARG:
/*
            case UNUSED_90: case UNUSED_91:
            case UNUSED_92: case UNUSED_93:
            case UNUSED_94: case UNUSED_95:
            case UNUSED_96: case UNUSED_97:
            case UNUSED_98: case UNUSED_99:
            case UNUSED_9A: case UNUSED_9B:
            case UNUSED_9C: case UNUSED_9D:
            case UNUSED_9E: case UNUSED_9F:
            case UNUSED_A0: case UNUSED_A1:
            case UNUSED_A2: case UNUSED_A3:
            case UNUSED_A4: case UNUSED_A5:
            case UNUSED_A6: case UNUSED_A7:
            case UNUSED_A8: case UNUSED_A9:
            case UNUSED_AA: case UNUSED_AB:
            case UNUSED_AC: case UNUSED_AD:
            case UNUSED_AE: case UNUSED_AF:
            case UNUSED_B0: case UNUSED_B1:
            case UNUSED_B2: case UNUSED_B3:
            case UNUSED_B4: case UNUSED_B5:
            case UNUSED_B6: case UNUSED_B7:
            case UNUSED_B8: case UNUSED_B9:
            case UNUSED_BA: case UNUSED_BB:
            case UNUSED_BC: case UNUSED_BD:
            case UNUSED_BE: case UNUSED_BF:
            case UNUSED_C0: case UNUSED_C1:
            case UNUSED_C2: case UNUSED_C3:
            case UNUSED_C4: case UNUSED_C5:
            case UNUSED_C6: case UNUSED_C7:
            case UNUSED_C8: case UNUSED_C9:
            case UNUSED_CA: case UNUSED_CB:
            case UNUSED_CC: case UNUSED_CD:
            case UNUSED_CE: case UNUSED_CF:
            case UNUSED_D0: case UNUSED_D1:
            case UNUSED_D2: case UNUSED_D3:
            case UNUSED_D4: case UNUSED_D5:
            case UNUSED_D6: case UNUSED_D7:
            case UNUSED_D8: case UNUSED_D9:
            case UNUSED_DA: case UNUSED_DB:
            case UNUSED_DC: case UNUSED_DD:
            case UNUSED_DE: case UNUSED_DF:
            case UNUSED_E0: case UNUSED_E1:
            case UNUSED_E2: case UNUSED_E3:
            case UNUSED_E4: case UNUSED_E5:
            case UNUSED_E6: case UNUSED_E7:
            case UNUSED_E8: case UNUSED_E9:
            case UNUSED_EA: case UNUSED_EB:
            case UNUSED_EC: case UNUSED_ED:
            case UNUSED_EE: case UNUSED_EF:
            case UNUSED_F0: case UNUSED_F1:
            case UNUSED_F2: case UNUSED_F3:
            case UNUSED_F4: case UNUSED_F5:
            case UNUSED_F6: case UNUSED_F7:
            case UNUSED_F8: case UNUSED_F9:
            case UNUSED_FA: case UNUSED_FB:
            case UNUSED_FC: case UNUSED_FD:
            case UNUSED_FE: case UNUSED_FF:
*/
            default:
                /* SystemError, unknown opcode */
                retval = PY_RET_EX_SYS;
                break;

        } /* switch (interpret) */

        /*
         * If execution reaches this point, it is because
         * either a return value (from above) is not OK
         * (an error or exception), or the return value is OK
         * and the interpreter is exiting.
         */

        /*
         * The following switch statement is a stub
         * exception handler.
         * It attempts to do something useful
         * for debugging purposes.
         */
        switch (retval)
        {
            case PY_RET_OK:
                /* normal interpreter exit */
                return retval;

            case PY_RET_ERR:
                /* general error */
                PY_ERR(__LINE__);
                break;

            case PY_RET_STUB:
                /* unimplemented fxn error */
                PY_ERR(__LINE__);
                break;

            case PY_RET_ASSERT_FAIL:
                /* assertion failed */
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_EXIT:
                /* TODO: Check for catch before exiting */
                /* SystemExit exception was raised */
                /* If TOS is an int, return its value to main */
                if (obj_isType(TOS, OBJ_TYPE_INT))
                {
                    return (PyReturn_t)((pPyInt_t)TOS)->val;
                }
                break;

            case PY_RET_EX_FLOAT:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_ZDIV:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_ASSRT:
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_ATTR:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_IMPRT:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_INDX:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_KEY:
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_MEM:
                /* OutOfMemoryError */
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_NAME:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_RUNTIME:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_SYNTAX:
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_SYS:
                /* SystemError */
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_TYPE:
                /* TypeError */
                PY_ERR(__LINE__);
                break;

            case PY_RET_EX_VAL:
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX_WARN:
                PY_ERR(__LINE__);
                break;

            case PY_RET_NO:
                /*
                 * ERROR: execution should never reach here;
                 * these are pymite return values,
                 * not Python exception values.
                 */
                PY_ERR(__LINE__);
                break;
            case PY_RET_EX:
                /*
                 * ERROR: execution should never reach here;
                 * these are pymite return values,
                 * not Python exception values.
                 */
                PY_ERR(__LINE__);
                break;

        } /* switch (error/exception) */

		/* unhandled exception, exit */
        /* XXX print stacktrace */
        gVmGlobal.interpctrl = INTERP_CTRL_EXIT;
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
