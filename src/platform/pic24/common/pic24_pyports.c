/*
 * "Copyright (c) 2008 Robert B. Reese, Bryan A. Jones, J. W. Bruce ("AUTHORS")"
 * All rights reserved.
 * (R. Reese, reese_AT_ece.msstate.edu, Mississippi State University)
 * (B. A. Jones, bjones_AT_ece.msstate.edu, Mississippi State University)
 * (J. W. Bruce, jwbruce_AT_ece.msstate.edu, Mississippi State University)
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the authors appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE "AUTHORS" BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE "AUTHORS"
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE "AUTHORS" SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE "AUTHORS" HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Please maintain this header in its entirety when copying/modifying
 * these files.
 *
 *
 */


// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  \brief This file supports Python-based configuration of 
 *  IO ports on the PIC24.
 */

#include "pic24_all.h"
#include "pyFuncsInC.h"
#include "pyToC.h"
#include <pps.h>

#undef __FILE_ID__
#define __FILE_ID__ 0x70


///\todo A hack to work around PIC header file bugs: the open-drain capabilities
/// are misreported. When this is fixed, remove this!
#ifdef UNIT_TEST
#undef _ODCA0
#endif


bool_t 
getBit(uint16_t u16_bitfield, uint16_t u16_bit)
{
    ASSERT(u16_bit < 16);
    return (u16_bitfield & (1 << u16_bit)) ? C_TRUE : C_FALSE;
}


void
setBit(volatile uint16_t* pu16_bitfield, uint16_t u16_bit, bool_t b_val)
{
    ASSERT(u16_bit < 16);
    if (b_val)
        *pu16_bitfield |= 1 << u16_bit;
    else
        *pu16_bitfield &= ~(1 << u16_bit);
}


// These macros auto-generate the bits by testing for their presense
// as macros in the chip-specific include file.
/** This variable stores a bitmap describing which digitial I/O pins exist
 *  on the current processor. Port A is stored at [0], B at [1], etc. A value
 *  of 1 for a gvien bit indicates the corresponding pin of that port exists.
 *  For example, 0x0001 indicates that only pin 0 of the selected port exists, 
 *  while pins 1-15 do not.
 */
static const uint16_t u16_digitalPinPresent[NUM_DIGITAL_PORTS] = { 
  #if NUM_DIGITAL_PORTS >= 1
    #ifdef _RA0
      0x0001 |
    #endif
    #ifdef _RA1
      0x0002 |
    #endif
    #ifdef _RA2
      0x0004 |
    #endif
    #ifdef _RA3
      0x0008 |
    #endif
    #ifdef _RA4
      0x0010 |
    #endif
    #ifdef _RA5
      0x0020 |
    #endif
    #ifdef _RA6
      0x0040 |
    #endif
    #ifdef _RA7
      0x0080 |
    #endif
    #ifdef _RA8
      0x0100 |
    #endif
    #ifdef _RA9
      0x0200 |
    #endif
    #ifdef _RA10
      0x0400 |
    #endif
    #ifdef _RA11
      0x0800 |
    #endif
    #ifdef _RA12
      0x1000 |
    #endif
    #ifdef _RA13
      0x2000 |
    #endif
    #ifdef _RA14
      0x4000 |
    #endif
    #ifdef _RA15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 2
    #ifdef _RB0
      0x0001 |
    #endif
    #ifdef _RB1
      0x0002 |
    #endif
    #ifdef _RB2
      0x0004 |
    #endif
    #ifdef _RB3
      0x0008 |
    #endif
    #ifdef _RB4
      0x0010 |
    #endif
    #ifdef _RB5
      0x0020 |
    #endif
    #ifdef _RB6
      0x0040 |
    #endif
    #ifdef _RB7
      0x0080 |
    #endif
    #ifdef _RB8
      0x0100 |
    #endif
    #ifdef _RB9
      0x0200 |
    #endif
    #ifdef _RB10
      0x0400 |
    #endif
    #ifdef _RB11
      0x0800 |
    #endif
    #ifdef _RB12
      0x1000 |
    #endif
    #ifdef _RB13
      0x2000 |
    #endif
    #ifdef _RB14
      0x4000 |
    #endif
    #ifdef _RB15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 3
    #ifdef _RC0
      0x0001 |
    #endif
    #ifdef _RC1
      0x0002 |
    #endif
    #ifdef _RC2
      0x0004 |
    #endif
    #ifdef _RC3
      0x0008 |
    #endif
    #ifdef _RC4
      0x0010 |
    #endif
    #ifdef _RC5
      0x0020 |
    #endif
    #ifdef _RC6
      0x0040 |
    #endif
    #ifdef _RC7
      0x0080 |
    #endif
    #ifdef _RC8
      0x0100 |
    #endif
    #ifdef _RC9
      0x0200 |
    #endif
    #ifdef _RC10
      0x0400 |
    #endif
    #ifdef _RC11
      0x0800 |
    #endif
    #ifdef _RC12
      0x1000 |
    #endif
    #ifdef _RC13
      0x2000 |
    #endif
    #ifdef _RC14
      0x4000 |
    #endif
    #ifdef _RC15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 4
    #ifdef _RD0
      0x0001 |
    #endif
    #ifdef _RD1
      0x0002 |
    #endif
    #ifdef _RD2
      0x0004 |
    #endif
    #ifdef _RD3
      0x0008 |
    #endif
    #ifdef _RD4
      0x0010 |
    #endif
    #ifdef _RD5
      0x0020 |
    #endif
    #ifdef _RD6
      0x0040 |
    #endif
    #ifdef _RD7
      0x0080 |
    #endif
    #ifdef _RD8
      0x0100 |
    #endif
    #ifdef _RD9
      0x0200 |
    #endif
    #ifdef _RD10
      0x0400 |
    #endif
    #ifdef _RD11
      0x0800 |
    #endif
    #ifdef _RD12
      0x1000 |
    #endif
    #ifdef _RD13
      0x2000 |
    #endif
    #ifdef _RD14
      0x4000 |
    #endif
    #ifdef _RD15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 5
    #ifdef _RE0
      0x0001 |
    #endif
    #ifdef _RE1
      0x0002 |
    #endif
    #ifdef _RE2
      0x0004 |
    #endif
    #ifdef _RE3
      0x0008 |
    #endif
    #ifdef _RE4
      0x0010 |
    #endif
    #ifdef _RE5
      0x0020 |
    #endif
    #ifdef _RE6
      0x0040 |
    #endif
    #ifdef _RE7
      0x0080 |
    #endif
    #ifdef _RE8
      0x0100 |
    #endif
    #ifdef _RE9
      0x0200 |
    #endif
    #ifdef _RE10
      0x0400 |
    #endif
    #ifdef _RE11
      0x0800 |
    #endif
    #ifdef _RE12
      0x1000 |
    #endif
    #ifdef _RE13
      0x2000 |
    #endif
    #ifdef _RE14
      0x4000 |
    #endif
    #ifdef _RE15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 6
    #ifdef _RF0
      0x0001 |
    #endif
    #ifdef _RF1
      0x0002 |
    #endif
    #ifdef _RF2
      0x0004 |
    #endif
    #ifdef _RF3
      0x0008 |
    #endif
    #ifdef _RF4
      0x0010 |
    #endif
    #ifdef _RF5
      0x0020 |
    #endif
    #ifdef _RF6
      0x0040 |
    #endif
    #ifdef _RF7
      0x0080 |
    #endif
    #ifdef _RF8
      0x0100 |
    #endif
    #ifdef _RF9
      0x0200 |
    #endif
    #ifdef _RF10
      0x0400 |
    #endif
    #ifdef _RF11
      0x0800 |
    #endif
    #ifdef _RF12
      0x1000 |
    #endif
    #ifdef _RF13
      0x2000 |
    #endif
    #ifdef _RF14
      0x4000 |
    #endif
    #ifdef _RF15
      0x8000 |
    #endif
    0x0000,
  #endif

  #if NUM_DIGITAL_PORTS >= 7
    #ifdef _RG0
      0x0001 |
    #endif
    #ifdef _RG1
      0x0002 |
    #endif
    #ifdef _RG2
      0x0004 |
    #endif
    #ifdef _RG3
      0x0008 |
    #endif
    #ifdef _RG4
      0x0010 |
    #endif
    #ifdef _RG5
      0x0020 |
    #endif
    #ifdef _RG6
      0x0040 |
    #endif
    #ifdef _RG7
      0x0080 |
    #endif
    #ifdef _RG8
      0x0100 |
    #endif
    #ifdef _RG9
      0x0200 |
    #endif
    #ifdef _RG10
      0x0400 |
    #endif
    #ifdef _RG11
      0x0800 |
    #endif
    #ifdef _RG12
      0x1000 |
    #endif
    #ifdef _RG13
      0x2000 |
    #endif
    #ifdef _RG14
      0x4000 |
    #endif
    #ifdef _RG15
      0x8000 |
    #endif
    0x0000,
  #endif
  };






