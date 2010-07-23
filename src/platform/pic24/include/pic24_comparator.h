/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  Macros to support comparator module configuration
 */


#ifndef _PIC24_COMPARATOR_H_
#define _PIC24_COMPARATOR_H_

/*
 *  Changes:
 *  12/1/08  Fixed CMP1_POS_IP_VIN_POS definition 
 */


/*
The following macros are the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/comparator.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/comparator.h header.

Changed the mixed case macros to all uppercase

*/

/*Registers Defaults*/
#define COMP_CVRCON_VAL    				0x0000
#define COMP_CMCON_VAL     				0x0000

#define CMP_IDLE_STOP               	0x8000 /* When device enters Idle mode, module does notgenerate interrupts.Module is still enabled. */
#define CMP_IDLE_CON                	0x0000 /* continue operation in idle mode */
#define CMP_IDLE_MASK               	(~CMP_IDLE_STOP)

#define CMP2_CHANGE_STATE           	0x2000 /* Comparator output changed states */
#define CMP2_NO_CHANGE             	 	0x0000 /* Comparator output did not change states */
#define CMP2_STATE_MASK             	(~CMP2_CHANGE_STATE )

#define CMP1_CHANGE_STATE           	0x1000 /* Comparator output changed states */
#define CMP1_NO_CHANGE              	0x0000 /* Comparator output did not change states */
#define CMP1_ENBL_DSBL_MASK         	(~CMP1_CHANGE_STATE )

#define CMP2_ENABLE                 	0x0800 /* Comparator is enabled */
#define CMP2_DISABLE                	0x0000 /* Comparator is disabled */
#define CMP2_ENBL_DSBL_MASK         	(~CMP2_ENABLE)

#define CMP1_ENABLE                 	0x0400 /* Comparator is enabled */
#define CMP1_DISABLE                	0x0000 /* Comparator is disabled */
#define CMP1_STATE_MASK             	(~CMP1_ENABLE)

#define CMP2_OUTPUT_ENABLE          	0x0200 /* Comparator output driven on the output pad */
#define CMP2_OUTPUT_DISABLE         	0x0000 /* Comparator output is not driven on the output pad */
#define CMP2_OUTPUT_MASK            	(~CMP2_OUTPUT_ENABLE)

#define CMP1_OUTPUT_ENABLE          	0x0100 /* Comparator output driven on the output pad */
#define CMP1_OUTPUT_DISABLE         	0x0000 /* Comparator output is not driven on the output pad */
#define CMP1_OUTPUT_MASK            	(~CMP1_OUTPUT_ENABLE)

#define CMP2_INV_OUTPUT             	0x0020 /* C2 output inverted */
#define CMP2_NORMAL_OUTPUT          	0x0000 /* C2 output not inverted */
#define CMP2_INV_OUTPUT_MASK        	(~CMP2_INV_OUTPUT)

#define CMP1_INV_OUTPUT             	0x0010 /* C1 output inverted */
#define CMP1_NORMAL_OUTPUT          	0x0000 /* C1 output not inverted */
#define CMP1_INV_OUTPUT_MASK        	(~CMP1_INV_OUTPUT)

#define CMP2_NEG_IP_VIN_POS        		0x0008 /* Input is connected to Vin+ */
#define CMP2_NEG_IP_VIN_NEG        		0x0000 /* Input is connected to Vin- */
#define CMP2_NEG_IP_MASK           		(~CMP2_NEG_IP_VIN_POS)

#define CMP2_POS_IP_VIN_POS        		0x0004 /* Input is connected to Vin+ */
#define CMP2_POS_IP_CV_REF         		0x0000 /* Input is connected to Vin- */
#define CMP2_POS_IP_MASK           		(~CMP2_POS_IP_VIN_POS)

#define CMP1_NEG_IP_VIN_POS        		0x0002 /* Input is connected to Vin+ */
#define CMP1_NEG_IP_VIN_NEG        		0x0000 /* Input is connected to Vin- */
#define CMP1_NEG_IP_MASK           		(~CMP1_NEG_IP_VIN_POS)

#define CMP1_POS_IP_VIN_POS        		0x0001 /* Input is connected to Vin+ */
#define CMP1_POS_IP_CV_REF         		0x0000 /* Input is connected to Vin- */
#define CMP1_POS_IP_MASK           		(~CMP1_POS_IP_VIN_POS)

#define CMP_VREF_ENABLE            		0x0080 /* CVREF circuit powered on */
#define CMP_VREF_DISABLE           		0x0000 /* CVREF circuit powered down */
#define CMP1_VREF_MASK             		(~CMP_VREF_ENABLE)

#define CMP_VREF_OUTPUT_ENABLE     		0x0040 /* CVREF voltage level is output on CVREF pin */
#define CMP_VREF_OUTPUT_DISABLE    		0x0000 /* CVREF voltage level is disconnected from CVREF pin */
#define CMP_VREF_OUTPUT_MASK       		(~CMP_VREF_OUTPUT_ENABLE)

#define CMP_VREF_SELECT_24_STEPS   		0x0020 /* 0 to 0.67 CVRSRC, with CVRSRC/24 step size */
#define CMP_VREF_SELECT_32_STEPS   		0x0000 /* 0.25 CVRSRC to 0.75 CVRSRC, with CVRSRC/32 step size */
#define CMP_VREF_STEP_SELECT_MASK  		(~CMP_VREF_SELECT_24_STEPS) /* 0 to 0.67 CVRSRC, with CVRSRC/24 step size */

#define CMP_VRSRC_VREF_VREF        		0x0010 /* Comparator reference source CVRSRC = VREF+ – VREF- */
#define CMP_VRSRC_AVDD_AVSS        		0x0000 /* Comparator reference source CVRSRC = AVDD – AVSS */
#define CMP_VRSRC_MASK             		(~CMP_VRSRC_VREF_VREF)


#define CMP_0P0_CVRR_1      0x0020
#define CMP_0P04_CVRR_1     0x0021
#define CMP_0P08_CVRR_1     0x0022
#define CMP_0P12_CVRR_1     0x0023
#define CMP_0P16_CVRR_1     0x0024
#define CMP_0P20_CVRR_1     0x0025
#define CMP_0P25_CVRR_1     0x0026
#define CMP_0P29_CVRR_1     0x0027
#define CMP_0P33_CVRR_1     0x0028
#define CMP_0P37_CVRR_1     0x0029
#define CMP_0P41_CVRR_1     0x002A
#define CMP_0P45_CVRR_1     0x002B
#define CMP_0P50_CVRR_1     0x002C
#define CMP_0P54_CVRR_1     0x002D
#define CMP_0P58_CVRR_1     0x002E
#define CMP_0P62_CVRR_1     0x002F

#define CMP_0P25_CVRR_0     0x0000
#define CMP_0P28_CVRR_0     0x0001
#define CMP_0P31_CVRR_0     0x0002
#define CMP_0P34_CVRR_0     0x0003
#define CMP_0P37_CVRR_0     0x0004
#define CMP_0P40_CVRR_0     0x0005
#define CMP_0P43_CVRR_0     0x0006
#define CMP_0P46_CVRR_0     0x0007
#define CMP_0P50_CVRR_0     0x0008
#define CMP_0P53_CVRR_0     0x0009
#define CMP_0P56_CVRR_0     0x000A
#define CMP_0P59_CVRR_0     0x000B
#define CMP_0P62_CVRR_0     0x000C
#define CMP_0P65_CVRR_0     0x000D
#define CMP_0P68_CVRR_0     0x000E
#define CMP_0P71_CVRR_0     0x000F


#endif
