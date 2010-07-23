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

// Only include if this module exists.
#if (NUM_ECAN_MODS >= 1)


// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_ECAN_MODS so Doxygen
// will only see it once.
/** \file
 *  ECAN support functions. \see pic24_ecan.h for details.
 */



#ifndef ECAN_1TIME_CODE_DEFS

/**
Format a standard data frame \em u8_n  for TX
\param p_ecanmsg pointer to message buffer (ECANMSG* )
\param u16_id Standard Identifier (11-bit)
\param u8_len  Number of data bytes in the message
*/


void formatStandardDataFrameECAN (ECANMSG* p_ecanmsg, uint16 u16_id, uint8 u8_len){
 p_ecanmsg->w0.IDE = 0;
 p_ecanmsg->w0.SRR = 0;
 p_ecanmsg->w0.SID = u16_id;
 p_ecanmsg->w1.EID17_6 = 0;
 p_ecanmsg->w2.EID5_0 = 0;
 p_ecanmsg->w2.RTR = 0;
 p_ecanmsg->w2.RB1 = 0;
 p_ecanmsg->w2.RB0 = 0;
 p_ecanmsg->w2.DLC = u8_len;     //length of the message
}


/**
Format an extended data frame \em u8_n  for TX
\param p_ecanmsg pointer to message buffer (ECANMSG* )
\param u32_id Standard Identifier (11-bit)
\param u8_len  Number of data bytes in the message
*/

void formatExtendedDataFrameECAN (ECANMSG* p_ecanmsg, uint32 u32_id, uint8 u8_len){
  
 p_ecanmsg->w0.IDE = 1;
 p_ecanmsg->w0.SRR = 0;
 p_ecanmsg->w0.SID =  (u32_id >> 18) & 0x7FF;
 p_ecanmsg->w1.EID17_6 = (u32_id >> 6) & 0xFFF;
 p_ecanmsg->w2.EID5_0 = u32_id & 0x3F;
 p_ecanmsg->w2.RTR = 0;
 p_ecanmsg->w2.RB1 = 0;
 p_ecanmsg->w2.RB0 = 0;
 p_ecanmsg->w2.DLC = u8_len;   //length of the message
}

/**
Extract the 29-bit message id from an extended data frame
\param p_ecanmsg pointer to RX message buffer (ECANMSG* )
\return 29-bit message id
*/

uint32 getIdExtendedDataFrameECAN (ECANMSG* p_ecanmsg){
  uint32 u32_id, u32_tmp;
  u32_tmp = p_ecanmsg->w0.SID;
  u32_id = u32_tmp << 18;
  u32_tmp = p_ecanmsg->w1.EID17_6;
  u32_id = u32_id | (u32_tmp << 6) | p_ecanmsg->w2.EID5_0; 
  return u32_id;
}

#define ECAN_1TIME_CODE_DEFS
#endif



/**
Clear full bit of buffer \em u8_bufNum  
\param u8_bufNum buffer number of full bit to clear (0 to 31)
*/

void clrRxFullFlagECAN1(uint8 u8_bufNum) {
  u8_bufNum &= 0x1F; //0-31
  if (u8_bufNum > 15) {
       u8_bufNum = u8_bufNum - 16;
       C1RXFUL2 = C1RXFUL2 & ~(1<<u8_bufNum);
  } else {
      C1RXFUL1 = C1RXFUL1 & ~(1<<u8_bufNum);
  }  
} 

/**
Get full bit of buffer \em u8_bufNum, zero if empty, non-zero if ull
\param u8_bufNum buffer number of full bit to read(0 to 31)
*/

uint8 getRxFullFlagECAN1(uint8 u8_bufNum) {
  u8_bufNum &= 0x1F; //0-31
  if (u8_bufNum > 15) {
       u8_bufNum = u8_bufNum - 16;
       return(C1RXFUL2 & (1<<u8_bufNum));
  } else {
       return(C1RXFUL1 & (1<<u8_bufNum));
  }  
} 

/**
Operation:  Clear all of the full and overflow RX flags.
*/
void clrRxFullOvfFlagsECAN1(void) {
  C1RXFUL1=0x0000;
  C1RXFUL2=0x0000;
  C1RXOVF1=0x0000;
  C1RXOVF2=0x0000;
}

