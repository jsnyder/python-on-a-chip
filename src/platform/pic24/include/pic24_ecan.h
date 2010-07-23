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

#ifndef _PIC24_ECAN1_H_
#define _PIC24_ECAN1_H_

// Only include if this ECAN Module exists.
#if (NUM_ECAN_MODS >= 1)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_ECAN_MODS so Doxygen
// will only see it once.
/** \file
*  ECAN Header File
*/

#ifndef ECAN_1TIME_HEADER_DEFS

#define ECAN_MODE_NORMAL 0
#define ECAN_MODE_DISABLED 1
#define ECAN_MODE_LOOPBACK 2
#define ECAN_MODE_LISTEN_ONLY 3
#define ECAN_MODE_CONFIGURE 4
#define ECAN_LISTEN_ALL_MESSAGES 7

#define ECAN_FCAN_IS_FCY 1
#define ECAN_FCAN_IS_OSC 0


//CiCFG2 register  (Baud rate config 2 register)
#define ECAN_NO_WAKEUP 0x4000
#define ECAN_SEG2PH_8TQ (0x0007 << 8)
#define ECAN_SEG2PH_7TQ (0x0006 << 8)
#define ECAN_SEG2PH_6TQ (0x0005 << 8)
#define ECAN_SEG2PH_5TQ (0x0004 << 8)
#define ECAN_SEG2PH_4TQ (0x0003 << 8)
#define ECAN_SEG2PH_3TQ (0x0002 << 8)
#define ECAN_SEG2PH_2TQ (0x0001 << 8)
#define ECAN_SEG2PH_1TQ (0x0000 << 8)

#define ECAN_SEG2_PROGRAMMABLE 0x0080
#define ECAN_SEG2_FIXED        0x0000

#define ECAN_SAMPLE_3TIMES 0x0040
#define ECAN_SAMPLE_1TIMES 0x0000

#define ECAN_SEG1PH_8TQ (0x0007 << 3)
#define ECAN_SEG1PH_7TQ (0x0006 << 3)
#define ECAN_SEG1PH_6TQ (0x0005 << 3)
#define ECAN_SEG1PH_5TQ (0x0004 << 3)
#define ECAN_SEG1PH_4TQ (0x0003 << 3)
#define ECAN_SEG1PH_3TQ (0x0002 << 3)
#define ECAN_SEG1PH_2TQ (0x0001 << 3)
#define ECAN_SEG1PH_1TQ (0x0000 << 3)

#define ECAN_PRSEG_8TQ 0x0007
#define ECAN_PRSEG_7TQ 0x0006
#define ECAN_PRSEG_6TQ 0x0005
#define ECAN_PRSEG_5TQ 0x0004
#define ECAN_PRSEG_4TQ 0x0003
#define ECAN_PRSEG_3TQ 0x0002
#define ECAN_PRSEG_2TQ 0x0001
#define ECAN_PRSEG_1TQ 0x0000

//CiCFG1 register (Baud rate config 1 register)
#define ECAN_SYNC_JUMP_4   (0x0003 << 6)
#define ECAN_SYNC_JUMP_3   (0x0002 << 6)
#define ECAN_SYNC_JUMP_2   (0x0001 << 6)
#define ECAN_SYNC_JUMP_1   (0x0000 << 6)

