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

/**
 * PyMite platform-specific routines for Desktop target
 *
 * Log
 * ---
 *
 * 2006/12/26   #65: Create plat module with put and get routines
 */


/**
 * Initializes the platform as needed by the routines
 * in the platform implementation file.
 */
PmReturn_t plat_init(void);


/**
 * Receives one byte from the default connection,
 * usually UART0 on a target device or stdio on the desktop
 */
PmReturn_t plat_getByte(uint8_t *b);


/**
 * Sends one byte out on the default connection,
 * usually UART0 on a target device or stdio on the desktop
 */
PmReturn_t plat_putByte(uint8_t b);

