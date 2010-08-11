/*
# This file is Copyright 2006, 2007, 2009 Dean Hall.
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


#undef __FILE_ID__
#define __FILE_ID__ 0x70


/** PyMite platform-specific routines for AVR target */


#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "pm.h"
#include "usb_serial.h"

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))

/**
 * When defined, the AVR target configures Timer/Counter0 to generate an
 * overflow interrupt to call pm_vmPeriodic().
 * If you configure T/C0 yourself, disable this define and be sure to
 * periodically call pm_vmPeriodic(usec)!
 * Has no meaning on non-AVR.
 */
#define AVR_DEFAULT_TIMER_SOURCE


#ifdef AVR_DEFAULT_TIMER_SOURCE

/* Hint: 1,000,000 µs/s * 256 T/C0 clock cycles per tick * 64 CPU clocks per
 * T/C0 clock cycle / x,000,000 CPU clock cycles per second -> µs per tick
 */
#define PLAT_TIME_PER_TICK_USEC (1000000ULL*256ULL*64ULL/F_CPU)

#endif /* AVR_DEFAULT_TIMER_SOURCE */


/* Configure stdin, stdout, stderr */
static int uart_putc(char c, FILE *stream);
static int uart_getc(FILE *stream);
FILE avr_uart = FDEV_SETUP_STREAM(uart_putc, uart_getc, _FDEV_SETUP_RW);


/*
 * AVR target shall use stdio for I/O routines.
 * The UART or USART must be configured for the interactive interface to work.
 */
PmReturn_t
plat_init(void)
{
    CPU_PRESCALE(0);
    usb_init();
    while(!usb_configured()) _delay_ms(1);

    stdin = stdout = stderr = &avr_uart;

#ifdef AVR_DEFAULT_TIMER_SOURCE
    /* PORT BEGIN: Configure a timer that fits your needs. */
    /* Use T/C0 in synchronous mode, aim for a tick rate of
     * several hundred Hz */
    /* set prescaler to /64 */
    TCCR0B |= (1<<CS01) | (1<<CS00); // (this should be all you need for AT90USBxxx)
    TIMSK0 |= (1<<TOIE0);
#endif

    return PM_RET_OK;
}


PmReturn_t
plat_deinit(void)
{
#ifdef AVR_DEFAULT_TIMER_SOURCE
    /* Disable Timer */
    TCCR0B = 0;
    TIMSK0 &= ~(1<<TOIE0);
#endif

    usb_serial_flush_input();
    usb_serial_flush_output();
    _delay_ms(5000);

    return PM_RET_OK;
}


#ifdef AVR_DEFAULT_TIMER_SOURCE
ISR(TIMER0_OVF_vect)
{
    /* TODO Find a clever way to handle bad return code, maybe use
     * PM_REPORT_IF_ERROR(retval) when that works on AVR inside an
     * interrupt.
     */
    pm_vmPeriodic(PLAT_TIME_PER_TICK_USEC);
}
#endif


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
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_PROG:
            b = pgm_read_byte(*paddr);
            *paddr += 1;
            return b;

        case MEMSPACE_EEPROM:
            b = eeprom_read_byte(*paddr);
            *paddr += 1;
            return b;

        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


static int
uart_getc(FILE *stream)
{
    int c = usb_serial_getchar();
    return (c == -1) ? _FDEV_ERR : c;
}


static int
uart_putc(char c, FILE *stream)
{
    return usb_serial_putchar(c) == 0 ? 0 : _FDEV_ERR;
}


/*
 * UART receive char routine MUST return exactly and only the received char;
 * it should not translate \n to \r\n.
 * This is because the interactive interface uses binary transfers.
 */
PmReturn_t
plat_getByte(uint8_t *b)
{
    PmReturn_t retval = PM_RET_OK;

    int c = usb_serial_getchar();
    if(c == -1)
    {
        PM_RAISE(retval, PM_RET_EX_IO);
        return retval;
    }
    *b = c;
    return retval;
}


/*
 * UART send char routine MUST send exactly and only the given char;
 * it should not translate \n to \r\n.
 * This is because the interactive interface uses binary transfers.
 */
PmReturn_t
plat_putByte(uint8_t b)
{
    PmReturn_t retval = PM_RET_OK;
    if(usb_serial_putchar(b) == 0)
    {
        return retval;
    }
    else
    {
        PM_RAISE(retval, PM_RET_EX_IO);
        return retval;
    }
}


/*
 * This operation is made atomic by temporarily disabling
 * the interrupts. The old state is restored afterwards.
 */
PmReturn_t
plat_getMsTicks(uint32_t *r_ticks)
{
    /* Critical section start */
    unsigned char _sreg = SREG;
    cli();
    *r_ticks = pm_timerMsTicks;
    SREG = _sreg;
    /* Critical section end */
    return PM_RET_OK;
}


void
plat_reportError(PmReturn_t result)
{
    /* Print error */
    printf_P(PSTR("Error:     0x%02X\n"), result);
    printf_P(PSTR("  Release: 0x%02X\n"), gVmGlobal.errVmRelease);
    printf_P(PSTR("  FileId:  0x%02X\n"), gVmGlobal.errFileId);
    printf_P(PSTR("  LineNum: %d\n"), gVmGlobal.errLineNum);

    /* Print traceback */
    {
        pPmObj_t pframe;
        pPmObj_t pstr;
        PmReturn_t retval;

        puts_P(PSTR("Traceback (top first):"));

        /* Get the top frame */
        pframe = (pPmObj_t)gVmGlobal.pthread->pframe;

        /* If it's the native frame, print the native function name */
        if (pframe == (pPmObj_t)&(gVmGlobal.nativeframe))
        {

            /* The last name inthe names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)gVmGlobal.nativeframe.nf_func->
                                   f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK)
            {
                puts_P(PSTR("  Unable to get native func name."));
                return;
            }
            else
            {
                printf_P(PSTR("  %s() __NATIVE__\n"), ((pPmString_t)pstr)->val);
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

            printf_P(PSTR("  %s()\n"), ((pPmString_t)pstr)->val);
        }
        puts_P(PSTR("  <module>."));
    }
}
