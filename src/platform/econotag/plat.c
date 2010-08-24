/** @file
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 *
 * some sections based on code (C) COPYRIGHT 2008 STMicroelectronics
 */

#undef __FILE_ID__
#define __FILE_ID__ 0x52

#include <stdio.h>

#include <mc1322x.h>
#include <board.h>

#include "pm.h"


/* Baud rate: 115200 bps, INC=767, MOD=9999, 24Mhz 8x samp */
#define INC 767
#define MOD 9999
#define SAMP UCON_SAMP_8X

/* Timer setup */
#define COUNT_MODE 1      /* Use rising edge of primary source */
#define PRIME_SRC 0xe     /* Div-64 prescale (for 24Mhz = 375000Hz)*/
#define LEN 1             /* Count until compare then reload with LOAD */

/* TMR0 ISR is 1000 Hz == 1 ms == 1000 us) */
#define PLAT_TIME_PER_TICK_USEC 1000


void
tmr0_isr(void)
{
    pm_vmPeriodic(PLAT_TIME_PER_TICK_USEC);

    *TMR0_SCTRL = 0;
    *TMR0_CSCTRL = 0x0040; /* clear compare flag */
}


PmReturn_t
plat_init(void)
{
    trim_xtal();
    uart1_init(INC,MOD,SAMP);
    vreg_init();
    maca_init();
    set_power(0x12);
    set_channel(0);

    /* Use GPIO44 to flash red LED when transmission occurs */
    *GPIO_FUNC_SEL2 = (0x01 << ((44-16*2)*2));
    gpio_pad_dir_set( 1ULL << 44 );

    *TMR_ENBL = 0;          /* Tmrs reset to enabled */
    *TMR0_SCTRL = 0;
    *TMR0_CSCTRL = 0x0040;
    *TMR0_LOAD = 0;         /* Reload to zero */
    *TMR0_COMP_UP = 375;    /* Trigger a reload at the end */
    *TMR0_CMPLD1 = 375;     /* Compare 1 triggered reload level */
    *TMR0_CNTR = 0;         /* Reset count register */
    *TMR0_CTRL = (COUNT_MODE<<13) | (PRIME_SRC<<9) | (LEN<<5);
    *TMR_ENBL = 1;          /* Enable Timer0 */

    /* Seed the random number generator */
    *MACA_RANDOM = 42;

    enable_irq(TMR);

    return PM_RET_OK;
}


PmReturn_t
plat_deinit(void)
{
    maca_off();
    disable_irq(TMR);

    /* Disable UART1 */
    *UART1_UCON = 0;

    return PM_RET_OK;
}


/*
 * Gets a byte from the address in the designated memory space
 * Post-increments *paddr.
 */
uint8_t
plat_memGetByte(PmMemSpace_t memspace, uint8_t const **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
        case MEMSPACE_PROG:
          b = **paddr;
          *paddr += 1;
          return b;
        case MEMSPACE_EEPROM:
        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


PmReturn_t
plat_getByte(uint8_t *b)
{
    *b = uart1_getc();

    return PM_RET_OK;
}


PmReturn_t
plat_putByte(uint8_t b)
{
    uart1_putc(b);

    return PM_RET_OK;
}


PmReturn_t
plat_getMsTicks(uint32_t *r_ticks)
{
    global_irq_disable();
    *r_ticks = pm_timerMsTicks;
    global_irq_enable();

    return PM_RET_OK;
}


void
plat_reportError(PmReturn_t result)
{
    /* Print error */
    printf("Error:     0x%02X\n", result);
    printf("  Release: 0x%02X\n", gVmGlobal.errVmRelease);
    printf("  FileId:  0x%02X\n", gVmGlobal.errFileId);
    printf("  LineNum: %d\n", gVmGlobal.errLineNum);

    /* Print traceback */
    {
        pPmObj_t pframe;
        pPmObj_t pstr;
        PmReturn_t retval;

        printf("Traceback (top first):\n");

        /* Get the top frame */
        pframe = (pPmObj_t)gVmGlobal.pthread->pframe;

        /* If it's the native frame, print the native function name */
        if (pframe == (pPmObj_t)&(gVmGlobal.nativeframe))
        {

            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)gVmGlobal.nativeframe.nf_func->
                                   f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK)
            {
                printf("  Unable to get native func name.\n");
                return;
            }
            else
            {
                printf("  %s() __NATIVE__\n", ((pPmString_t)pstr)->val);
            }

            /* Get the frame that called the native frame */
            pframe = (pPmObj_t)gVmGlobal.nativeframe.nf_back;
        }

        /* Print the remaining frame stack */
        for (;
             pframe != C_NULL;
             pframe = (pPmObj_t)((pPmFrame_t)pframe)->fo_back)
        {
            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)((pPmFrame_t)pframe)->
                                   fo_func->f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK) break;

            printf("  %s()\n", ((pPmString_t)pstr)->val);
        }
        printf("  <module>.\n");
    }
}