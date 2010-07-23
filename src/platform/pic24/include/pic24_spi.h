/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/


// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  SPI module support functions.
 */



#ifndef _PIC24_SPI_H_
#define _PIC24_SPI_H_
/*
The following macros are a subset of the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/spi.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/spi.h header.
*/

/* SPIXCON1: SPIx CONTROL REGISTER 1 */
#define  DISABLE_SCK_PIN        0x1000 /* SCK pin is not used by module */
#define  ENABLE_SCK_PIN         0x0000 /* SCK pin is  used by module */
#define  SCK_PIN_MASK           (~DISABLE_SCK_PIN)

#define  DISABLE_SDO_PIN        0x0800 /* SDO pin is not used by module */
#define  ENABLE_SDO_PIN         0x0000 /* SDO pin is  used by module */
#define  SDO_PIN_MASK           (~DISABLE_SDO_PIN)

#define  SPI_MODE16_ON          0x0400 /* Communication is word wide */
#define  SPI_MODE8_ON           0x0000 /* Communication is byte wide */
#define  SPI_MODE_MASK          (~SPI_MODE16_ON)

#define  SPI_SMP_ON             0x0200 /* Input data sampled at end of data output time */
#define  SPI_SMP_OFF            0x0000 /* Input data sampled at middle of data output time */
#define  SPI_SMP_MASK           (~SPI_SMP_ON)

#define  SPI_CKE_ON             0x0100 /* Transmit happens from active clock state to idle clock state*/
#define  SPI_CKE_OFF            0x0000 /* Transmit happens on transition from idle clock state to active clock state */
#define  SPI_CKE_MASK           (~SPI_CKE_ON)

#define  SLAVE_ENABLE_ON        0x0080 /* Slave Select enbale */
#define  SLAVE_ENABLE_OFF       0x0000 /* Slave Select not used by module */
#define  SLAVE_ENABLE_MASK      (~SLAVE_ENABLE_ON)

#define  CLK_POL_ACTIVE_LOW     0x0040 /* Idle state for clock is high, active is low */
#define  CLK_POL_ACTIVE_HIGH    0x0000 /* Idle state for clock is low, active is high */
#define  CLK_POL_ACTIVE_MASK    (~CLK_POL_ACTIVE_LOW)

#define  MASTER_ENABLE_ON       0x0020 /* Master Mode */
#define  MASTER_ENABLE_OFF      0x0000 /* Slave Mode */
#define  MASTER_ENABLE_MASK     (~MASTER_ENABLE_ON)

#define  SEC_PRESCAL_1_1        0x001c /* Secondary Prescale 1:1   */
#define  SEC_PRESCAL_2_1        0x0018 /* Secondary Prescale 2:1   */
#define  SEC_PRESCAL_3_1        0x0014 /* Secondary Prescale 3:1   */
#define  SEC_PRESCAL_4_1        0x0010/* Secondary Prescale 4:1   */
#define  SEC_PRESCAL_5_1        0x000c /* Secondary Prescale 5:1   */
#define  SEC_PRESCAL_6_1        0x0008/* Secondary Prescale 6:1   */
#define  SEC_PRESCAL_7_1        0x0004 /* Secondary Prescale 7:1   */
#define  SEC_PRESCAL_8_1        0x0000 /* Secondary Prescale 8:1   */
#define  SEC_PRESCAL_MASK       (~SEC_PRESCAL_1_1)

#define  PRI_PRESCAL_1_1        0x0003 /* Primary Prescale 1:1     */
#define  PRI_PRESCAL_4_1        0x0002 /* Primary Prescale 4:1     */
#define  PRI_PRESCAL_16_1       0x0001 /* Primary Prescale 16:1    */
#define  PRI_PRESCAL_64_1       0x0000 /* Primary Prescale 64:1    */
#define  PRI_PRESCAL_MASK       (~PRI_PRESCAL_1_1)

/* SPIxSTAT REGISTER */
#define  SPI_ENABLE             0x8000 /* Enable module */
#define  SPI_DISABLE            0x0000 /* Disable module */
#define  SPI_ENBL_DSBL_MASK     (~SPI_ENABLE)

#define  SPI_IDLE_STOP          0x2000 /* Discontinue module operation in idle mode */
#define  SPI_IDLE_CON           0x0000 /* Continue module operation in idle mode */
#define  SPI_IDLE_MASK          (~SPI_IDLE_STOP)

#define  SPI_RX_OVFLOW          0x0040
#define  SPI_RX_OVFLOW_CLR      0x0000 /* Clear receive overflow bit */

/* SPIxCON2: SPIx CONTROL REGISTER 2 */
#define  FRAME_ENABLE_ON        0x8000 /* Frame SPI support enable */
#define  FRAME_ENABLE_OFF       0x0000 /* Frame SPI support Disable */
#define  FRAME_ENABLE_MASK      (~FRAME_ENABLE_ON)

#define  FRAME_SYNC_INPUT       0x4000 /* Frame sync pulse Input (slave)  */
#define  FRAME_SYNC_OUTPUT      0x0000 /* Frame sync pulse Output (master)*/
#define  FRAME_SYNC_MASK        (~FRAME_SYNC_INPUT)

#define  FRAME_SYNC_ACTIVE_HIGH 0x2000 /* Frame sync pulse Input (slave)  */
#define  FRAME_SYNC_ACTIVE_LOW  0x0000 /* Frame sync pulse Output (master)*/
#define  FRAME_SYNC_POL_MASK    (~FRAME_SYNC_ACTIVE_HIGH)

#define  SPI_FRM_PULSE_FIRST_CLK 0x0002 /* frame pulse coincides with the first bit clock */
#define  SPI_FRM_PULSE_PREV_CLK  0x0000 /* frame pulse precedes the first bit clock */
#define  SPI_FRM_PULSE_MASK     (~SPI_FRM_PULSE_FIRST_CLK)

#define  SPI_ENH_BUFF_ENABLE    0x0001 /* enable enhanced buffer */
#define  SPI_ENH_BUFF_DISABLE   0x0000 /* disable enhanced buffer */
#define  SPI_ENH_BUFF_MASK      (~SPI_ENH_BUFF_ENABLE)

// Only include if this UART exists.
#if (NUM_SPI_MODS >= 1)
uint16 ioMasterSPI1(uint16 u16_c);
#endif


#if (NUM_SPI_MODS >= 2)
uint16 ioMasterSPI2(uint16 u16_c);
#endif


#endif