// These macro auto-generate the bits by testing for their presense
// as macros in the chip-specific include file. Note that the bit
// name for PIC24H and dsPIC33 processors is _ODCxy, while PIC24F 
// uses _ODxy. Therefore, these macros test for both.
/** This variable stores a bitmap describing which digitial I/O pins can be
 *  configured as open-drain outputs on the current processor. Port A is 
 *  stored at [0], B at [1], etc. A value of 1 for a gvien bit indicates 
 *  the corresponding pin of that port can be made open-drain. For example, 
 *  0x0001 indicates that only pin 0 of the selected port can be made, 
 *  open-drain, while pins 1-15 operator only in the standard, totem-pole
 *  output configuration.
 */
static const uint16_t u16_digitalPinOpenDrainPresent[NUM_DIGITAL_PORTS] = {
  #if NUM_DIGITAL_PORTS >= 1
    #if defined(_ODCA0)  || defined(_ODA0)
      0x0001 |
    #endif
    #if defined(_ODCA1)  || defined(_ODA1)
      0x0002 |
    #endif
    #if defined(_ODCA2)  || defined(_ODA2)
      0x0004 |
    #endif
    #if defined(_ODCA3)  || defined(_ODA3)
      0x0008 |
    #endif
    #if defined(_ODCA4)  || defined(_ODA4)
      0x0010 |
    #endif
    #if defined(_ODCA5)  || defined(_ODA5)
      0x0020 |
    #endif
    #if defined(_ODCA6)  || defined(_ODA6)
      0x0040 |
    #endif
    #if defined(_ODCA7)  || defined(_ODA7)
      0x0080 |
    #endif
    #if defined(_ODCA8)  || defined(_ODA8)
      0x0100 |
    #endif
    #if defined(_ODCA9)  || defined(_ODA9)
      0x0200 |
    #endif
    #if defined(_ODCA10) || defined(_ODA10)
      0x0400 |
    #endif
    #if defined(_ODCA11) || defined(_ODA11)
      0x0800 |
    #endif
    #if defined(_ODCA12) || defined(_ODA12)
      0x1000 |
    #endif
    #if defined(_ODCA13) || defined(_ODA13)
      0x2000 |
    #endif
    #if defined(_ODCA14) || defined(_ODA14)
      0x4000 |
    #endif
    #if defined(_ODCA15) || defined(_ODA15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 2
    #if defined(_ODCB0)  || defined(_ODB0)
      0x0001 |
    #endif
    #if defined(_ODCB1)  || defined(_ODB1)
      0x0002 |
    #endif
    #if defined(_ODCB2)  || defined(_ODB2)
      0x0004 |
    #endif
    #if defined(_ODCB3)  || defined(_ODB3)
      0x0008 |
    #endif
    #if defined(_ODCB4)  || defined(_ODB4)
      0x0010 |
    #endif
    #if defined(_ODCB5)  || defined(_ODB5)
      0x0020 |
    #endif
    #if defined(_ODCB6)  || defined(_ODB6)
      0x0040 |
    #endif
    #if defined(_ODCB7)  || defined(_ODB7)
      0x0080 |
    #endif
    #if defined(_ODCB8)  || defined(_ODB8)
      0x0100 |
    #endif
    #if defined(_ODCB9)  || defined(_ODB9)
      0x0200 |
    #endif
    #if defined(_ODCB10) || defined(_ODB10)
      0x0400 |
    #endif
    #if defined(_ODCB11) || defined(_ODB11)
      0x0800 |
    #endif
    #if defined(_ODCB12) || defined(_ODB12)
      0x1000 |
    #endif
    #if defined(_ODCB13) || defined(_ODB13)
      0x2000 |
    #endif
    #if defined(_ODCB14) || defined(_ODB14)
      0x4000 |
    #endif
    #if defined(_ODCB15) || defined(_ODB15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 3
    #if defined(_ODCC0)  || defined(_ODC0)
      0x0001 |
    #endif
    #if defined(_ODCC1)  || defined(_ODC1)
      0x0002 |
    #endif
    #if defined(_ODCC2)  || defined(_ODC2)
      0x0004 |
    #endif
    #if defined(_ODCC3)  || defined(_ODC3)
      0x0008 |
    #endif
    #if defined(_ODCC4)  || defined(_ODC4)
      0x0010 |
    #endif
    #if defined(_ODCC5)  || defined(_ODC5)
      0x0020 |
    #endif
    #if defined(_ODCC6)  || defined(_ODC6)
      0x0040 |
    #endif
    #if defined(_ODCC7)  || defined(_ODC7)
      0x0080 |
    #endif
    #if defined(_ODCC8)  || defined(_ODC8)
      0x0100 |
    #endif
    #if defined(_ODCC9)  || defined(_ODC9)
      0x0200 |
    #endif
    #if defined(_ODCC10) || defined(_ODC10)
      0x0400 |
    #endif
    #if defined(_ODCC11) || defined(_ODC11)
      0x0800 |
    #endif
    #if defined(_ODCC12) || defined(_ODC12)
      0x1000 |
    #endif
    #if defined(_ODCC13) || defined(_ODC13)
      0x2000 |
    #endif
    #if defined(_ODCC14) || defined(_ODC14)
      0x4000 |
    #endif
    #if defined(_ODCC15) || defined(_ODC15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 4
    #if defined(_ODCD0)  || defined(_ODD0)
      0x0001 |
    #endif
    #if defined(_ODCD1)  || defined(_ODD1)
      0x0002 |
    #endif
    #if defined(_ODCD2)  || defined(_ODD2)
      0x0004 |
    #endif
    #if defined(_ODCD3)  || defined(_ODD3)
      0x0008 |
    #endif
    #if defined(_ODCD4)  || defined(_ODD4)
      0x0010 |
    #endif
    #if defined(_ODCD5)  || defined(_ODD5)
      0x0020 |
    #endif
    #if defined(_ODCD6)  || defined(_ODD6)
      0x0040 |
    #endif
    #if defined(_ODCD7)  || defined(_ODD7)
      0x0080 |
    #endif
    #if defined(_ODCD8)  || defined(_ODD8)
      0x0100 |
    #endif
    #if defined(_ODCD9)  || defined(_ODD9)
      0x0200 |
    #endif
    #if defined(_ODCD10) || defined(_ODD10)
      0x0400 |
    #endif
    #if defined(_ODCD11) || defined(_ODD11)
      0x0800 |
    #endif
    #if defined(_ODCD12) || defined(_ODD12)
      0x1000 |
    #endif
    #if defined(_ODCD13) || defined(_ODD13)
      0x2000 |
    #endif
    #if defined(_ODCD14) || defined(_ODD14)
      0x4000 |
    #endif
    #if defined(_ODCD15) || defined(_ODD15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 5
    #if defined(_ODCE0)  || defined(_ODE0)
      0x0001 |
    #endif
    #if defined(_ODCE1)  || defined(_ODE1)
      0x0002 |
    #endif
    #if defined(_ODCE2)  || defined(_ODE2)
      0x0004 |
    #endif
    #if defined(_ODCE3)  || defined(_ODE3)
      0x0008 |
    #endif
    #if defined(_ODCE4)  || defined(_ODE4)
      0x0010 |
    #endif
    #if defined(_ODCE5)  || defined(_ODE5)
      0x0020 |
    #endif
    #if defined(_ODCE6)  || defined(_ODE6)
      0x0040 |
    #endif
    #if defined(_ODCE7)  || defined(_ODE7)
      0x0080 |
    #endif
    #if defined(_ODCE8)  || defined(_ODE8)
      0x0100 |
    #endif
    #if defined(_ODCE9)  || defined(_ODE9)
      0x0200 |
    #endif
    #if defined(_ODCE10) || defined(_ODE10)
      0x0400 |
    #endif
    #if defined(_ODCE11) || defined(_ODE11)
      0x0800 |
    #endif
    #if defined(_ODCE12) || defined(_ODE12)
      0x1000 |
    #endif
    #if defined(_ODCE13) || defined(_ODE13)
      0x2000 |
    #endif
    #if defined(_ODCE14) || defined(_ODE14)
      0x4000 |
    #endif
    #if defined(_ODCE15) || defined(_ODE15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 6
    #if defined(_ODCF0)  || defined(_ODF0)
      0x0001 |
    #endif
    #if defined(_ODCF1)  || defined(_ODF1)
      0x0002 |
    #endif
    #if defined(_ODCF2)  || defined(_ODF2)
      0x0004 |
    #endif
    #if defined(_ODCF3)  || defined(_ODF3)
      0x0008 |
    #endif
    #if defined(_ODCF4)  || defined(_ODF4)
      0x0010 |
    #endif
    #if defined(_ODCF5)  || defined(_ODF5)
      0x0020 |
    #endif
    #if defined(_ODCF6)  || defined(_ODF6)
      0x0040 |
    #endif
    #if defined(_ODCF7)  || defined(_ODF7)
      0x0080 |
    #endif
    #if defined(_ODCF8)  || defined(_ODF8)
      0x0100 |
    #endif
    #if defined(_ODCF9)  || defined(_ODF9)
      0x0200 |
    #endif
    #if defined(_ODCF10) || defined(_ODF10)
      0x0400 |
    #endif
    #if defined(_ODCF11) || defined(_ODF11)
      0x0800 |
    #endif
    #if defined(_ODCF12) || defined(_ODF12)
      0x1000 |
    #endif
    #if defined(_ODCF13) || defined(_ODF13)
      0x2000 |
    #endif
    #if defined(_ODCF14) || defined(_ODF14)
      0x4000 |
    #endif
    #if defined(_ODCF15) || defined(_ODF15)
      0x8000 |
    #endif
    0x0000,
  #endif 

  #if NUM_DIGITAL_PORTS >= 7
    #if defined(_ODCG0)  || defined(_ODG0)
      0x0001 |
    #endif
    #if defined(_ODCG1)  || defined(_ODG1)
      0x0002 |
    #endif
    #if defined(_ODCG2)  || defined(_ODG2)
      0x0004 |
    #endif
    #if defined(_ODCG3)  || defined(_ODG3)
      0x0008 |
    #endif
    #if defined(_ODCG4)  || defined(_ODG4)
      0x0010 |
    #endif
    #if defined(_ODCG5)  || defined(_ODG5)
      0x0020 |
    #endif
    #if defined(_ODCG6)  || defined(_ODG6)
      0x0040 |
    #endif
    #if defined(_ODCG7)  || defined(_ODG7)
      0x0080 |
    #endif
    #if defined(_ODCG8)  || defined(_ODG8)
      0x0100 |
    #endif
    #if defined(_ODCG9)  || defined(_ODG9)
      0x0200 |
    #endif
    #if defined(_ODCG10) || defined(_ODG10)
      0x0400 |
    #endif
    #if defined(_ODCG11) || defined(_ODG11)
      0x0800 |
    #endif
    #if defined(_ODCG12) || defined(_ODG12)
      0x1000 |
    #endif
    #if defined(_ODCG13) || defined(_ODG13)
      0x2000 |
    #endif
    #if defined(_ODCG14) || defined(_ODG14)
      0x4000 |
    #endif
    #if defined(_ODCG15) || defined(_ODG15)
      0x8000 |
    #endif
    0x0000,
  #endif 
 };