#define ECAN_PRE_2x64 0x003f
#define ECAN_PRE_2x63 0x003e
#define ECAN_PRE_2x62 0x003d
#define ECAN_PRE_2x61 0x003c
#define ECAN_PRE_2x60 0x003b
#define ECAN_PRE_2x59 0x003a
#define ECAN_PRE_2x58 0x0039
#define ECAN_PRE_2x57 0x0038
#define ECAN_PRE_2x56 0x0037
#define ECAN_PRE_2x55 0x0036
#define ECAN_PRE_2x54 0x0035
#define ECAN_PRE_2x53 0x0034
#define ECAN_PRE_2x52 0x0033
#define ECAN_PRE_2x51 0x0032
#define ECAN_PRE_2x50 0x0031
#define ECAN_PRE_2x49 0x0030
#define ECAN_PRE_2x48 0x002f
#define ECAN_PRE_2x47 0x002e
#define ECAN_PRE_2x46 0x002d
#define ECAN_PRE_2x45 0x002c
#define ECAN_PRE_2x44 0x002b
#define ECAN_PRE_2x43 0x002a
#define ECAN_PRE_2x42 0x0029
#define ECAN_PRE_2x41 0x0028
#define ECAN_PRE_2x40 0x0027
#define ECAN_PRE_2x39 0x0026
#define ECAN_PRE_2x38 0x0025
#define ECAN_PRE_2x37 0x0024
#define ECAN_PRE_2x36 0x0023
#define ECAN_PRE_2x35 0x0022
#define ECAN_PRE_2x34 0x0021
#define ECAN_PRE_2x33 0x0020
#define ECAN_PRE_2x32 0x001f
#define ECAN_PRE_2x31 0x001e
#define ECAN_PRE_2x30 0x001d
#define ECAN_PRE_2x29 0x001c
#define ECAN_PRE_2x28 0x001b
#define ECAN_PRE_2x27 0x001a
#define ECAN_PRE_2x26 0x0019
#define ECAN_PRE_2x25 0x0018
#define ECAN_PRE_2x24 0x0017
#define ECAN_PRE_2x23 0x0016
#define ECAN_PRE_2x22 0x0015
#define ECAN_PRE_2x21 0x0014
#define ECAN_PRE_2x20 0x0013
#define ECAN_PRE_2x19 0x0012
#define ECAN_PRE_2x18 0x0011
#define ECAN_PRE_2x17 0x0010
#define ECAN_PRE_2x16 0x000f
#define ECAN_PRE_2x15 0x000e
#define ECAN_PRE_2x14 0x000d
#define ECAN_PRE_2x13 0x000c
#define ECAN_PRE_2x12 0x000b
#define ECAN_PRE_2x11 0x000a
#define ECAN_PRE_2x10 0x0009
#define ECAN_PRE_2x9 0x0008
#define ECAN_PRE_2x8 0x0007
#define ECAN_PRE_2x7 0x0006
#define ECAN_PRE_2x6 0x0005
#define ECAN_PRE_2x5 0x0004
#define ECAN_PRE_2x4 0x0003
#define ECAN_PRE_2x3 0x0002
#define ECAN_PRE_2x2 0x0001
#define ECAN_PRE_2x1 0x0000

//CiFCTRL register (FIFO Control register)
#define ECAN_DMA_BUF_SIZE_32 (0x0006 << 13)
#define ECAN_DMA_BUF_SIZE_24 (0x0005 << 13)
#define ECAN_DMA_BUF_SIZE_16 (0x0004 << 13)
#define ECAN_DMA_BUF_SIZE_12 (0x0003 << 13)
#define ECAN_DMA_BUF_SIZE_8 (0x0002 << 13)
#define ECAN_DMA_BUF_SIZE_6 (0x0001 << 13)
#define ECAN_DMA_BUF_SIZE_4 (0x0000 << 13)


