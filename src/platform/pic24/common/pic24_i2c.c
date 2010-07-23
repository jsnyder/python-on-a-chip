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
#include <stdio.h>   //for NULL definition

// Only include if this UART exists.
#if (NUM_I2C_MODS >= 1)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  I2C support functions. \see pic24_i2c.h for details.
 */


/**
Configure and enable the I2C1 module for operation at \em u16_FkHZ kHZ clock speed.
\param u16_FkHZ specifies clock speed in kHZ
*/
void configI2C1(uint16 u16_FkHZ) {
  uint32 u32_temp;

  u32_temp = (FCY/1000L)/((uint32) u16_FkHZ);
  u32_temp = u32_temp - FCY/10000000L - 1;
  I2C1BRG = u32_temp;
  I2C1CONbits.I2CEN = 1;
}

/**
Operation: Perform an I2C start operation.
*/
void startI2C1(void) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C1 Start";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1; //enable WDT
  I2C1CONbits.SEN = 1;   // initiate start
  // wait until start finished
  while (I2C1CONbits.SEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Perform an I2C repeated start operation.
*/
void rstartI2C1(void) {// repeated start
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C1 RStart";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;  //enable WDT
  I2C1CONbits.RSEN = 1;   // initiate start
  // wait until start finished
  while (I2C1CONbits.RSEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Perform an I2C stop operation.
*/
void stopI2C1(void) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C1 Stop";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;  //enable WDT
  I2C1CONbits.PEN=1;     // initiate stop, PEN=1
  //wait until stop finished
  while (I2C1CONbits.PEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Send one byte (\em u8_val), if NAK is returned use reportError() function to save error and do software reset.
\param u8_val byte to send
*/
void putI2C1(uint8 u8_val) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C1 Put";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;       //enable WDT
  I2C1TRN = u8_val;    // write byte
  while (I2C1STATbits.TRSTAT);   // wait for 8bits+ ack bit to finish
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
  if (I2C1STATbits.ACKSTAT != I2C_ACK) {
    //NAK returned
    reportError("I2CPUT1, NAK returned.");
  }
}

/**
Operation: Send one byte (\em u8_val), return the acknowledgement bit that comes back from the slave. This
function does not error out if a NAK is returned.
\param u8_val byte to send
\return Ack bit value returned from slave.
*/
uint8 putNoAckCheckI2C1(uint8 u8_val) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C1 Put";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;       //enable WDT
  I2C1TRN = u8_val;    // write byte
  while (I2C1STATbits.TRSTAT);   // wait for 8bits+ ack bit to finish
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
  return(I2C1STATbits.ACKSTAT);
}

/**
Operation: Wait for a byte byte on the I2C bus, send \em u8_ack2Send as the acknowledgement bit to send back to the slave.
\param u8_ack2Send ack bit to send back to slave after byte is read
\return byte read from slave
*/
uint8 getI2C1(uint8 u8_ack2Send) {
  uint8 u8_wdtState;
  uint8 u8_inByte;

  sz_lastTimeoutError = "I2C1 Get";
  u8_wdtState = _SWDTEN;              //save WDT state
  _SWDTEN = 1;                        //enable WDT
  while (I2C1CON & 0x1F);           //wait for idle condition
  I2C1CONbits.RCEN = 1;             //enable receive
  while (!I2C1STATbits.RBF);        //wait for receive byte
  CLRWDT();
  u8_inByte = I2C1RCV;              //read byte;
  //wait for idle condition before attempting ACK
  while (I2C1CON & 0x1F);           //lower 5 bits must be 0
  I2C1CONbits.ACKDT = u8_ack2Send;  //ACK bit to send back on receive
  I2C1CONbits.ACKEN = 1;            //enable ACKbit transmittion
  while (I2C1CONbits.ACKEN);        //wait for completion
  _SWDTEN = u8_wdtState;              //restore WDT
  sz_lastTimeoutError = NULL;
  return(u8_inByte);                  //return the value
}
/**
Transaction: Write 1 byte (\em u8_d1) to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param u8_d1 Byte to send
*/
void write1I2C1(uint8 u8_addr,uint8 u8_d1) {
  startI2C1();
  putI2C1(I2C_WADDR(u8_addr));
  putI2C1(u8_d1);
  stopI2C1();
}
/**
Transaction: Write 2 bytes (\em u8_d1, \em u8_d2) to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param u8_d1 First byte to send
\param u8_d2 Second byte to send
*/
void write2I2C1(uint8 u8_addr,uint8 u8_d1, uint8 u8_d2) {
  startI2C1();
  putI2C1(I2C_WADDR(u8_addr));
  putI2C1(u8_d1);
  putI2C1(u8_d2);
  stopI2C1();
}

/**
Transaction: Write \em u16_cnt bytes stored in buffer \em *pu8_data to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param pu8_data Pointer to buffer containing bytes to send
\param u16_cnt Number of bytes to send
*/
void writeNI2C1(uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt) {
  uint16 u16_i;
  startI2C1();
  putI2C1(I2C_WADDR(u8_addr));
  for (u16_i=0; u16_i < u16_cnt; u16_i++) {
    putI2C1(*pu8_data);
    pu8_data++;
  }
  stopI2C1();
}
/**
Transaction: Read one byte from I2C slave at address \em u8_addr, save to \em *pu8_d1.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_d1 Pointer to location to store byte read from slave
*/
void read1I2C1 (uint8 u8_addr,uint8* pu8_d1) {
  startI2C1();
  putI2C1(I2C_RADDR(u8_addr));
  *pu8_d1 = getI2C1(I2C_NAK); //last ack bit from master to slave during read must be a NAK
  stopI2C1();
}
/**
Transaction: Read two bytes from I2C slave at address \em u8_addr, save to \em *pu8_d1, \em *pu8_d2.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_d1 Pointer to location to store first byte read from slave
\param pu8_d2 Pointer to location to store second byte read from slave
*/
void read2I2C1 (uint8 u8_addr,uint8* pu8_d1, uint8* pu8_d2) {
  startI2C1();
  putI2C1(I2C_RADDR(u8_addr));
  *pu8_d1 = getI2C1(I2C_ACK);
  *pu8_d2 = getI2C1(I2C_NAK);
  stopI2C1();
}
/**
Transaction: Read \em u16_cnt bytes from I2C slave at address \em u8_addr, save to buffer \em *pu8_data.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_data Pointer to buffer for storing bytes read from slave
\param u16_cnt Number of bytes read from slave.
*/
void readNI2C1 (uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt) {
  uint16 u16_i;
  startI2C1();
  putI2C1(I2C_RADDR(u8_addr));
  for (u16_i=0; u16_i < u16_cnt; u16_i++) {
    if (u16_i != u16_cnt-1) *pu8_data = getI2C1(I2C_ACK);
    else *pu8_data = getI2C1(I2C_NAK);
    pu8_data++;
  }
  stopI2C1();
}

#endif // #if (NUM_I2C_MODS >= 1)












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
#include <stdio.h>   //for NULL definition

// Only include if this UART exists.
#if (NUM_I2C_MODS >= 2)

// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_I2C_MODS so Doxygen
// will only see it once.
/** \file
 *  I2C support functions. \see pic24_i2c.h for details.
 */


/**
Configure and enable the I2C2 module for operation at \em u16_FkHZ kHZ clock speed.
\param u16_FkHZ specifies clock speed in kHZ
*/
void configI2C2(uint16 u16_FkHZ) {
  uint32 u32_temp;

  u32_temp = (FCY/1000L)/((uint32) u16_FkHZ);
  u32_temp = u32_temp - FCY/10000000L - 1;
  I2C2BRG = u32_temp;
  I2C2CONbits.I2CEN = 1;
}

/**
Operation: Perform an I2C start operation.
*/
void startI2C2(void) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C2 Start";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1; //enable WDT
  I2C2CONbits.SEN = 1;   // initiate start
  // wait until start finished
  while (I2C2CONbits.SEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Perform an I2C repeated start operation.
*/
void rstartI2C2(void) {// repeated start
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C2 RStart";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;  //enable WDT
  I2C2CONbits.RSEN = 1;   // initiate start
  // wait until start finished
  while (I2C2CONbits.RSEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Perform an I2C stop operation.
*/
void stopI2C2(void) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C2 Stop";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;  //enable WDT
  I2C2CONbits.PEN=1;     // initiate stop, PEN=1
  //wait until stop finished
  while (I2C2CONbits.PEN);
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
}

/**
Operation: Send one byte (\em u8_val), if NAK is returned use reportError() function to save error and do software reset.
\param u8_val byte to send
*/
void putI2C2(uint8 u8_val) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C2 Put";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;       //enable WDT
  I2C2TRN = u8_val;    // write byte
  while (I2C2STATbits.TRSTAT);   // wait for 8bits+ ack bit to finish
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
  if (I2C2STATbits.ACKSTAT != I2C_ACK) {
    //NAK returned
    reportError("I2CPUT2, NAK returned.");
  }
}

/**
Operation: Send one byte (\em u8_val), return the acknowledgement bit that comes back from the slave. This
function does not error out if a NAK is returned.
\param u8_val byte to send
\return Ack bit value returned from slave.
*/
uint8 putNoAckCheckI2C2(uint8 u8_val) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "I2C2 Put";
  u8_wdtState = _SWDTEN;  //save WDT state
  _SWDTEN = 1;       //enable WDT
  I2C2TRN = u8_val;    // write byte
  while (I2C2STATbits.TRSTAT);   // wait for 8bits+ ack bit to finish
  _SWDTEN = u8_wdtState;  //restore WDT
  sz_lastTimeoutError = NULL;
  return(I2C2STATbits.ACKSTAT);
}

/**
Operation: Wait for a byte byte on the I2C bus, send \em u8_ack2Send as the acknowledgement bit to send back to the slave.
\param u8_ack2Send ack bit to send back to slave after byte is read
\return byte read from slave
*/
uint8 getI2C2(uint8 u8_ack2Send) {
  uint8 u8_wdtState;
  uint8 u8_inByte;

  sz_lastTimeoutError = "I2C2 Get";
  u8_wdtState = _SWDTEN;              //save WDT state
  _SWDTEN = 1;                        //enable WDT
  while (I2C2CON & 0x1F);           //wait for idle condition
  I2C2CONbits.RCEN = 1;             //enable receive
  while (!I2C2STATbits.RBF);        //wait for receive byte
  CLRWDT();
  u8_inByte = I2C2RCV;              //read byte;
  //wait for idle condition before attempting ACK
  while (I2C2CON & 0x1F);           //lower 5 bits must be 0
  I2C2CONbits.ACKDT = u8_ack2Send;  //ACK bit to send back on receive
  I2C2CONbits.ACKEN = 1;            //enable ACKbit transmittion
  while (I2C2CONbits.ACKEN);        //wait for completion
  _SWDTEN = u8_wdtState;              //restore WDT
  sz_lastTimeoutError = NULL;
  return(u8_inByte);                  //return the value
}
/**
Transaction: Write 1 byte (\em u8_d1) to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param u8_d1 Byte to send
*/
void write1I2C2(uint8 u8_addr,uint8 u8_d1) {
  startI2C2();
  putI2C2(I2C_WADDR(u8_addr));
  putI2C2(u8_d1);
  stopI2C2();
}
/**
Transaction: Write 2 bytes (\em u8_d1, \em u8_d2) to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param u8_d1 First byte to send
\param u8_d2 Second byte to send
*/
void write2I2C2(uint8 u8_addr,uint8 u8_d1, uint8 u8_d2) {
  startI2C2();
  putI2C2(I2C_WADDR(u8_addr));
  putI2C2(u8_d1);
  putI2C2(u8_d2);
  stopI2C2();
}

/**
Transaction: Write \em u16_cnt bytes stored in buffer \em *pu8_data to I2C slave at address \em u8_addr.
\param u8_addr  Slave I2C address
\param pu8_data Pointer to buffer containing bytes to send
\param u16_cnt Number of bytes to send
*/
void writeNI2C2(uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt) {
  uint16 u16_i;
  startI2C2();
  putI2C2(I2C_WADDR(u8_addr));
  for (u16_i=0; u16_i < u16_cnt; u16_i++) {
    putI2C2(*pu8_data);
    pu8_data++;
  }
  stopI2C2();
}
/**
Transaction: Read one byte from I2C slave at address \em u8_addr, save to \em *pu8_d1.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_d1 Pointer to location to store byte read from slave
*/
void read1I2C2 (uint8 u8_addr,uint8* pu8_d1) {
  startI2C2();
  putI2C2(I2C_RADDR(u8_addr));
  *pu8_d1 = getI2C2(I2C_NAK); //last ack bit from master to slave during read must be a NAK
  stopI2C2();
}
/**
Transaction: Read two bytes from I2C slave at address \em u8_addr, save to \em *pu8_d1, \em *pu8_d2.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_d1 Pointer to location to store first byte read from slave
\param pu8_d2 Pointer to location to store second byte read from slave
*/
void read2I2C2 (uint8 u8_addr,uint8* pu8_d1, uint8* pu8_d2) {
  startI2C2();
  putI2C2(I2C_RADDR(u8_addr));
  *pu8_d1 = getI2C2(I2C_ACK);
  *pu8_d2 = getI2C2(I2C_NAK);
  stopI2C2();
}
/**
Transaction: Read \em u16_cnt bytes from I2C slave at address \em u8_addr, save to buffer \em *pu8_data.
As per the I2C standard, a NAK is returned for the last byte read from the slave, ACKs are returned for the other bytes.
\param u8_addr  Slave I2C address
\param pu8_data Pointer to buffer for storing bytes read from slave
\param u16_cnt Number of bytes read from slave.
*/
void readNI2C2 (uint8 u8_addr,uint8* pu8_data, uint16 u16_cnt) {
  uint16 u16_i;
  startI2C2();
  putI2C2(I2C_RADDR(u8_addr));
  for (u16_i=0; u16_i < u16_cnt; u16_i++) {
    if (u16_i != u16_cnt-1) *pu8_data = getI2C2(I2C_ACK);
    else *pu8_data = getI2C2(I2C_NAK);
    pu8_data++;
  }
  stopI2C2();
}

#endif // #if (NUM_I2C_MODS >= 2)