// Include appropriate ports file for the device in use.
// These definitions are then used below to map digital I/O ports to the
// corresponding analog and change notification pin
#if defined(__PIC24HJ128GP202__)

#include "devices/pic24hj128gp202_pyports.h"

#elif defined(__PIC24HJ128GP204__)

#include "devices/pic24hj128gp204_pyports.h"

#elif defined(__PIC24HJ128GP206__)

#include "devices/pic24hj128gp206_pyports.h"

#elif defined(__PIC24HJ128GP210__)

#include "devices/pic24hj128gp210_pyports.h"

#elif defined(__PIC24HJ128GP306__)

#include "devices/pic24hj128gp306_pyports.h"

#elif defined(__PIC24HJ128GP310__)

#include "devices/pic24hj128gp310_pyports.h"

#elif defined(__PIC24HJ128GP502__)

#include "devices/pic24hj128gp502_pyports.h"

#elif defined(__PIC24HJ128GP504__)

#include "devices/pic24hj128gp504_pyports.h"

#elif defined(__PIC24HJ128GP506__)

#include "devices/pic24hj128gp506_pyports.h"

#elif defined(__PIC24HJ128GP510__)

#include "devices/pic24hj128gp510_pyports.h"

#elif defined(__PIC24HJ12GP201__)

#include "devices/pic24hj12gp201_pyports.h"

#elif defined(__PIC24HJ12GP202__)

#include "devices/pic24hj12gp202_pyports.h"

#elif defined(__PIC24HJ16GP304__)

#include "devices/pic24hj16gp304_pyports.h"

#elif defined(__PIC24HJ256GP206__)

#include "devices/pic24hj256gp206_pyports.h"

#elif defined(__PIC24HJ256GP210__)

#include "devices/pic24hj256gp210_pyports.h"

#elif defined(__PIC24HJ256GP610__)

#include "devices/pic24hj256gp610_pyports.h"

#elif defined(__PIC24HJ32GP202__)

#include "devices/pic24hj32gp202_pyports.h"

#elif defined(__PIC24HJ32GP204__)

#include "devices/pic24hj32gp204_pyports.h"

#elif defined(__PIC24HJ32GP302__)

#include "devices/pic24hj32gp302_pyports.h"

#elif defined(__PIC24HJ32GP304__)

#include "devices/pic24hj32gp304_pyports.h"

#elif defined(__PIC24HJ64GP202__)

#include "devices/pic24hj64gp202_pyports.h"

#elif defined(__PIC24HJ64GP204__)

#include "devices/pic24hj64gp204_pyports.h"

#elif defined(__PIC24HJ64GP206__)

#include "devices/pic24hj64gp206_pyports.h"

#elif defined(__PIC24HJ64GP210__)

#include "devices/pic24hj64gp210_pyports.h"

#elif defined(__PIC24HJ64GP502__)

#include "devices/pic24hj64gp502_pyports.h"

#elif defined(__PIC24HJ64GP504__)

#include "devices/pic24hj64gp504_pyports.h"

#elif defined(__PIC24HJ64GP506__)

#include "devices/pic24hj64gp506_pyports.h"

#elif defined(__PIC24HJ64GP510__)

#include "devices/pic24hj64gp510_pyports.h"

#elif defined(__PIC24F04KA200__)