#define ECAN_FIFO_START_AREA_31 31
#define ECAN_FIFO_START_AREA_30 30
#define ECAN_FIFO_START_AREA_29 29
#define ECAN_FIFO_START_AREA_28 28
#define ECAN_FIFO_START_AREA_27 27
#define ECAN_FIFO_START_AREA_26 26
#define ECAN_FIFO_START_AREA_25 25
#define ECAN_FIFO_START_AREA_24 24
#define ECAN_FIFO_START_AREA_23 23
#define ECAN_FIFO_START_AREA_22 22
#define ECAN_FIFO_START_AREA_21 21
#define ECAN_FIFO_START_AREA_20 20
#define ECAN_FIFO_START_AREA_19 19
#define ECAN_FIFO_START_AREA_18 18
#define ECAN_FIFO_START_AREA_17 17
#define ECAN_FIFO_START_AREA_16 16
#define ECAN_FIFO_START_AREA_15 15
#define ECAN_FIFO_START_AREA_14 14
#define ECAN_FIFO_START_AREA_13 13
#define ECAN_FIFO_START_AREA_12 12
#define ECAN_FIFO_START_AREA_11 11
#define ECAN_FIFO_START_AREA_10 10
#define ECAN_FIFO_START_AREA_9 9
#define ECAN_FIFO_START_AREA_8 8
#define ECAN_FIFO_START_AREA_7 7
#define ECAN_FIFO_START_AREA_6 6
#define ECAN_FIFO_START_AREA_5 5
#define ECAN_FIFO_START_AREA_4 4
#define ECAN_FIFO_START_AREA_3 3
#define ECAN_FIFO_START_AREA_2 2
#define ECAN_FIFO_START_AREA_1 1
#define ECAN_FIFO_START_AREA_0 0

//CiRXFnSID  register
#define ECAN_MATCH_EID   0x0008
#define ECAN_MATCH_SID   0x0000

#define ECAN_USE_FIFO   0xF

//CiTRmnCON  TXRX buffer control
#define ECAN_RX_BUFF 0   
#define ECAN_TX_BUFF 1

 
//Data structure for ECAN Data Frame
typedef struct _ECANW0 {
    unsigned IDE: 1;
    unsigned SRR:1;
    unsigned SID:11;
}ECANW0;
typedef struct _ECANW1 {
    unsigned EID17_6: 12;
}ECANW1;

typedef struct _ECANW2 {
    unsigned DLC:4;
    unsigned RB0:1;
    unsigned :3;
    unsigned RB1:1;
    unsigned RTR:1;
    unsigned EID5_0:6;
}ECANW2;

typedef struct _ECANW7 {
    unsigned :8;
    unsigned FILHIT:5;
    unsigned :3;
}ECANW7;



typedef struct _ECANMSG {
   ECANW0 w0;
   ECANW1 w1;
   ECANW2 w2;
   union64 data;
   ECANW7  w7;
}ECANMSG;


void formatStandardDataFrameECAN (ECANMSG* p_ecanmsg, uint16 u16_id, uint8 u8_len);
void formatExtendedDataFrameECAN (ECANMSG* p_ecanmsg, uint32 u32_id, uint8 u8_len);
uint32 getIdExtendedDataFrameECAN (ECANMSG* p_ecanmsg);

#define ECAN_1TIME_HEADER_DEFS
#endif




#ifdef _C1IF
/** Waits until all characters placed in the UART have been sent. */
inline static void CHANGE_MODE_ECAN1(mode) {
  C1CTRL1bits.REQOP = mode;
  while(C1CTRL1bits.OPMODE != mode); 
}

/** Return the number (0-31) of the next ECAN FIFO read buffer
 */
#define GET_FIFO_READBUFFER_ECAN1() (C1FIFO & 0x1F)   

void clrRxFullFlagECAN1(uint8 u8_bufNum);
uint8 getRxFullFlagECAN1(uint8 u8_bufNum);
void clrRxFullOvfFlagsECAN1(void);
void configTxRxBufferECAN1(uint8 u8_bufNum, uint8 u8_type, uint8 u8_priority);
void configRxFilterECAN1(uint8 u8_filtNum, uint32 u32_id, uint8 u8_idType, uint8 u8_bufnum, uint8 u8_maskReg);
void configRxMaskECAN1(uint8 u8_maskNum, uint32 u32_idMask, uint8 u8_idType, uint8 u8_matchType);
void startTxECAN1(uint8 u8_bufNum);
uint8 getTxInProgressECAN1(uint8 u8_bufNum);

#endif

 
#endif // #if (NUM_ECAN_MODS >= 1)
#endif // #define _PIC24_ECAN1_H_



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