/**
Configure a buffer as either RX or TX buffer, only has to be done for first 8 buffers.  
\param u8_bufNum buffer number (0 to 7)
\param u8_type buffer type (0 - receive, 1 transmit)
\param u8_priority only used for TX, priority (0-3)
*/
void configTxRxBufferECAN1(uint8 u8_bufNum, uint8 u8_type, uint8 u8_priority ) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  C1TR01CONbits.TXEN0 = u8_type; 
             C1TR01CONbits.TX0PRI = u8_priority;
             break;
    case 1:  C1TR01CONbits.TXEN1 = u8_type; 
             C1TR01CONbits.TX1PRI = u8_priority;
             break;
    case 2:  C1TR23CONbits.TXEN2 = u8_type; 
             C1TR23CONbits.TX2PRI = u8_priority;
             break;
    case 3:  C1TR23CONbits.TXEN3 = u8_type; 
             C1TR23CONbits.TX3PRI = u8_priority;
             break;
    case 4:  C1TR45CONbits.TXEN4 = u8_type; 
             C1TR45CONbits.TX4PRI = u8_priority;
             break;
    case 5:  C1TR45CONbits.TXEN5 = u8_type; 
             C1TR45CONbits.TX5PRI = u8_priority;
             break;
    case 6:  C1TR67CONbits.TXEN6 = u8_type; 
             C1TR67CONbits.TX6PRI = u8_priority;
             break;
    default:  C1TR67CONbits.TXEN7 = u8_type; 
             C1TR67CONbits.TX7PRI = u8_priority;
             break;
  }
}

/**
Start Transmit for buffer \em u8_bufNum  
\param u8_bufNum buffer number (0 to 7)
**/
void startTxECAN1(uint8 u8_bufNum) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  C1TR01CONbits.TXREQ0 = 1; break;
    case 1:  C1TR01CONbits.TXREQ1 = 1; break;
    case 2:  C1TR23CONbits.TXREQ2 = 1; break;
    case 3:  C1TR23CONbits.TXREQ3 = 1; break;
    case 4:  C1TR45CONbits.TXREQ4 = 1;; break;
    case 5:  C1TR45CONbits.TXREQ5 = 1; break;
    case 6:  C1TR67CONbits.TXREQ6 = 1;  break;
    default:  C1TR67CONbits.TXREQ7 = 1; break;
  }
}

/**
Start Transmit for buffer \em u8_bufNum  
\param u8_bufNum buffer number (0 to 7)
**/
uint8 getTxInProgressECAN1(uint8 u8_bufNum) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  return(C1TR01CONbits.TXREQ0);
    case 1:  return(C1TR01CONbits.TXREQ1);
    case 2:  return(C1TR23CONbits.TXREQ2);
    case 3:  return(C1TR23CONbits.TXREQ3);
    case 4:  return(C1TR45CONbits.TXREQ4);
    case 5:  return(C1TR45CONbits.TXREQ5);
    case 6:  return(C1TR67CONbits.TXREQ6);
    default:  return(C1TR67CONbits.TXREQ7);
  }
}

 


