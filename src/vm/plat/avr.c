/*
 * PyMite - A flyweight Python interpreter for 8-bit microcontrollers and more.
 * Copyright 2006 Dean Hall
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
#define __FILE_ID__ 0x51
/**
 * PyMite platform-specific routines for AVR target
 *
 * Log
 * ---
 *
 * 2007/01/31   #86: Move platform-specific code to the platform impl file
 * 2007/01/10   #75: Added time tick service for desktop (POSIX) and AVR. (P.Adelt)
 * 2006/12/26   #65: Create plat module with put and get routines
 */


#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "../pm.h"


/***************************************************************
 * Configuration
 **************************************************************/

/**
 * When defined, the AVR target configures Timer/Counter0 to generate an
 * overflow interrupt to call pm_vmPeriodic().
 * If you configure T/C0 yourself, disable this define and be sure to
 * periodically call pm_vmPeriodic(usec)!
 * Has no meaning on non-AVR.
 */
#define AVR_DEFAULT_TIMER_SOURCE


/***************************************************************
 * Constants
 **************************************************************/
 
#ifdef AVR_DEFAULT_TIMER_SOURCE

/* Hint: 1,000,000 µs/s * 256 T/C0 clock cycles per tick * 8 CPU clocks per  
 * T/C0 clock cycle / x,000,000 CPU clock cycles per second -> µs per tick  
 */  
#define PLAT_TIME_PER_TICK_USEC (1000000ULL*256ULL*8ULL/F_CPU)

#endif /* AVR_DEFAULT_TIMER_SOURCE */
  
/***************************************************************
 * Defines
 **************************************************************/

/***************************************************************
 * Functions
 **************************************************************/


/*
 * AVR target shall use stdio for I/O routines.
 * The UART or USART must be configured for the interactive interface to work.
 */
PmReturn_t
plat_init(void)
{
    /* PORT BEGIN: Set these UART/USART SFRs properly for your AVR */

    /* Set the baud rate register */
    UBRR = (F_CPU / (16UL * UART_BAUD)) - 1;

    /* Enable the transmit and receive pins */
    UCR = _BV(TXEN) | _BV(RXEN);
    /* PORT END */
    
    #ifdef AVR_DEFAULT_TIMER_SOURCE
    /* PORT BEGIN: Configure a timer that fits your needs. */
    /* Use T/C0 in synchronous mode, aim for a tick rate of
     * several hundred Hz */
    #if (TARGET_MCU == atmega103) || (TARGET_MCU == atmega128)
    /* set T/C0 to use synchronous clock */
    ASSR &= ~(1<<AS0);
    /* set prescaler to /8 */
    TCCR0 &= ~0x07;
    TCCR0 |= (1<<CS01);
    #else
    #error No timer configuration is implemented for this AVR.
    #endif 
    #endif /* AVR_DEFAULT_TIMER_SOURCE */
    /* PORT END */

    return PM_RET_OK;
}

#ifdef AVR_DEFAULT_TIMER_SOURCE
ISR(TIMER0_OVF_vect) 
{
    /* TODO Find a clever way to handle bad return code, maybe use 
     * PM_PRINT_IF_ERROR(retval) when that works on AVR inside an
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
plat_memGetByte(PmMemSpace_t memspace, uint8_t **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
            b = **paddr;
            *paddr += 1;
            return b;

        case MEMSPACE_FLASH:
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


/*
 * UART receive char routine MUST return exactly and only the received char;
 * it should not translate \n to \r\n.
 * This is because the interactive interface uses binary transfers.
 */
PmReturn_t
plat_getByte(uint8_t *b)
{
    PmReturn_t retval = PM_RET_OK;

    /* PORT BEGIN: Set these UART/USART SFRs properly for your AVR */
    /* Loop until serial receive is complete */
    loop_until_bit_is_set(USR, RXC);
    
    /* If a framing error or data overrun occur, raise an IOException */
    if (UCR & (_BV(FE) | _BV(DOR)))
    {
        PM_RAISE(retval, PM_RET_EX_IO);
        return retval;
    }
    *b = UDR;
    /* PORT END */

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
    /* PORT BEGIN: Set these UART/USART SFRs properly for your AVR */
    /* Loop until serial data reg is empty (from previous transfer) */
    loop_until_bit_is_set(USR, UDRE);
    
    /* Put the byte to send into the serial data register */
    UDR = b;
    /* PORT END */

    return PM_RET_OK;
}

/* remember that 32bit-accesses are non-atomic on AVR */
uint32_t
plat_getMsTicks(void)
{
    uint32_t result;
    /* Critical section start */
    unsigned char _sreg = SREG;
    cli();
    result = pm_timerMsTicks;
    SREG = _sreg;
    /* Critical section end */
    return result;
}