#ifndef _PIC24_ECAN2_H_
#define _PIC24_ECAN2_H_

// Only include if this ECAN Module exists.
#if (NUM_ECAN_MODS >= 2)

// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
// Note: place this comment below the #if NUM_ECAN_MODS so Doxygen
// will only see it once.
/** \file
*  ECAN Header File
*/

#ifndef ECAN_1TIME_HEADER_DEFS

#define ECAN_MODE_NORMAL 0
#define ECAN_MODE_DISABLED 1
#define ECAN_MODE_LOOPBACK 2
#define ECAN_MODE_LISTEN_ONLY 3
#define ECAN_MODE_CONFIGURE 4
#define ECAN_LISTEN_ALL_MESSAGES 7

#define ECAN_FCAN_IS_FCY 1
#define ECAN_FCAN_IS_OSC 0


//CiCFG2 register  (Baud rate config 2 register)
#define ECAN_NO_WAKEUP 0x4000
#define ECAN_SEG2PH_8TQ (0x0007 << 8)
#define ECAN_SEG2PH_7TQ (0x0006 << 8)
#define ECAN_SEG2PH_6TQ (0x0005 << 8)
#define ECAN_SEG2PH_5TQ (0x0004 << 8)
#define ECAN_SEG2PH_4TQ (0x0003 << 8)
#define ECAN_SEG2PH_3TQ (0x0002 << 8)
#define ECAN_SEG2PH_2TQ (0x0001 << 8)
#define ECAN_SEG2PH_1TQ (0x0000 << 8)

#define ECAN_SEG2_PROGRAMMABLE 0x0080
#define ECAN_SEG2_FIXED        0x0000

#define ECAN_SAMPLE_3TIMES 0x0040
#define ECAN_SAMPLE_1TIMES 0x0000

#define ECAN_SEG1PH_8TQ (0x0007 << 3)
#define ECAN_SEG1PH_7TQ (0x0006 << 3)
#define ECAN_SEG1PH_6TQ (0x0005 << 3)
#define ECAN_SEG1PH_5TQ (0x0004 << 3)
#define ECAN_SEG1PH_4TQ (0x0003 << 3)
#define ECAN_SEG1PH_3TQ (0x0002 << 3)
#define ECAN_SEG1PH_2TQ (0x0001 << 3)
#define ECAN_SEG1PH_1TQ (0x0000 << 3)

#define ECAN_PRSEG_8TQ 0x0007
#define ECAN_PRSEG_7TQ 0x0006
#define ECAN_PRSEG_6TQ 0x0005
#define ECAN_PRSEG_5TQ 0x0004
#define ECAN_PRSEG_4TQ 0x0003
#define ECAN_PRSEG_3TQ 0x0002
#define ECAN_PRSEG_2TQ 0x0001
#define ECAN_PRSEG_1TQ 0x0000

//CiCFG1 register (Baud rate config 1 register)
#define ECAN_SYNC_JUMP_4   (0x0003 << 6)
#define ECAN_SYNC_JUMP_3   (0x0002 << 6)
#define ECAN_SYNC_JUMP_2   (0x0001 << 6)
#define ECAN_SYNC_JUMP_1   (0x0000 << 6)