/**
Configure an acceptance Filter 
\param u8_filtNum filter number (0 to 15)
\param u32_id identifier, either SID (11 bits) or EID (29 bits)
\param u8_idType ID type (0: SID, nonzero: EID)
\param u8_bufnum RX buffer (0-14) to use for filter , if 15, then use FIFO
\param u8_maskReg Mask register (0-2) to use for filter
*/
void configRxFilterECAN1(uint8 u8_filtNum, uint32 u32_id, uint8 u8_idType, uint8 u8_bufnum, uint8 u8_maskReg) {
 uint16 *pu16_CxRXFySID,*pu16_CxRXFyEID, *pu16_CxFMSKSEL1, *pu16_CxBUFPNT1;
 uint16 u16_sid;
 uint16 u16_eid15_0;
 uint16 u16_eid17_16;
 uint16 u16_mask;
 uint8 u8_startPos;

 u8_filtNum &= 0xF;  //0-15
 u8_bufnum &= 0xF;   //0-15
 u8_maskReg &= 0x07;    //0-7
   
 pu16_CxRXFySID =  (uint16*) &C1RXF0SID + (u8_filtNum << 1);
 pu16_CxRXFyEID = pu16_CxRXFySID + 1;
 pu16_CxFMSKSEL1 = (uint16*) &C1FMSKSEL1 + (u8_filtNum >> 3);
 pu16_CxBUFPNT1 = (uint16*) &C1BUFPNT1 + (u8_filtNum >> 2);
 
 C1CTRL1bits.WIN=1;  //select filter register window

 //write to the CxRXFySID, CxRXFyEID registers 
 if(u8_idType) { // EID    
   u16_sid = (u32_id >> 18) & 0x7FF;
   u16_eid17_16 = (u32_id >>16) & 0x3;
   u16_eid15_0 = u32_id & 0xFFFF; 
   *pu16_CxRXFySID =(u16_sid <<5) | ECAN_MATCH_EID |  u16_eid17_16;	
   *pu16_CxRXFyEID = u16_eid15_0;				            
  } else  {   //SID
    u16_sid = u32_id  & 0x7FF;
 	*pu16_CxRXFySID = u16_sid <<5;   
	*pu16_CxRXFyEID = 0;             
  }

 //point the filter to the RX buffer (modify CxBUFPNT1 register)
 u8_startPos = 4 * (u8_filtNum & 0x3);  //starting bit position to mask
 u16_mask = ~ ( 0xF << u8_startPos);
 *pu16_CxBUFPNT1 = (*pu16_CxBUFPNT1 & u16_mask) | (u8_bufnum << u8_startPos);

 //point the filter to the mask register (modify CxFMSKSEL1 register)
 u8_startPos = 2 * (u8_filtNum & 0x7);
 u16_mask = ~ ( 0x3 << u8_startPos);
 *pu16_CxFMSKSEL1 = (*pu16_CxFMSKSEL1 & u16_mask) | (u8_maskReg << u8_startPos);

 C1FEN1 = C1FEN1 | (1 << u8_filtNum) ; // Enable the filter

 C1CTRL1bits.WIN=0; 

}

/**
Configure an acceptance MASK
\param u8_maskNum mask number (0 to 3; 0 to 2 specifies mask register, 3 then no mask is used)
\param u32_idMask mask for the identifier, either SID mask (11 bits) or EID mask (29 bits)
\param u8_idType ID type (0: SID, nonzero: EID)
\param u8_matchType  Match type; if zero match either SID or EID addresses if filter matches
(i.e, match if  (Filter SID == Message SID) || (Filter SID:EID = Message SID:EID)) )
If nonzero, match only message types as specified by the filter (either SID or SID:EID). 
*/

void configRxMaskECAN1(uint8 u8_maskNum, uint32 u32_idMask, uint8 u8_idType, uint8 u8_matchType){
uint16 *pu16_CxRXMySID,*pu16_CxRXMyEID;
uint16 u16_msid;
uint16 u16_meid15_0;
uint16 u16_meid17_16;

pu16_CxRXMySID =(uint16*) &C1RXM0SID + (u8_maskNum << 1);
pu16_CxRXMyEID = pu16_CxRXMySID + 1;

C1CTRL1bits.WIN=1;  //select filter register window

 //write to the CxRXMySID, CxRXMyEID registers 
 if(u8_idType) { // EID  
   u16_msid = (u32_idMask >> 18) & 0x7FF;
   u16_meid17_16 = (u32_idMask >>16) & 0x3;
   u16_meid15_0 = u32_idMask & 0xFFFF; 
   if (u8_matchType) *pu16_CxRXMySID =(u16_msid <<5) | ECAN_MATCH_EID |  u16_meid17_16;	
    else *pu16_CxRXMySID =(u16_msid <<5) |   u16_meid17_16;
   *pu16_CxRXMyEID = u16_meid15_0;
 } else {
   u16_msid = u32_idMask  & 0x7FF;
   if (u8_matchType) *pu16_CxRXMySID = (u16_msid <<5) | ECAN_MATCH_EID ;   
   else  *pu16_CxRXMySID = (u16_msid <<5);
   *pu16_CxRXMyEID = 0;
 }   
C1CTRL1bits.WIN=0; 
}

#endif // #if (NUM_ECAN_MODS >= ${x})













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

// Only include if this module exists.
#if (NUM_ECAN_MODS >= 2)


