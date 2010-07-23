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

#include "pic24_all.h"

// Only include if this UART exists.
#if (NUM_SPI_MODS >= 1)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the SPI module on the PIC24 uC.
 *  \see pic24_spi.h for more details.
 */



//SPI Receive Overflow freezes the SPI module
void checkRxErrorSPI1() {
  if (SPI1STATbits.SPIROV) {
    //clear the error
    SPI1STATbits.SPIROV = 0;
    reportError("SPI1 Receive Overflow\n");
  }
}

/**
 * Writes a value to the SPIx output buffer, and returns the SPIx
 * input value. This function waits until the entire transmission
 * is complete so it can return the new input value. Whether or not
 * 8-bits or 16-bits is sent depends on how the SPIx module is
 * configured.
 * \param u16_c Value to write to SPI TXBUF
 * \return Value read from SPI RXBUF
 */

uint16 ioMasterSPI1(uint16 u16_c) {
  checkRxErrorSPI1();
  _SPI1IF = 0;      //clear interrupt flag since we are about to write new value
  SPI1BUF = u16_c;
  while (!_SPI1IF) { //wait for operation to complete
    doHeartbeat();
  };
  return(SPI1BUF);
}

#endif // #if (NUM_SPI_MODS >= 1)









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

#include "pic24_all.h"

// Only include if this UART exists.
#if (NUM_SPI_MODS >= 2)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  This file contains routines which configure and
 *  use the SPI module on the PIC24 uC.
 *  \see pic24_spi.h for more details.
 */



//SPI Receive Overflow freezes the SPI module
void checkRxErrorSPI2() {
  if (SPI2STATbits.SPIROV) {
    //clear the error
    SPI2STATbits.SPIROV = 0;
    reportError("SPI2 Receive Overflow\n");
  }
}

/**
 * Writes a value to the SPIx output buffer, and returns the SPIx
 * input value. This function waits until the entire transmission
 * is complete so it can return the new input value. Whether or not
 * 8-bits or 16-bits is sent depends on how the SPIx module is
 * configured.
 * \param u16_c Value to write to SPI TXBUF
 * \return Value read from SPI RXBUF
 */

uint16 ioMasterSPI2(uint16 u16_c) {
  checkRxErrorSPI2();
  _SPI2IF = 0;      //clear interrupt flag since we are about to write new value
  SPI2BUF = u16_c;
  while (!_SPI2IF) { //wait for operation to complete
    doHeartbeat();
  };
  return(SPI2BUF);
}

#endif // #if (NUM_SPI_MODS >= 2)









