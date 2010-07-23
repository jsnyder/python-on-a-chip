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
*  Implementation of analog-to-digital converter functions prototyped in pic24_adc.h
 */

#include "pic24_all.h"
#include <stdio.h>   //for NULL definition

/*********************************
 * Function private to this file *
 *********************************/


/*********************************************************
 * Public functions intended to be called by other files *
 *********************************************************/

/** Performs an ADC conversion (assumes ADC is initialized properly
 *  to return integer results.
 *  \return Integer value (10- or 12-bit, depending on ADC configuration)
 *          corresponding to the ADC conversion result.
 */
uint16 convertADC1(void) {
  uint8 u8_wdtState;

  sz_lastTimeoutError = "convertADC1()";
  u8_wdtState = _SWDTEN;                  //save WDT state
  _SWDTEN = 1;                            //enable WDT since we block
  SET_SAMP_BIT_ADC1();                    //start sampling
  __delay32(1);                           //takes one clock to clear previous DONE flag, delay before checking.
  WAIT_UNTIL_CONVERSION_COMPLETE_ADC1();  //wait for conversion to finish
  _SWDTEN = u8_wdtState;                  //restore WDT
  sz_lastTimeoutError = NULL;             //reset error message
  return(ADC1BUF0);
}

/** Configures ADC1 to perform 10-/12-bit conversion on a single channel via
 *  CH0.  The sampling is done against the AVDD and AVSS references and
 *  using the internal ADC clock to conserve timer resourses.  User can
 *  initiate this manual sampling+conversion by setting the SAMP bit nin
 *  AD1CON1.  When the DONE bit in AD1CON1 goes high, the conversion is
 *  done.
 *  \param u16_ch0PositiveMask Mask to select the single analog input to
 *          convert.  See AD1CHS0 register and associated <i>defines</i>s in
 *          pic24_adc.h
 *  \param u8_autoSampleTime Number of <i>T</i><sub>AD</sub> periods for
 *          sampling the signal.  This value must be 0-31.  If greater than
 *          31, then 31<i>T</i><sub>AD</sub> will be used.
 *  \param u8_use12bit If TRUE, set up the ADC into 12 bit mode, else
 *          use the 10 bit mode.
 */
void configADC1_ManualCH0(uint16 u16_ch0PositiveMask,      \
                          uint8 u8_autoSampleTime,         \
                          uint8 u8_use12bit) {

  if (u8_autoSampleTime > 31) u8_autoSampleTime=31;
  AD1CON1bits.ADON = 0;   // turn off ADC (changing setting while ADON is not allowed)

  /** Configure the internal ADC **/
  AD1CON1 = ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF;
#ifdef _AD12B
  if (u8_use12bit)
    AD1CON1bits.AD12B = 1;
  else
    AD1CON1bits.AD12B = 0;
#endif
  AD1CON3 = ADC_CONV_CLK_INTERNAL_RC | (u8_autoSampleTime<<8);
  AD1CON2 = ADC_VREF_AVDD_AVSS;
#if (defined(__PIC24H__)|| defined(__dsPIC33F__))
  AD1CHS0 = ADC_CH0_NEG_SAMPLEA_VREFN | u16_ch0PositiveMask;
#else
  AD1CHS  = ADC_CH0_NEG_SAMPLEA_VREFN | u16_ch0PositiveMask;
#endif
  AD1CON1bits.ADON = 1;   //turn on the ADC
}

/** Configures ADC1 to perform conversions over a number of scanned
 *  channels to CH0.  The sampling is done against the AVDD and AVSS references
 *  and  using the internal ADC clock to conserve timer resourses.
 *  Samples are obtained continuously once sampling begins.  Triggers ADC
 *  completion interrupts every u8_NumChannels conversion cycles.  Results
 *  are written to the first u8_NumChannels locations in the 16 word ADCxBUFn
 *  registers.
 *
 *  Sampling+conversion will start automatically when ADC is turned on.
 *
 *  User must provide ISR to copy the 1-16 ADC results from ADC1BUFn before
 *  the next conversion completes. See Chapter 11 in the book for an example
 *  (adc7scan1 project).
 *
 *  \param u16_ch0ScanMask A bit-mask to select the analog inputs to scan over
 *          and convert.  See AD1CSSL register and associated <i>defines</i>s in
 *          pic24_adc.h
 *  \param u8_autoSampleTime Number of <i>T</i><sub>AD</sub> periods for
 *          sampling the signal.  This value must be 0-31.  If greater than
 *          31, then 31<i>T</i><sub>AD</sub> will be used.
 *  \param u8_use12bit If TRUE, set up the ADC into 12 bit mode, else
 *          use the 10 bit mode.
 */
