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

/**
 * VM feature configuration
 *
 * Compile time switches to include features or save space.
 *
 * Log
 * ---
 *
 * 2007/01/09   #75: First (P.Adelt)
 */


#ifndef FEATURES_H_
#define FEATURES_H_

/**
 * When defined, bytecodes PRINT_ITEM and PRINT_NEWLINE are supported. Along
 * with these, helper routines in the object type are compiled in that allow
 * printing of the object.
 */
#define HAVE_PRINT 

/**
 * When defined, the AVR target configures Timer/Counter0 to generate an
 * overflow interrupt to call pm_vmPeriodic().
 * If you configure T/C0 yourself, disable this define and be sure to
 * periodically call pm_vmPeriodic(usec)!
 * Has no meaning on non-AVR.
 */
#define AVR_DEFAULT_TIMER_SOURCE

#endif /*FEATURES_H_*/