#define ECAN_PRE_2x64 0x003f
#define ECAN_PRE_2x63 0x003e
#define ECAN_PRE_2x62 0x003d
#define ECAN_PRE_2x61 0x003c
#define ECAN_PRE_2x60 0x003b
#define ECAN_PRE_2x59 0x003a
#define ECAN_PRE_2x58 0x0039
#define ECAN_PRE_2x57 0x0038
#define ECAN_PRE_2x56 0x0037
#define ECAN_PRE_2x55 0x0036
#define ECAN_PRE_2x54 0x0035
#define ECAN_PRE_2x53 0x0034
#define ECAN_PRE_2x52 0x0033
#define ECAN_PRE_2x51 0x0032
#define ECAN_PRE_2x50 0x0031
#define ECAN_PRE_2x49 0x0030
#define ECAN_PRE_2x48 0x002f
#define ECAN_PRE_2x47 0x002e
#define ECAN_PRE_2x46 0x002d
#define ECAN_PRE_2x45 0x002c
#define ECAN_PRE_2x44 0x002b
#define ECAN_PRE_2x43 0x002a
#define ECAN_PRE_2x42 0x0029
#define ECAN_PRE_2x41 0x0028
#define ECAN_PRE_2x40 0x0027
#define ECAN_PRE_2x39 0x0026
#define ECAN_PRE_2x38 0x0025
#define ECAN_PRE_2x37 0x0024
#define ECAN_PRE_2x36 0x0023
#define ECAN_PRE_2x35 0x0022
#define ECAN_PRE_2x34 0x0021
#define ECAN_PRE_2x33 0x0020
#define ECAN_PRE_2x32 0x001f
#define ECAN_PRE_2x31 0x001e
#define ECAN_PRE_2x30 0x001d
#define ECAN_PRE_2x29 0x001c
#define ECAN_PRE_2x28 0x001b
#define ECAN_PRE_2x27 0x001a
#define ECAN_PRE_2x26 0x0019
#define ECAN_PRE_2x25 0x0018
#define ECAN_PRE_2x24 0x0017
#define ECAN_PRE_2x23 0x0016
#define ECAN_PRE_2x22 0x0015
#define ECAN_PRE_2x21 0x0014
#define ECAN_PRE_2x20 0x0013
#define ECAN_PRE_2x19 0x0012
#define ECAN_PRE_2x18 0x0011
#define ECAN_PRE_2x17 0x0010
#define ECAN_PRE_2x16 0x000f
#define ECAN_PRE_2x15 0x000e
#define ECAN_PRE_2x14 0x000d
#define ECAN_PRE_2x13 0x000c
#define ECAN_PRE_2x12 0x000b
#define ECAN_PRE_2x11 0x000a
#define ECAN_PRE_2x10 0x0009
#define ECAN_PRE_2x9 0x0008
#define ECAN_PRE_2x8 0x0007
#define ECAN_PRE_2x7 0x0006
#define ECAN_PRE_2x6 0x0005
#define ECAN_PRE_2x5 0x0004
#define ECAN_PRE_2x4 0x0003
#define ECAN_PRE_2x3 0x0002
#define ECAN_PRE_2x2 0x0001
#define ECAN_PRE_2x1 0x0000

//CiFCTRL register (FIFO Control register)
#define ECAN_DMA_BUF_SIZE_32 (0x0006 << 13)
#define ECAN_DMA_BUF_SIZE_24 (0x0005 << 13)
#define ECAN_DMA_BUF_SIZE_16 (0x0004 << 13)
#define ECAN_DMA_BUF_SIZE_12 (0x0003 << 13)
#define ECAN_DMA_BUF_SIZE_8 (0x0002 << 13)
#define ECAN_DMA_BUF_SIZE_6 (0x0001 << 13)
#define ECAN_DMA_BUF_SIZE_4 (0x0000 << 13)