#include "devices/pic24f04ka200_pyports.h"

#elif defined(__PIC24F04KA201__)

#include "devices/pic24f04ka201_pyports.h"

#elif defined(__PIC24F08KA101__)

#include "devices/pic24f08ka101_pyports.h"

#elif defined(__PIC24F08KA102__)

#include "devices/pic24f08ka102_pyports.h"

#elif defined(__PIC24F16KA101__)

#include "devices/pic24f16ka101_pyports.h"

#elif defined(__PIC24F16KA102__)

#include "devices/pic24f16ka102_pyports.h"

#elif defined(__PIC24F32KA101__)

#include "devices/pic24f32ka101_pyports.h"

#elif defined(__PIC24F32KA102__)

#include "devices/pic24f32ka102_pyports.h"

#elif defined(__PIC24FJ128GA006__)

#include "devices/pic24fj128ga006_pyports.h"

#elif defined(__PIC24FJ128GA008__)

#include "devices/pic24fj128ga008_pyports.h"

#elif defined(__PIC24FJ128GA010__)

#include "devices/pic24fj128ga010_pyports.h"

#elif defined(__PIC24FJ128GA106__)

#include "devices/pic24fj128ga106_pyports.h"

#elif defined(__PIC24FJ128GA108__)

#include "devices/pic24fj128ga108_pyports.h"

#elif defined(__PIC24FJ128GA110__)

#include "devices/pic24fj128ga110_pyports.h"

#elif defined(__PIC24FJ128GB106__)

#include "devices/pic24fj128gb106_pyports.h"

#elif defined(__PIC24FJ128GB108__)

#include "devices/pic24fj128gb108_pyports.h"

#elif defined(__PIC24FJ128GB110__)

#include "devices/pic24fj128gb110_pyports.h"

#elif defined(__PIC24FJ16GA002__)

#include "devices/pic24fj16ga002_pyports.h"

#elif defined(__PIC24FJ16GA004__)

#include "devices/pic24fj16ga004_pyports.h"

#elif defined(__PIC24FJ192GA106__)

#include "devices/pic24fj192ga106_pyports.h"

#elif defined(__PIC24FJ192GA108__)

#include "devices/pic24fj192ga108_pyports.h"

#elif defined(__PIC24FJ192GA110__)

#include "devices/pic24fj192ga110_pyports.h"

#elif defined(__PIC24FJ192GB106__)

#include "devices/pic24fj192gb106_pyports.h"

#elif defined(__PIC24FJ192GB108__)

#include "devices/pic24fj192gb108_pyports.h"

#elif defined(__PIC24FJ192GB110__)

#include "devices/pic24fj192gb110_pyports.h"

#elif defined(__PIC24FJ256GA106__)

#include "devices/pic24fj256ga106_pyports.h"

#elif defined(__PIC24FJ256GA108__)

#include "devices/pic24fj256ga108_pyports.h"

#elif defined(__PIC24FJ256GA110__)

#include "devices/pic24fj256ga110_pyports.h"

#elif defined(__PIC24FJ256GB106__)

#include "devices/pic24fj256gb106_pyports.h"

#elif defined(__PIC24FJ256GB108__)

#include "devices/pic24fj256gb108_pyports.h"

#elif defined(__PIC24FJ256GB110__)

#include "devices/pic24fj256gb110_pyports.h"

#elif defined(__PIC24FJ32GA002__)

#include "devices/pic24fj32ga002_pyports.h"

#elif defined(__PIC24FJ32GA004__)

#include "devices/pic24fj32ga004_pyports.h"

#elif defined(__PIC24FJ48GA002__)

#include "devices/pic24fj48ga002_pyports.h"

#elif defined(__PIC24FJ48GA004__)

#include "devices/pic24fj48ga004_pyports.h"

#elif defined(__PIC24FJ64GA002__)

#include "devices/pic24fj64ga002_pyports.h"

#elif defined(__PIC24FJ64GA004__)

#include "devices/pic24fj64ga004_pyports.h"

#elif defined(__PIC24FJ64GA006__)

#include "devices/pic24fj64ga006_pyports.h"

#elif defined(__PIC24FJ64GA008__)

#include "devices/pic24fj64ga008_pyports.h"

#elif defined(__PIC24FJ64GA010__)

#include "devices/pic24fj64ga010_pyports.h"

#elif defined(__PIC24FJ64GA106__)

#include "devices/pic24fj64ga106_pyports.h"

#elif defined(__PIC24FJ64GA108__)

#include "devices/pic24fj64ga108_pyports.h"

#elif defined(__PIC24FJ64GA110__)

#include "devices/pic24fj64ga110_pyports.h"

#elif defined(__PIC24FJ64GB106__)

#include "devices/pic24fj64gb106_pyports.h"

#elif defined(__PIC24FJ64GB108__)

#include "devices/pic24fj64gb108_pyports.h"

#elif defined(__PIC24FJ64GB110__)

#include "devices/pic24fj64gb110_pyports.h"

#elif defined(__PIC24FJ96GA006__)

#include "devices/pic24fj96ga006_pyports.h"

#elif defined(__PIC24FJ96GA008__)

#include "devices/pic24fj96ga008_pyports.h"

#elif defined(__PIC24FJ96GA010__)

#include "devices/pic24fj96ga010_pyports.h"

#elif defined(__dsPIC33FJ06GS101__)

#include "devices/dspic33fj06gs101_pyports.h"

#elif defined(__dsPIC33FJ06GS102__)

#include "devices/dspic33fj06gs102_pyports.h"

#elif defined(__dsPIC33FJ06GS202__)

#include "devices/dspic33fj06gs202_pyports.h"

#elif defined(__dsPIC33FJ128GP202__)

#include "devices/dspic33fj128gp202_pyports.h"

#elif defined(__dsPIC33FJ128GP204__)

#include "devices/dspic33fj128gp204_pyports.h"

#elif defined(__dsPIC33FJ128GP206A__)

#include "devices/dspic33fj128gp206a_pyports.h"

#elif defined(__dsPIC33FJ128GP206__)

#include "devices/dspic33fj128gp206_pyports.h"

#elif defined(__dsPIC33FJ128GP306A__)

#include "devices/dspic33fj128gp306a_pyports.h"

#elif defined(__dsPIC33FJ128GP306__)

#include "devices/dspic33fj128gp306_pyports.h"

#elif defined(__dsPIC33FJ128GP310A__)

#include "devices/dspic33fj128gp310a_pyports.h"

#elif defined(__dsPIC33FJ128GP310__)

#include "devices/dspic33fj128gp310_pyports.h"

#elif defined(__dsPIC33FJ128GP706A__)

#include "devices/dspic33fj128gp706a_pyports.h"

#elif defined(__dsPIC33FJ128GP706__)

#include "devices/dspic33fj128gp706_pyports.h"

#elif defined(__dsPIC33FJ128GP708A__)

#include "devices/dspic33fj128gp708a_pyports.h"

#elif defined(__dsPIC33FJ128GP708__)

#include "devices/dspic33fj128gp708_pyports.h"

#elif defined(__dsPIC33FJ128GP710A__)

#include "devices/dspic33fj128gp710a_pyports.h"

#elif defined(__dsPIC33FJ128GP710__)

#include "devices/dspic33fj128gp710_pyports.h"

#elif defined(__dsPIC33FJ128GP802__)

#include "devices/dspic33fj128gp802_pyports.h"

#elif defined(__dsPIC33FJ128GP804__)

#include "devices/dspic33fj128gp804_pyports.h"

#elif defined(__dsPIC33FJ128MC202__)

#include "devices/dspic33fj128mc202_pyports.h"

#elif defined(__dsPIC33FJ128MC204__)

#include "devices/dspic33fj128mc204_pyports.h"

#elif defined(__dsPIC33FJ128MC506A__)

#include "devices/dspic33fj128mc506a_pyports.h"

