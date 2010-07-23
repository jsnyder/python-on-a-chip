/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/


// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  DMA module support functions.
 */



#ifndef _PIC24_DMA_H_
#define _PIC24_DMA_H_


/* And/OR Macros */
#define DMA_MODULE_ON               0x8000 /* A/D Converter on */
#define DMA_MODULE_OFF              0x0000 /* A/D Converter off */
#define DMA_MODULE_MASK             (~DMA_MODULE_ON)

#define DMA_SIZE_BYTE               0x4000 /* DMA data size is byte */
#define DMA_SIZE_WORD               0x0000 /* DMA data size is word */
#define DMA_SIZE_MASK               (~DMA_SIZE_BYTE);

#define DMA_DIR_WRITE_PERIPHERAL    0x2000 /* Read from DMA RAM address, write to peripheral*/
#define DMA_DIR_READ_PERIPHERAL    0x0000 /* Read from peripheral address, write to DMA RAM*/
#define DMA_DIR_MASK                (~DMA_DIR_WRITE_PERIPHERAL)

#define DMA_INTERRUPT_HALF          0x1000 /* interrupt on half full */
#define DMA_INTERRUPT_FULL          0x0000 /* interrupt on full */
#define DMA_INTERRUPT_MASK          (~DMA_INTERRUPT_HALF)

#define DMA_NULLW_ON                0x0800 /* Null data write to peripheral in addition to DMA RAM write*/
#define DMA_NULLW_OFF               0x0000 /* Normal operation*/
#define DMA_NULLW_MASK              (~DMA_NULLW_ON)

#define DMA_AMODE_PERIPHERAL_INDIRECT 0x0020 /* Peripheral indirect addressing mode*/
#define DMA_AMODE_REGISTER_INDIRECT   0x0010  /* Register indirect without post increment*/
#define DMA_AMODE_REGISTER_POSTINC    0x0000  /* Register indirect with post-incrmenent mode*/
#define DMA_AMODE_MASK             (~DMA_AMODE_PERIPHERAL_INDIRECT)


#define DMA_MODE_ONE_SHOT_PING_PONG      0x0003 /* One-Shot, Ping-Pong modes enabled*/
#define DMA_MODE_CONTINUOUS_PING_PONG    0x0002 /* Continuous Ping-Pong modes enabled*/
#define DMA_MODE_ONE_SHOT                0x0001 /* One-shot Ping-Pong mode disabled*/
#define DMA_MODE_CONTINUOUS              0x0000 /* Continuous, Ping-pong modes disabled */
#define DMA_MODE_MASK              (~DMA_MODE_ONE_SHOT_PING_PONG)


#define DMA_IRQ_INT0				0x0000
#define DMA_IRQ_IC1					0x0001
#define DMA_IRQ_OC1					0x0002
#define DMA_IRQ_IC2					0x0005
#define DMA_IRQ_OC2					0x0006
#define DMA_IRQ_TMR2				0x0007
#define DMA_IRQ_TMR3				0x0008
#define DMA_IRQ_SPI1				0x000A
#define DMA_IRQ_U1RX				0x000B
#define DMA_IRQ_U1TX				0x000C
#define DMA_IRQ_ADC1				0x000D
#define DMA_IRQ_ADC2				0x0015
#define DMA_IRQ_U2RX				0x001E
#define DMA_IRQ_U2TX				0x001F
#define DMA_IRQ_SPI2				0x0021
#define DMA_IRQ_ECAN1RX 			0x0022
#define DMA_IRQ_ECAN2RX				0x0037
#define DMA_IRQ_ECAN1TX				0x0046
#define DMA_IRQ_ECAN2TX				0x0047


#endif