void configADC1_AutoScanIrqCH0(uint16   u16_ch0ScanMask, \
                               uint8    u8_autoSampleTime, \
                               uint8    u8_use12bit) {
  uint8     u8_i, u8_nChannels=0;
  uint16    u16_mask = 0x0001;

  // compute the number of Channels the user wants to scan over
  for (u8_i=0; u8_i<16; u8_i++) {
    if (u16_ch0ScanMask & u16_mask)
      u8_nChannels++;
    u16_mask<<=1;
  } //end for

  if (u8_autoSampleTime > 31) u8_autoSampleTime=31;

  AD1CON1bits.ADON = 0;   // turn off ADC (changing setting while ADON is not allowed)
  /** Configure the internal ADC **/
  AD1CON1 = ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON;
#ifdef _AD12B
  if (u8_use12bit)
    AD1CON1bits.AD12B = 1;
  else
    AD1CON1bits.AD12B = 0;
#endif
  AD1CON3 = ADC_CONV_CLK_INTERNAL_RC | (u8_autoSampleTime<<8);
  AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_CONVERT_CH0 | ADC_SCAN_ON | ((u8_nChannels-1)<<2);
#if (defined(__PIC24H__)|| defined(__dsPIC33F__))
  AD1CHS0 = ADC_CH0_NEG_SAMPLEA_VREFN;
#else
  AD1CHS = ADC_CH0_NEG_SAMPLEA_VREFN;
#endif
  AD1CSSL = u16_ch0ScanMask;

  _AD1IP = 7;             // set AD1 interrupt priority
  _AD1IF = 0;             // clear AD1 interrupt flag
  _AD1IE = 1;             // ENABLE AD1 interrupt

  AD1CON1bits.ADON = 1;   // turn on the ADC
}


/** Configures ADC1 to perform conversions over a number of scanned
 *  channels to CH0.  The sampling is done against the AVDD and AVSS references
 *  and  using the internal ADC clock to conserve timer resourses.
 *  Samples are obtained continuously once sampling begins.  Triggers ADC
 *  completion interrupts every <i>N</i> conversion cycles, where <i>N</i> is
 *  the number of bits set in the scan channel mask argument u16_ch0ScanMask.
 *  Results are written to the first u8_NumChannels locations in the 8 word
 *  <b>alternating halves</b> of the 16 word ADCxBUFn registers.
 *
 *  User ISR must check the AD1CON2.BUFS bit when responding to copy the 8
 *  words from the correct half of the ADC1BUFn register array.  See Chapter
 *  11 in the book for an example.  (adc7scan2 project)
 *
 *  Sampling+conversion will start automatically when ADC is turned on.
 *
 *  \param u16_ch0ScanMask A bit-mask to select the analog inputs to scan over
 *          and convert.  See AD1CSSL register and associated <i>defines</i>s in
 *          pic24_adc.h
 *  \param u8_autoSampleTime Number of <i>T</i><sub>AD</sub> periods for
 *          sampling the signal.  This value must be 0-31.  If greater than
 *          31, then 31<i>T</i><sub>AD</sub> will be used.
 *  \param u8_use12bit If TRUE, set up the ADC into 12 bit mode, else
 *          use the 10 bit mode.
 */