#elif defined(__dsPIC33FJ128MC506__)

#include "devices/dspic33fj128mc506_pyports.h"

#elif defined(__dsPIC33FJ128MC510A__)

#include "devices/dspic33fj128mc510a_pyports.h"

#elif defined(__dsPIC33FJ128MC510__)

#include "devices/dspic33fj128mc510_pyports.h"

#elif defined(__dsPIC33FJ128MC706A__)

#include "devices/dspic33fj128mc706a_pyports.h"

#elif defined(__dsPIC33FJ128MC706__)

#include "devices/dspic33fj128mc706_pyports.h"

#elif defined(__dsPIC33FJ128MC708A__)

#include "devices/dspic33fj128mc708a_pyports.h"

#elif defined(__dsPIC33FJ128MC708__)

#include "devices/dspic33fj128mc708_pyports.h"

#elif defined(__dsPIC33FJ128MC710A__)

#include "devices/dspic33fj128mc710a_pyports.h"

#elif defined(__dsPIC33FJ128MC710__)

#include "devices/dspic33fj128mc710_pyports.h"

#elif defined(__dsPIC33FJ128MC802__)

#include "devices/dspic33fj128mc802_pyports.h"

#elif defined(__dsPIC33FJ128MC804__)

#include "devices/dspic33fj128mc804_pyports.h"

#elif defined(__dsPIC33FJ12GP201__)

#include "devices/dspic33fj12gp201_pyports.h"

#elif defined(__dsPIC33FJ12GP202__)

#include "devices/dspic33fj12gp202_pyports.h"

#elif defined(__dsPIC33FJ12MC201__)

#include "devices/dspic33fj12mc201_pyports.h"

#elif defined(__dsPIC33FJ12MC202__)

#include "devices/dspic33fj12mc202_pyports.h"

#elif defined(__dsPIC33FJ16GP304__)

#include "devices/dspic33fj16gp304_pyports.h"

#elif defined(__dsPIC33FJ16GS402__)

#include "devices/dspic33fj16gs402_pyports.h"

#elif defined(__dsPIC33FJ16GS404__)

#include "devices/dspic33fj16gs404_pyports.h"

#elif defined(__dsPIC33FJ16GS502__)

#include "devices/dspic33fj16gs502_pyports.h"

#elif defined(__dsPIC33FJ16GS504__)

#include "devices/dspic33fj16gs504_pyports.h"

#elif defined(__dsPIC33FJ16MC304__)

#include "devices/dspic33fj16mc304_pyports.h"

#elif defined(__dsPIC33FJ256GP506A__)

#include "devices/dspic33fj256gp506a_pyports.h"

#elif defined(__dsPIC33FJ256GP506__)

#include "devices/dspic33fj256gp506_pyports.h"

#elif defined(__dsPIC33FJ256GP510A__)

#include "devices/dspic33fj256gp510a_pyports.h"

#elif defined(__dsPIC33FJ256GP510__)

#include "devices/dspic33fj256gp510_pyports.h"

#elif defined(__dsPIC33FJ256GP710A__)

#include "devices/dspic33fj256gp710a_pyports.h"

#elif defined(__dsPIC33FJ256GP710__)

#include "devices/dspic33fj256gp710_pyports.h"

#elif defined(__dsPIC33FJ256MC510A__)

#include "devices/dspic33fj256mc510a_pyports.h"

#elif defined(__dsPIC33FJ256MC510__)

#include "devices/dspic33fj256mc510_pyports.h"

#elif defined(__dsPIC33FJ256MC710A__)

#include "devices/dspic33fj256mc710a_pyports.h"

#elif defined(__dsPIC33FJ256MC710__)

#include "devices/dspic33fj256mc710_pyports.h"

#elif defined(__dsPIC33FJ32GP202__)

#include "devices/dspic33fj32gp202_pyports.h"

#elif defined(__dsPIC33FJ32GP204__)

#include "devices/dspic33fj32gp204_pyports.h"

#elif defined(__dsPIC33FJ32GP302__)

#include "devices/dspic33fj32gp302_pyports.h"

#elif defined(__dsPIC33FJ32GP304__)

#include "devices/dspic33fj32gp304_pyports.h"

#elif defined(__dsPIC33FJ32GS406__)

#include "devices/dspic33fj32gs406_pyports.h"

#elif defined(__dsPIC33FJ32GS606__)

#include "devices/dspic33fj32gs606_pyports.h"

#elif defined(__dsPIC33FJ32GS608__)

#include "devices/dspic33fj32gs608_pyports.h"

#elif defined(__dsPIC33FJ32GS610__)

#include "devices/dspic33fj32gs610_pyports.h"

#elif defined(__dsPIC33FJ32MC202__)

#include "devices/dspic33fj32mc202_pyports.h"

#elif defined(__dsPIC33FJ32MC204__)

#include "devices/dspic33fj32mc204_pyports.h"

#elif defined(__dsPIC33FJ32MC302__)

#include "devices/dspic33fj32mc302_pyports.h"

#elif defined(__dsPIC33FJ32MC304__)

#include "devices/dspic33fj32mc304_pyports.h"

#elif defined(__dsPIC33FJ64GP202__)

#include "devices/dspic33fj64gp202_pyports.h"

#elif defined(__dsPIC33FJ64GP204__)

#include "devices/dspic33fj64gp204_pyports.h"

#elif defined(__dsPIC33FJ64GP206A__)

#include "devices/dspic33fj64gp206a_pyports.h"

#elif defined(__dsPIC33FJ64GP206__)

#include "devices/dspic33fj64gp206_pyports.h"

#elif defined(__dsPIC33FJ64GP306A__)

#include "devices/dspic33fj64gp306a_pyports.h"

#elif defined(__dsPIC33FJ64GP306__)

#include "devices/dspic33fj64gp306_pyports.h"

#elif defined(__dsPIC33FJ64GP310A__)

#include "devices/dspic33fj64gp310a_pyports.h"

#elif defined(__dsPIC33FJ64GP310__)

#include "devices/dspic33fj64gp310_pyports.h"

#elif defined(__dsPIC33FJ64GP706A__)

#include "devices/dspic33fj64gp706a_pyports.h"

#elif defined(__dsPIC33FJ64GP706__)

#include "devices/dspic33fj64gp706_pyports.h"

#elif defined(__dsPIC33FJ64GP708A__)

#include "devices/dspic33fj64gp708a_pyports.h"

#elif defined(__dsPIC33FJ64GP708__)

#include "devices/dspic33fj64gp708_pyports.h"

#elif defined(__dsPIC33FJ64GP710A__)

#include "devices/dspic33fj64gp710a_pyports.h"

#elif defined(__dsPIC33FJ64GP710__)

#include "devices/dspic33fj64gp710_pyports.h"

#elif defined(__dsPIC33FJ64GP802__)

#include "devices/dspic33fj64gp802_pyports.h"

#elif defined(__dsPIC33FJ64GP804__)

#include "devices/dspic33fj64gp804_pyports.h"

#elif defined(__dsPIC33FJ64GS406__)

#include "devices/dspic33fj64gs406_pyports.h"

#elif defined(__dsPIC33FJ64GS606__)

#include "devices/dspic33fj64gs606_pyports.h"

#elif defined(__dsPIC33FJ64GS608__)

#include "devices/dspic33fj64gs608_pyports.h"

#elif defined(__dsPIC33FJ64GS610__)

#include "devices/dspic33fj64gs610_pyports.h"

#elif defined(__dsPIC33FJ64MC202__)

#include "devices/dspic33fj64mc202_pyports.h"

#elif defined(__dsPIC33FJ64MC204__)

#include "devices/dspic33fj64mc204_pyports.h"

#elif defined(__dsPIC33FJ64MC506A__)

#include "devices/dspic33fj64mc506a_pyports.h"