#define ECAN_FIFO_START_AREA_31 31
#define ECAN_FIFO_START_AREA_30 30
#define ECAN_FIFO_START_AREA_29 29
#define ECAN_FIFO_START_AREA_28 28
#define ECAN_FIFO_START_AREA_27 27
#define ECAN_FIFO_START_AREA_26 26
#define ECAN_FIFO_START_AREA_25 25
#define ECAN_FIFO_START_AREA_24 24
#define ECAN_FIFO_START_AREA_23 23
#define ECAN_FIFO_START_AREA_22 22
#define ECAN_FIFO_START_AREA_21 21
#define ECAN_FIFO_START_AREA_20 20
#define ECAN_FIFO_START_AREA_19 19
#define ECAN_FIFO_START_AREA_18 18
#define ECAN_FIFO_START_AREA_17 17
#define ECAN_FIFO_START_AREA_16 16
#define ECAN_FIFO_START_AREA_15 15
#define ECAN_FIFO_START_AREA_14 14
#define ECAN_FIFO_START_AREA_13 13
#define ECAN_FIFO_START_AREA_12 12
#define ECAN_FIFO_START_AREA_11 11
#define ECAN_FIFO_START_AREA_10 10
#define ECAN_FIFO_START_AREA_9 9
#define ECAN_FIFO_START_AREA_8 8
#define ECAN_FIFO_START_AREA_7 7
#define ECAN_FIFO_START_AREA_6 6
#define ECAN_FIFO_START_AREA_5 5
#define ECAN_FIFO_START_AREA_4 4
#define ECAN_FIFO_START_AREA_3 3
#define ECAN_FIFO_START_AREA_2 2
#define ECAN_FIFO_START_AREA_1 1
#define ECAN_FIFO_START_AREA_0 0

//CiRXFnSID  register
#define ECAN_MATCH_EID   0x0008
#define ECAN_MATCH_SID   0x0000

#define ECAN_USE_FIFO   0xF

//CiTRmnCON  TXRX buffer control
#define ECAN_RX_BUFF 0   
#define ECAN_TX_BUFF 1

 
//Data structure for ECAN Data Frame
typedef struct _ECANW0 {
    unsigned IDE: 1;
    unsigned SRR:1;
    unsigned SID:11;
}ECANW0;
typedef struct _ECANW1 {
    unsigned EID17_6: 12;
}ECANW1;

typedef struct _ECANW2 {
    unsigned DLC:4;
    unsigned RB0:1;
    unsigned :3;
    unsigned RB1:1;
    unsigned RTR:1;
    unsigned EID5_0:6;
}ECANW2;

typedef struct _ECANW7 {
    unsigned :8;
    unsigned FILHIT:5;
    unsigned :3;
}ECANW7;



typedef struct _ECANMSG {
   ECANW0 w0;
   ECANW1 w1;
   ECANW2 w2;
   union64 data;
   ECANW7  w7;
}ECANMSG;


void formatStandardDataFrameECAN (ECANMSG* p_ecanmsg, uint16 u16_id, uint8 u8_len);
void formatExtendedDataFrameECAN (ECANMSG* p_ecanmsg, uint32 u32_id, uint8 u8_len);
uint32 getIdExtendedDataFrameECAN (ECANMSG* p_ecanmsg);

#define ECAN_1TIME_HEADER_DEFS
#endif




#ifdef _C2IF
/** Waits until all characters placed in the UART have been sent. */
inline static void CHANGE_MODE_ECAN2(mode) {
  C2CTRL1bits.REQOP = mode;
  while(C2CTRL1bits.OPMODE != mode); 
}

/** Return the number (0-31) of the next ECAN FIFO read buffer
 */
#define GET_FIFO_READBUFFER_ECAN2() (C2FIFO & 0x1F)   

void clrRxFullFlagECAN2(uint8 u8_bufNum);
uint8 getRxFullFlagECAN2(uint8 u8_bufNum);
void clrRxFullOvfFlagsECAN2(void);
void configTxRxBufferECAN2(uint8 u8_bufNum, uint8 u8_type, uint8 u8_priority);
void configRxFilterECAN2(uint8 u8_filtNum, uint32 u32_id, uint8 u8_idType, uint8 u8_bufnum, uint8 u8_maskReg);
void configRxMaskECAN2(uint8 u8_maskNum, uint32 u32_idMask, uint8 u8_idType, uint8 u8_matchType);
void startTxECAN2(uint8 u8_bufNum);
uint8 getTxInProgressECAN2(uint8 u8_bufNum);

#endif

 
#endif // #if (NUM_ECAN_MODS >= 2)
#endif // #define _PIC24_ECAN2_H_