void configADC1_AutoHalfScanIrqCH0(uint16   u16_ch0ScanMask, \
                                   uint8    u8_autoSampleTime, \
                                   uint8    u8_use12bit) {
  uint8     u8_i, u8_nChannels=0;
  uint16    u16_mask = 0x0001;

  // compute the number of Channels the user wants to scan over
  for (u8_i=0; u8_i<16; u8_i++) {
    if (u16_ch0ScanMask & u16_mask)
      u8_nChannels++;
    u16_mask<<=1;
  } //end for

  if (u8_autoSampleTime > 31) u8_autoSampleTime=31;

  AD1CON1bits.ADON = 0;   // turn off ADC (changing setting while ADON is not allowed)
  /** Configure the internal ADC **/
  AD1CON1 = ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON;
#ifdef _AD12B
  if (u8_use12bit)
    AD1CON1bits.AD12B = 1;
  else
    AD1CON1bits.AD12B = 0;
#endif
  AD1CON3 = ADC_CONV_CLK_INTERNAL_RC | (u8_autoSampleTime<<8);
  AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_CONVERT_CH0 | ADC_ALT_BUF_ON | ADC_SCAN_ON | ((u8_nChannels-1)<<2);
#if (defined(__PIC24H__)|| defined(__dsPIC33F__))
  AD1CHS0 = ADC_CH0_NEG_SAMPLEA_VREFN;
#else
  AD1CHS  = ADC_CH0_NEG_SAMPLEA_VREFN;
#endif
  AD1CSSL = u16_ch0ScanMask;

  _AD1IP = 7;             // set AD1 interrupt priority
  _AD1IF = 0;             // clear AD1 interrupt flag
  _AD1IE = 1;             // ENABLE AD1 interrupt

  AD1CON1bits.ADON = 1;   // turn on the ADC
}


/** Configures ADC1 to perform simultaneous sampling and (sequential) 10bit
 *  conversion on four channels.
 *  Sampling is done against the AVDD and AVSS references.  Sample duration
 *  is determined by the Timer2/3.  Conversion clock is created from the
 *  internal system instruction clock.  This means that this ADC configuration
 *  can NOT be used for sleeping ADC operations.
 *
 *  ADC completion interrupts notify user when data is ready.  Our four channel
 *  conversion values are written into the alternative halves of the ADC1BUF<i>n</i>
 *  registers.  ADC ISR must
 *  "restart" the sample (by setting  AD1CON1.SAMP bit) before exit.
 *  Sampling will end and conversion will begin on the next Timer2/3 trigger.
 *  Conversion values are written into
 *  the alternative halves of the ADC1BUF<i>n</i> registers.
 *
 *  Sampling starts when AD1CON1.SAMP bit is written by main.
 *
 *  User must ........ See Chapter 11 in the book for an example
 *  (adc4simul project).
 *
 *  \param u8_ch0Select   The number of the AN<i>x</i> channel to sample on
 *          CH0 sample-and-hold amplifier.  This pin can be the same as a
 *          pin sampled on channels 1, 2, and 3.  (See next argument.)
 *  \param u16_ch123SelectMask A bit-mask to select the analog inputs to for
 *          channels 1,2, and 3.  See AD1CHS123 register and associated
 *          <i>defines</i>s in pic24_adc.h
 *  \param u16_numTcyMask A bit-mask to select the number of T<sub>CY</sub>
 *          periods used to create one T<sub>CY</sub> period.  Note that
 *          T<sub>AD</sub> > 75ns.  See AD1CON3 register and associated
 *          <i>defines</i>s in pic24_adc.h
 */
void configADC1_Simul4ChanIrq(uint8    u8_ch0Select, \
                              uint16   u16_ch123SelectMask, \
                              uint16   u16_numTcyMask ) {

  AD1CON1bits.ADON = 0;   // turn off ADC (changing setting while ADON is not allowed)
  /** Configure the internal ADC **/
  AD1CON1 = ADC_CLK_TMR | ADC_SAMPLE_SIMULTANEOUS;
  AD1CON3 = (u16_numTcyMask & 0x00FF);
  AD1CON2 = ADC_VREF_AVDD_AVSS | ADC_CONVERT_CH0123 | ADC_ALT_BUF_ON;
#if (defined(__PIC24H__)|| defined(__dsPIC33F__))
  AD1CHS0 = ADC_CH0_NEG_SAMPLEA_VREFN | (u8_ch0Select & 0x1F);
  AD1CHS123 = u16_ch123SelectMask;
#else
  AD1CHS = ADC_CH0_NEG_SAMPLEA_VREFN | (u8_ch0Select & 0x1F);
#endif
  AD1CSSL = 0;

  _AD1IP = 7;             // set AD1 interrupt priority
  _AD1IF = 0;             // clear AD1 interrupt flag
  _AD1IE = 1;             // ENABLE AD1 interrupt

  AD1CON1bits.ADON = 1;   // turn on the ADC
}