#elif defined(__dsPIC33FJ64MC506__)

#include "devices/dspic33fj64mc506_pyports.h"

#elif defined(__dsPIC33FJ64MC508A__)

#include "devices/dspic33fj64mc508a_pyports.h"

#elif defined(__dsPIC33FJ64MC508__)

#include "devices/dspic33fj64mc508_pyports.h"

#elif defined(__dsPIC33FJ64MC510A__)

#include "devices/dspic33fj64mc510a_pyports.h"

#elif defined(__dsPIC33FJ64MC510__)

#include "devices/dspic33fj64mc510_pyports.h"

#elif defined(__dsPIC33FJ64MC706A__)

#include "devices/dspic33fj64mc706a_pyports.h"

#elif defined(__dsPIC33FJ64MC706__)

#include "devices/dspic33fj64mc706_pyports.h"

#elif defined(__dsPIC33FJ64MC710A__)

#include "devices/dspic33fj64mc710a_pyports.h"

#elif defined(__dsPIC33FJ64MC710__)

#include "devices/dspic33fj64mc710_pyports.h"

#elif defined(__dsPIC33FJ64MC802__)

#include "devices/dspic33fj64mc802_pyports.h"

#elif defined(__dsPIC33FJ64MC804__)

#include "devices/dspic33fj64mc804_pyports.h"

#else

#error -- processor ID not specified in pic24_pyports.h

#endif


#ifndef _PIC24_PYDIGIO_DEFINED
#warning Digital IO macros not defined for this device!
#warning Edit common\pic24_pyports.h file!
#endif








/** The values state that a given digital I/O pin does not 
 *  have analog capability. It is used in \ref anCnMap.
 */
#define UNDEF_AN_PIN 255

/** The values state that a given digital I/O pin does not 
 *  have change notification capability. It is used in \ref anCnMap.
 */
#define UNDEF_CN_PIN 255

/** Define a structure which contains a mapping from
 *  a digital I/O port/pin to an analog pin and to
 *  a change notification pin.
 */
typedef struct {
  /// The analog pin (ANxx) corresponding to a given digital port/pin,
  /// or \ref UNDEF_AN_PIN if the pin has no analog capability.
  uint8_t u8_anPin;
  /// The analog pin (ANxx) corresponding to a given digital port/pin,
  /// or \ref UNDEF_CN_PIN if the pin has no change notification capability.
  uint8_t u8_cnPin;
} anCnMap_t;

// The AN_CN_MAP macro specifies the mapping. It is defined in
// the device/<devicename>_pyports.h file.
/** An array of the \ref anCnMap_t structure with an entry for each of
 *  the (up to) 16 pins on each digitial I/O port for this device.
 */
static const anCnMap_t anCnMap[NUM_DIGITAL_PORTS * 16] = { AN_CN_MAP };

#if defined(HAS_REMAPPABLE_PINS) || defined(__DOXYGEN__)
/** This bitfield indicates which remappable pins exist on this device.
 *  Each bit is true if the corresponding remappable pin exists.
 *  In particular, bit 0 = RP0, bit 1 = RP1, etc.
 */
static const uint32_t u32_isRemappable = {
#ifdef _RP0R
    0x00000001 |
#endif
#ifdef _RP1R
    0x00000002 |
#endif
#ifdef _RP2R
    0x00000004 |
#endif
#ifdef _RP3R
    0x00000008 |
#endif
#ifdef _RP4R
    0x00000010 |
#endif
#ifdef _RP5R
    0x00000020 |
#endif
#ifdef _RP6R
    0x00000040 |
#endif
#ifdef _RP7R
    0x00000080 |
#endif
#ifdef _RP8R
    0x00000100 |
#endif
#ifdef _RP9R
    0x00000200 |
#endif
#ifdef _RP10R
    0x00000400 |
#endif
#ifdef _RP11R
    0x00000800 |
#endif
#ifdef _RP12R
    0x00001000 |
#endif
#ifdef _RP13R
    0x00002000 |
#endif
#ifdef _RP14R
    0x00004000 |
#endif
#ifdef _RP15R
    0x00008000 |
#endif
#ifdef _RP16R
    0x00010000 |
#endif
#ifdef _RP17R
    0x00020000 |
#endif
#ifdef _RP18R
    0x00040000 |
#endif
#ifdef _RP19R
    0x00080000 |
#endif
#ifdef _RP20R
    0x00100000 |
#endif
#ifdef _RP21R
    0x00200000 |
#endif
#ifdef _RP22R
    0x00400000 |
#endif
#ifdef _RP23R
    0x00800000 |
#endif
#ifdef _RP24R
    0x01000000 |
#endif
#ifdef _RP25R
    0x02000000 |
#endif
#ifdef _RP26R
    0x04000000 |
#endif
#ifdef _RP27R
    0x08000000 |
#endif
#ifdef _RP28R
    0x10000000 |
#endif
#ifdef _RP29R
    0x20000000 |
#endif
#ifdef _RP30R
    0x40000000 |
#endif
// Note: RP31R can't exist, since this value is reserved
// for assigning an input to Vss.
    0x00000000 
};
#endif





/** Make sure the given pin is within bounds.
 *  @param u16_port Port, where 0 = A, 1 = B, etc.
 *  @param u16_pin  Pin of the given port; from 0 to 15.
 *  @return Returns C_FALSE if the port exceeds \ref NUM_DIGITAL_PORTS
 *          or if the pin > 15. Returns C_TRUE otherwise.
 */
inline __STATIC__ bool_t digitalPinInBounds(uint16_t u16_port, uint16_t u16_pin)
{
    // Check for an out-of-range port
    if (u16_port >= NUM_DIGITAL_PORTS)
        return C_FALSE;
    // Check for an out-of-range pin
    if (u16_pin > 15)
        return C_FALSE;
    else
        return C_TRUE;
}

bool_t 
digitalPinExists(uint16_t u16_port, uint16_t u16_pin)
{
    // Check for an out-of-range port
    if (!digitalPinInBounds(u16_port, u16_pin))
        return C_FALSE;
    // Check the map of pins.
    return getBit(u16_digitalPinPresent[u16_port], u16_pin);
}


/** Determine if the given digitial I/O open-drain pin exists.
 *  @param u16_port Port, where 0 = A, 1 = B, etc.
 *  @param u16_pin  Pin of the given port; from 0 to 15.
 *  @return Returns C_TRUE if the pin open-drain exists, C_FALSE otherwise.
 *          Nonexistant ports or pins simply return C_FALSE.
 */
__STATIC__ bool_t
digitalOpenDrainPinExists(uint16_t u16_port, uint16_t u16_pin)
{
    // Check for an out-of-range port
    if (!digitalPinInBounds(u16_port, u16_pin))
        return C_FALSE;
    // Check the map of pins.
    return getBit(u16_digitalPinOpenDrainPresent[u16_port], u16_pin);
}


/** This values gives the number of words between I/O port control registers.
 *  For example, &TRISA = 0x02C0 and &TRISB = 0x2C8, a difference of
 *  four words. 
 */
// Note: I can't make this a const, since only the linker knows these values.
// E.g. the statement below produces a compile error:
// static const u16_ioPortControlOffset = (uint16_t) (&TRISB - &TRISA);
#define IO_PORT_CONTROL_OFFSET 4

PmReturn_t
setPinIsInput(uint16_t u16_port, uint16_t u16_pin, bool_t b_isInput)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    // Select input or output for the pin
    setBit((&TRISA) + u16_port*IO_PORT_CONTROL_OFFSET, u16_pin, b_isInput);
    return retval;
}


PmReturn_t
getPinIsInput(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isInput)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    // Determine if pin is an input or an output
    *pb_isInput = getBit(*((&TRISA) + u16_port*IO_PORT_CONTROL_OFFSET), u16_pin);
    return retval;
}