// Documentation for this file. If the \file tag is not present,
// this file will not be documented.
// Note: place this comment below the #if NUM_ECAN_MODS so Doxygen
// will only see it once.
/** \file
 *  ECAN support functions. \see pic24_ecan.h for details.
 */



#ifndef ECAN_1TIME_CODE_DEFS

/**
Format a standard data frame \em u8_n  for TX
\param p_ecanmsg pointer to message buffer (ECANMSG* )
\param u16_id Standard Identifier (11-bit)
\param u8_len  Number of data bytes in the message
*/


void formatStandardDataFrameECAN (ECANMSG* p_ecanmsg, uint16 u16_id, uint8 u8_len){
 p_ecanmsg->w0.IDE = 0;
 p_ecanmsg->w0.SRR = 0;
 p_ecanmsg->w0.SID = u16_id;
 p_ecanmsg->w1.EID17_6 = 0;
 p_ecanmsg->w2.EID5_0 = 0;
 p_ecanmsg->w2.RTR = 0;
 p_ecanmsg->w2.RB1 = 0;
 p_ecanmsg->w2.RB0 = 0;
 p_ecanmsg->w2.DLC = u8_len;     //length of the message
}


/**
Format an extended data frame \em u8_n  for TX
\param p_ecanmsg pointer to message buffer (ECANMSG* )
\param u32_id Standard Identifier (11-bit)
\param u8_len  Number of data bytes in the message
*/

void formatExtendedDataFrameECAN (ECANMSG* p_ecanmsg, uint32 u32_id, uint8 u8_len){
  
 p_ecanmsg->w0.IDE = 1;
 p_ecanmsg->w0.SRR = 0;
 p_ecanmsg->w0.SID =  (u32_id >> 18) & 0x7FF;
 p_ecanmsg->w1.EID17_6 = (u32_id >> 6) & 0xFFF;
 p_ecanmsg->w2.EID5_0 = u32_id & 0x3F;
 p_ecanmsg->w2.RTR = 0;
 p_ecanmsg->w2.RB1 = 0;
 p_ecanmsg->w2.RB0 = 0;
 p_ecanmsg->w2.DLC = u8_len;   //length of the message
}

/**
Extract the 29-bit message id from an extended data frame
\param p_ecanmsg pointer to RX message buffer (ECANMSG* )
\return 29-bit message id
*/

uint32 getIdExtendedDataFrameECAN (ECANMSG* p_ecanmsg){
  uint32 u32_id, u32_tmp;
  u32_tmp = p_ecanmsg->w0.SID;
  u32_id = u32_tmp << 18;
  u32_tmp = p_ecanmsg->w1.EID17_6;
  u32_id = u32_id | (u32_tmp << 6) | p_ecanmsg->w2.EID5_0; 
  return u32_id;
}

#define ECAN_1TIME_CODE_DEFS
#endif



/**
Clear full bit of buffer \em u8_bufNum  
\param u8_bufNum buffer number of full bit to clear (0 to 31)
*/

void clrRxFullFlagECAN2(uint8 u8_bufNum) {
  u8_bufNum &= 0x1F; //0-31
  if (u8_bufNum > 15) {
       u8_bufNum = u8_bufNum - 16;
       C2RXFUL2 = C2RXFUL2 & ~(1<<u8_bufNum);
  } else {
      C2RXFUL1 = C2RXFUL1 & ~(1<<u8_bufNum);
  }  
} 

/**
Get full bit of buffer \em u8_bufNum, zero if empty, non-zero if ull
\param u8_bufNum buffer number of full bit to read(0 to 31)
*/

uint8 getRxFullFlagECAN2(uint8 u8_bufNum) {
  u8_bufNum &= 0x1F; //0-31
  if (u8_bufNum > 15) {
       u8_bufNum = u8_bufNum - 16;
       return(C2RXFUL2 & (1<<u8_bufNum));
  } else {
       return(C2RXFUL1 & (1<<u8_bufNum));
  }  
} 

/**
Operation:  Clear all of the full and overflow RX flags.
*/
void clrRxFullOvfFlagsECAN2(void) {
  C2RXFUL1=0x0000;
  C2RXFUL2=0x0000;
  C2RXOVF1=0x0000;
  C2RXOVF2=0x0000;
}