PmReturn_t
setPinIsDigital(uint16_t u16_port, uint16_t u16_pin, 
  bool_t b_isDigital)
{
    PmReturn_t retval = PM_RET_OK;
    uint8_t u8_anPin;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);

    // There are four possibilities for digital configuration:
    //                      | set as analog   | set as digital
    // ---------------------+-----------------+-----------------------------------------
    // has analog           | clear PCFG bit  | set PCFG bit
    // does not have analog | throw exception | do nothing (already digital)
    u8_anPin = anCnMap[u16_port*16 + u16_pin].u8_anPin;
    if (u8_anPin != UNDEF_AN_PIN) {
        // Enable/disable analog input mode on this pin.
        // Each ADC handles 32 channels; some PIC24F / dsPIC33 parts have
        // two converters. If so, need to clear the corresponding bit on both.
        SET_EXTENDED_BIT(&AD1PCFGL, u8_anPin, b_isDigital);
#ifdef _AD2IF
        SET_EXTENDED_BIT(&AD2PCFGL, u8_anPin, b_isDigital);
#endif
    } else {
        // If analog is enabled on a pin without analog ability,
        // report an error. Otherwise, do nothing -- digital
        // is the default for a pin without analog ability.
        EXCEPTION_UNLESS(b_isDigital, PM_RET_EX_VAL,
          "Pin %c%d does not support analog functionality.", 
          (char) (u16_port + 'A'), u16_pin);
    }

    return retval;
}


PmReturn_t
setPinIsOpenDrain(uint16_t u16_port, uint16_t u16_pin, bool_t b_isOpenDrain)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    // There are four possibilities for open-drain configuration:
    //                          | set as open-drain  | set as normal (push/pull aka totem-pole)
    // -------------------------+--------------------+-----------------------------------------
    // has open-drain           | set OD bit         | clear OD bit
    // does not have open-drain | throw exception    | do nothing (already normal)
    if (digitalOpenDrainPinExists(u16_port, u16_pin)) {
        // Set the pin per the OD boolean.
        // PIC24F names this differently, so define around it.
        #if defined (_ODA0)  || defined (_ODA1)  || defined (_ODA2)  || defined (_ODA3)  || \
            defined (_ODA4)  || defined (_ODA5)  || defined (_ODA6)  || defined (_ODA7)  || \
            defined (_ODA8)  || defined (_ODA9)  || defined (_ODA10) || defined (_ODA11) || \
            defined (_ODA12) || defined (_ODA12) || defined (_ODA14) || defined (_ODA15)
        #define ODCA ODA
        #endif
        setBit((&ODCA) + u16_port*IO_PORT_CONTROL_OFFSET, u16_pin, b_isOpenDrain);
    } else {
        // If open-drain is enabled on a pin without OD ability,
        // report an error. Otherwise, do nothing -- open-drain
        // is already disabled for a pin without OD ability.
        EXCEPTION_UNLESS(!b_isOpenDrain, PM_RET_EX_VAL,
          "The pin %c%d has no open-drain ability.", (char) (u16_port + 'A'), u16_pin);
    }

    return retval;
}

PmReturn_t
setPinPullDirection(uint16_t u16_port, uint16_t u16_pin, 
  int16_t i16_dir)
{
    PmReturn_t retval = PM_RET_OK;
    uint8_t u8_cnPin;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);

    // Detetrmine which (if any) CN bit exists on the given pin
    u8_cnPin = anCnMap[u16_port*16 + u16_pin].u8_cnPin;

    // For no pull, disable pull-ups and pull-downs if they exist
    if (i16_dir == 0) {
        if (u8_cnPin != UNDEF_CN_PIN) {
            SET_EXTENDED_BIT(&CNPU1, u8_cnPin, C_FALSE);
            #ifdef HAS_PULL_DOWNS
                SET_EXTENDED_BIT(&CNPD1, u8_cnPin, C_FALSE);
            #endif
        }
    // For pull-ups, disable pull-downs if they exist. Throw
    // an exception if pull-ups don't exist
    } else if (i16_dir > 0) {
        EXCEPTION_UNLESS(u8_cnPin != UNDEF_CN_PIN, PM_RET_EX_VAL,
          "Pull-ups do not exist on %c%d.", 
          (char) (u16_port + 'A'), u16_pin);
        SET_EXTENDED_BIT(&CNPU1, u8_cnPin, C_TRUE);
        #ifdef HAS_PULL_DOWNS
            SET_EXTENDED_BIT(&CNPD1, u8_cnPin, C_FALSE);
        #endif
    // For pull-downs, disable pull-ups. Throw an exception
    // if either don't exist.
    } else {
        ASSERT(i16_dir < 0);

        // Verify pull-downs exist then enable them
        #ifdef HAS_PULL_DOWNS
            SET_EXTENDED_BIT(&CNPD1, u8_cnPin, C_TRUE);
        #else
            EXCEPTION_UNLESS(0, PM_RET_EX_VAL,
              "Pull-downs do not exist on this chip.");
        #endif

        // Verify pull-ups exist then disable them
        EXCEPTION_UNLESS(u8_cnPin != UNDEF_CN_PIN, PM_RET_EX_VAL,
          "Pull-ups do not exist on %c%d.", 
          (char) (u16_port + 'A'), u16_pin);
        SET_EXTENDED_BIT(&CNPU1, u8_cnPin, C_FALSE);
    }

    return retval;
}

#ifdef HAS_REMAPPABLE_PINS

/** Unmap a specific peripheral input from a given pin. Checks the peripheral
 *  to see if it is mapped to the given pin; if so, that peripheral is
 *  unmapped, freeing the pin.
 *  @param rpinrBitfield A bitfield in one of the RPINRx registers which
 *           maps the input of a peripheral to a pin.
 *  @param rpPin An RPx value, indicating which RP pin should be free of
 *           any mapping after this macro completes.
 */
#define UNMAP_PERIPHERAL_INPUT(rpinrBitfield, rpPin) \
    if (rpinrBitfield == rpPin)                      \
        rpinrBitfield = IN_PIN_PPS_VSS;              \
    else                                             \
        ((void) 0)

/** Unmap a specific peripheral output from a given pin. Assigns the
 *  pin to have no peripheral mapped to it. This create a case in a
 *  switch statement, so it must be placed in a switch statement.
 *  @param rpPin An RPx value, indicating which RP pin should be free of
 *           any mapping after this macro completes.
 */
#define UNMAP_PERIPHERAL_OUTPUT(rpPin)        \
    case rpPin :                              \
        _RP ## rpPin ## R = OUT_FN_PPS_NULL;  \
    break

/// Call \ref unmapPins. See that function for parameters and return
/// values.
#define UNMAP_PIN(u16_port, u16_pin) unmapPin(u16_port, u16_pin)

PmReturn_t
unmapPin(uint16_t u16_port, uint16_t u16_pin)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t u16_rp;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);

    // If this isn't a remappable pin (only ports B and C
    // have remappable pins), we're done.
    if ( (u16_port != PORT_B_INDEX) && (u16_port != PORT_C_INDEX) )
        return retval;

    // Convert from port/pin to an RP number.
    // RP0-15 = RB0-15, RP16-31 = RB0-15
    u16_rp = (u16_port - PORT_B_INDEX)*16 + u16_pin;

    // See if this pin can be remapped. If not, we're done.
    if (!GET_EXTENDED_BIT(u32_isRemappable, u16_rp))
        return retval;

    // For each remappable peripheral that takes full control
    // of an I/O pin, check to see if a given pin is mapped to
    // it. If so, unmap that peripheral.

    // Unmap UART1 inputs
#ifdef _U1CTSR
    UNMAP_PERIPHERAL_INPUT(_U1CTSR, u16_rp);
#endif
#ifdef _U1RXR
    UNMAP_PERIPHERAL_INPUT(_U1RXR, u16_rp);
#endif

    // Unmap UART2 inputs
#ifdef _U2CTSR
    UNMAP_PERIPHERAL_INPUT(_U2CTSR, u16_rp);
#endif
#ifdef _U2RXR
    UNMAP_PERIPHERAL_INPUT(_U2RXR, u16_rp);
#endif

    // Unmap SPI1 inputs
#ifdef _SCK1R
    UNMAP_PERIPHERAL_INPUT(_SCK1R, u16_rp);
#endif
#ifdef _SDI1R
    UNMAP_PERIPHERAL_INPUT(_SDI1R, u16_rp);
#endif
#ifdef _SS1R
    UNMAP_PERIPHERAL_INPUT(_SS1R, u16_rp);
#endif

    // Unmap SPI2 inputs
#ifdef _SCK2R
    UNMAP_PERIPHERAL_INPUT(_SCK2R, u16_rp);
#endif
#ifdef _SDI2R
    UNMAP_PERIPHERAL_INPUT(_SDI2R, u16_rp);
#endif
#ifdef _SS2R
    UNMAP_PERIPHERAL_INPUT(_SS2R, u16_rp);
#endif

    // Unmap ECAN1 inputs
#ifdef _C1RXR
    UNMAP_PERIPHERAL_INPUT(_C1RXR, u16_rp);
#endif

    // Check to see if the pin to be unmapped has any
    // ouputs mapped to it and unmap if so.
    switch (u16_rp) {
#ifdef _RP0R
        UNMAP_PERIPHERAL_OUTPUT(0);
#endif

#ifdef _RP1R
        UNMAP_PERIPHERAL_OUTPUT(1);
#endif

#ifdef _RP2R
        UNMAP_PERIPHERAL_OUTPUT(2);
#endif

#ifdef _RP3R
        UNMAP_PERIPHERAL_OUTPUT(3);
#endif

#ifdef _RP4R
        UNMAP_PERIPHERAL_OUTPUT(4);
#endif

#ifdef _RP5R
        UNMAP_PERIPHERAL_OUTPUT(5);
#endif

#ifdef _RP6R
        UNMAP_PERIPHERAL_OUTPUT(6);
#endif

#ifdef _RP7R
        UNMAP_PERIPHERAL_OUTPUT(7);
#endif

#ifdef _RP8R
        UNMAP_PERIPHERAL_OUTPUT(8);
#endif

#ifdef _RP9R
        UNMAP_PERIPHERAL_OUTPUT(9);
#endif

#ifdef _RP10R
        UNMAP_PERIPHERAL_OUTPUT(10);
#endif

#ifdef _RP11R
        UNMAP_PERIPHERAL_OUTPUT(11);
#endif

#ifdef _RP12R
        UNMAP_PERIPHERAL_OUTPUT(12);
#endif

#ifdef _RP13R
        UNMAP_PERIPHERAL_OUTPUT(13);
#endif

#ifdef _RP14R
        UNMAP_PERIPHERAL_OUTPUT(14);
#endif

#ifdef _RP15R
        UNMAP_PERIPHERAL_OUTPUT(15);
#endif

#ifdef _RP16R
        UNMAP_PERIPHERAL_OUTPUT(16);
#endif

#ifdef _RP17R
        UNMAP_PERIPHERAL_OUTPUT(17);
#endif

#ifdef _RP18R
        UNMAP_PERIPHERAL_OUTPUT(18);
#endif

#ifdef _RP19R
        UNMAP_PERIPHERAL_OUTPUT(19);
#endif

#ifdef _RP20R
        UNMAP_PERIPHERAL_OUTPUT(20);
#endif

#ifdef _RP21R
        UNMAP_PERIPHERAL_OUTPUT(21);
#endif

#ifdef _RP22R
        UNMAP_PERIPHERAL_OUTPUT(22);
#endif

#ifdef _RP23R
        UNMAP_PERIPHERAL_OUTPUT(23);
#endif

#ifdef _RP24R
        UNMAP_PERIPHERAL_OUTPUT(24);
#endif

#ifdef _RP25R
        UNMAP_PERIPHERAL_OUTPUT(25);
#endif

#ifdef _RP26R
        UNMAP_PERIPHERAL_OUTPUT(26);
#endif

#ifdef _RP27R
        UNMAP_PERIPHERAL_OUTPUT(27);
#endif

#ifdef _RP28R
        UNMAP_PERIPHERAL_OUTPUT(28);
#endif

#ifdef _RP29R
        UNMAP_PERIPHERAL_OUTPUT(29);
#endif

#ifdef _RP30R
        UNMAP_PERIPHERAL_OUTPUT(30);
#endif

        default :
            // No pin matches, so nothing to do
        break;
    }

    return retval;
}

#else // !defined(HAS_REMAPPABLE_PINS)
/// Define a "function" for devices without remappable I/O which
/// returns OK -- all pins are automatically unmapped.
#define UNMAP_PIN(u16_port, u16_pin) PM_RET_OK
#endif

PmReturn_t
configDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t b_isInput,
    bool_t b_isOpenDrain, int16_t i16_pullDir)
{
    PmReturn_t retval = PM_RET_OK;

    // Call the low-level functions to configure the port
    PM_CHECK_FUNCTION( setPinIsDigital(u16_port, u16_pin, C_TRUE) );
    PM_CHECK_FUNCTION( setPinIsInput(u16_port, u16_pin, b_isInput) );
    PM_CHECK_FUNCTION( setPinIsOpenDrain(u16_port, u16_pin, b_isOpenDrain) );
    PM_CHECK_FUNCTION( setPinPullDirection(u16_port, u16_pin, i16_pullDir) );
    PM_CHECK_FUNCTION( UNMAP_PIN(u16_port, u16_pin) );

    return retval;
}

PmReturn_t
configAnalogPin(uint16_t u16_analogPin)
{
    PmReturn_t retval = PM_RET_OK;
    uint16_t u16_port;
    uint16_t u16_pin;
    uint16_t u16_ndx;

    // Search for this analog pin in the anCnMap
    for (u16_ndx = 0; u16_ndx < 16*NUM_DIGITAL_PORTS; u16_ndx++)
    {
        if (anCnMap[u16_ndx].u8_anPin == u16_analogPin)
            break;
    }
    EXCEPTION_UNLESS(anCnMap[u16_ndx].u8_anPin == u16_analogPin, PM_RET_EX_VAL,
      "Invalid analog pin %d.", u16_analogPin);
    u16_port = u16_ndx >> 4;
    u16_pin = u16_ndx & 0xF;
            
    // Configure the pine    
    PM_CHECK_FUNCTION( setPinIsDigital(u16_port, u16_pin, C_FALSE) );
    PM_CHECK_FUNCTION( setPinIsInput(u16_port, u16_pin, C_TRUE) );
    PM_CHECK_FUNCTION( setPinPullDirection(u16_port, u16_pin, 0) );
    PM_CHECK_FUNCTION( UNMAP_PIN(u16_port, u16_pin) );

    return retval;
}


PmReturn_t
setDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t b_isHigh)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    setBit((&PORTA) + u16_port*IO_PORT_CONTROL_OFFSET, u16_pin, b_isHigh);

    return retval;
}

PmReturn_t
readDigitalPin(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isHigh)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    *pb_isHigh = getBit(*(&PORTA + u16_port*IO_PORT_CONTROL_OFFSET), u16_pin);

    return retval;
}

PmReturn_t
readDigitalLatch(uint16_t u16_port, uint16_t u16_pin, bool_t* pb_isHigh)
{
    PmReturn_t retval = PM_RET_OK;

    EXCEPTION_UNLESS(digitalPinExists(u16_port, u16_pin), PM_RET_EX_VAL,
      "Invalid pin %c%d.", (char) (u16_port + 'A'), u16_pin);
    *pb_isHigh = getBit(*(&LATA + u16_port*IO_PORT_CONTROL_OFFSET), u16_pin);

    return retval;
}