/**
Configure a buffer as either RX or TX buffer, only has to be done for first 8 buffers.  
\param u8_bufNum buffer number (0 to 7)
\param u8_type buffer type (0 - receive, 1 transmit)
\param u8_priority only used for TX, priority (0-3)
*/
void configTxRxBufferECAN2(uint8 u8_bufNum, uint8 u8_type, uint8 u8_priority ) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  C2TR01CONbits.TXEN0 = u8_type; 
             C2TR01CONbits.TX0PRI = u8_priority;
             break;
    case 1:  C2TR01CONbits.TXEN1 = u8_type; 
             C2TR01CONbits.TX1PRI = u8_priority;
             break;
    case 2:  C2TR23CONbits.TXEN2 = u8_type; 
             C2TR23CONbits.TX2PRI = u8_priority;
             break;
    case 3:  C2TR23CONbits.TXEN3 = u8_type; 
             C2TR23CONbits.TX3PRI = u8_priority;
             break;
    case 4:  C2TR45CONbits.TXEN4 = u8_type; 
             C2TR45CONbits.TX4PRI = u8_priority;
             break;
    case 5:  C2TR45CONbits.TXEN5 = u8_type; 
             C2TR45CONbits.TX5PRI = u8_priority;
             break;
    case 6:  C2TR67CONbits.TXEN6 = u8_type; 
             C2TR67CONbits.TX6PRI = u8_priority;
             break;
    default:  C2TR67CONbits.TXEN7 = u8_type; 
             C2TR67CONbits.TX7PRI = u8_priority;
             break;
  }
}

/**
Start Transmit for buffer \em u8_bufNum  
\param u8_bufNum buffer number (0 to 7)
**/
void startTxECAN2(uint8 u8_bufNum) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  C2TR01CONbits.TXREQ0 = 1; break;
    case 1:  C2TR01CONbits.TXREQ1 = 1; break;
    case 2:  C2TR23CONbits.TXREQ2 = 1; break;
    case 3:  C2TR23CONbits.TXREQ3 = 1; break;
    case 4:  C2TR45CONbits.TXREQ4 = 1;; break;
    case 5:  C2TR45CONbits.TXREQ5 = 1; break;
    case 6:  C2TR67CONbits.TXREQ6 = 1;  break;
    default:  C2TR67CONbits.TXREQ7 = 1; break;
  }
}

/**
Start Transmit for buffer \em u8_bufNum  
\param u8_bufNum buffer number (0 to 7)
**/
uint8 getTxInProgressECAN2(uint8 u8_bufNum) {
  u8_bufNum &= 0x07; //0-7
  switch (u8_bufNum) {
    case 0:  return(C2TR01CONbits.TXREQ0);
    case 1:  return(C2TR01CONbits.TXREQ1);
    case 2:  return(C2TR23CONbits.TXREQ2);
    case 3:  return(C2TR23CONbits.TXREQ3);
    case 4:  return(C2TR45CONbits.TXREQ4);
    case 5:  return(C2TR45CONbits.TXREQ5);
    case 6:  return(C2TR67CONbits.TXREQ6);
    default:  return(C2TR67CONbits.TXREQ7);
  }
}

 


/**
Configure an acceptance Filter 
\param u8_filtNum filter number (0 to 15)
\param u32_id identifier, either SID (11 bits) or EID (29 bits)
\param u8_idType ID type (0: SID, nonzero: EID)
\param u8_bufnum RX buffer (0-14) to use for filter , if 15, then use FIFO
\param u8_maskReg Mask register (0-2) to use for filter
*/
void configRxFilterECAN2(uint8 u8_filtNum, uint32 u32_id, uint8 u8_idType, uint8 u8_bufnum, uint8 u8_maskReg) {
 uint16 *pu16_CxRXFySID,*pu16_CxRXFyEID, *pu16_CxFMSKSEL1, *pu16_CxBUFPNT1;
 uint16 u16_sid;
 uint16 u16_eid15_0;
 uint16 u16_eid17_16;
 uint16 u16_mask;
 uint8 u8_startPos;

 u8_filtNum &= 0xF;  //0-15
 u8_bufnum &= 0xF;   //0-15
 u8_maskReg &= 0x07;    //0-7
   
 pu16_CxRXFySID =  (uint16*) &C2RXF0SID + (u8_filtNum << 1);
 pu16_CxRXFyEID = pu16_CxRXFySID + 1;
 pu16_CxFMSKSEL1 = (uint16*) &C2FMSKSEL1 + (u8_filtNum >> 3);
 pu16_CxBUFPNT1 = (uint16*) &C2BUFPNT1 + (u8_filtNum >> 2);
 
 C2CTRL1bits.WIN=1;  //select filter register window

 //write to the CxRXFySID, CxRXFyEID registers 
 if(u8_idType) { // EID    
   u16_sid = (u32_id >> 18) & 0x7FF;
   u16_eid17_16 = (u32_id >>16) & 0x3;
   u16_eid15_0 = u32_id & 0xFFFF; 
   *pu16_CxRXFySID =(u16_sid <<5) | ECAN_MATCH_EID |  u16_eid17_16;	
   *pu16_CxRXFyEID = u16_eid15_0;				            
  } else  {   //SID
    u16_sid = u32_id  & 0x7FF;
 	*pu16_CxRXFySID = u16_sid <<5;   
	*pu16_CxRXFyEID = 0;             
  }

 //point the filter to the RX buffer (modify CxBUFPNT1 register)
 u8_startPos = 4 * (u8_filtNum & 0x3);  //starting bit position to mask
 u16_mask = ~ ( 0xF << u8_startPos);
 *pu16_CxBUFPNT1 = (*pu16_CxBUFPNT1 & u16_mask) | (u8_bufnum << u8_startPos);

 //point the filter to the mask register (modify CxFMSKSEL1 register)
 u8_startPos = 2 * (u8_filtNum & 0x7);
 u16_mask = ~ ( 0x3 << u8_startPos);
 *pu16_CxFMSKSEL1 = (*pu16_CxFMSKSEL1 & u16_mask) | (u8_maskReg << u8_startPos);

 C2FEN1 = C2FEN1 | (1 << u8_filtNum) ; // Enable the filter

 C2CTRL1bits.WIN=0; 

}

/**
Configure an acceptance MASK
\param u8_maskNum mask number (0 to 3; 0 to 2 specifies mask register, 3 then no mask is used)
\param u32_idMask mask for the identifier, either SID mask (11 bits) or EID mask (29 bits)
\param u8_idType ID type (0: SID, nonzero: EID)
\param u8_matchType  Match type; if zero match either SID or EID addresses if filter matches
(i.e, match if  (Filter SID == Message SID) || (Filter SID:EID = Message SID:EID)) )
If nonzero, match only message types as specified by the filter (either SID or SID:EID). 
*/

void configRxMaskECAN2(uint8 u8_maskNum, uint32 u32_idMask, uint8 u8_idType, uint8 u8_matchType){
uint16 *pu16_CxRXMySID,*pu16_CxRXMyEID;
uint16 u16_msid;
uint16 u16_meid15_0;
uint16 u16_meid17_16;

pu16_CxRXMySID =(uint16*) &C2RXM0SID + (u8_maskNum << 1);
pu16_CxRXMyEID = pu16_CxRXMySID + 1;

C2CTRL1bits.WIN=1;  //select filter register window

 //write to the CxRXMySID, CxRXMyEID registers 
 if(u8_idType) { // EID  
   u16_msid = (u32_idMask >> 18) & 0x7FF;
   u16_meid17_16 = (u32_idMask >>16) & 0x3;
   u16_meid15_0 = u32_idMask & 0xFFFF; 
   if (u8_matchType) *pu16_CxRXMySID =(u16_msid <<5) | ECAN_MATCH_EID |  u16_meid17_16;	
    else *pu16_CxRXMySID =(u16_msid <<5) |   u16_meid17_16;
   *pu16_CxRXMyEID = u16_meid15_0;
 } else {
   u16_msid = u32_idMask  & 0x7FF;
   if (u8_matchType) *pu16_CxRXMySID = (u16_msid <<5) | ECAN_MATCH_EID ;   
   else  *pu16_CxRXMySID = (u16_msid <<5);
   *pu16_CxRXMyEID = 0;
 }   
C2CTRL1bits.WIN=0; 
}

#endif // #if (NUM_ECAN_MODS >= ${x})













