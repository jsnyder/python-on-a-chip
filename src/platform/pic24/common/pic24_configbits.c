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
 *  This file contains configuration bit settings. Important points on the
 *  syntax used:
 *  - The "functions" below are actually macros which set
 *    these configuration bits. For more details, see
 *    the chip-specific include file, such as <code>p24HJ12GP201.h</code>
 *    in <code>C:\\Program Files\\Microchip\\MPLAB C30\\support\\h</code>,
 *    <!-- Note: extra \\ needed to prevent Doxygen errors, but
 *         these are not actually part of the path.
 *    --> which contain macros (starting on line 2843) to ease setting
 *    configuration bits.
 *  - Instead of ORing bits, AND them: use for example
 *    <code>GSS_OFF & GCP_OFF</code>, NOT
 *    <code>GSS_OFF | GCP_OFF</code>.
 *  - Only one invocation of each config register
 *    should appear in a project, at the top of a C
 *    source file (outside of any function).
 *  - All possible configuration options are listed; the
 *    option currently in use is indicated by an arrow
 *    <code>--></code> next to the setting.
 *  - This file contains configuration settings for some of the
 *    PIC24 family of chips. To change or add support for a new
 *    chip, examine the include-file documentation and read the
 *    FRM documentation on config bits plus the chip-specific
 *    documentation on config bits.
 *
 *   Note on clock choice: The processor is configured to always
 *   start up with the FRC, rather than what it will use after
 *   clock configuration. This guarantees a working clock at
 *   power-up, which can then be changed by the bootloader / user
 *   code / etc.
 */

#include "pic24_all.h"

/// \name PIC24H configuration bits
//@{
#if (defined(__PIC24HJ12GP202__) || \
defined(__PIC24HJ12GP201__) || \
defined(__PIC24HJ32GP202__) || \
defined(__PIC24HJ32GP202__) || \
defined(__PIC24HJ16GP304__) || \
defined(__DOXYGEN__)) // NOTE: DOXYGEN only used for documentation generation


/** FBS: Boot Code Segment Configuration Register
 ** \code
 **   Boot Segment Program Memory:
 **     BSS_HIGH_LARGE_BOOT_CODE  High Security Lar Boot Flash
 **     BSS_LARGE_FLASH_HIGH      High Security Lar Boot Flash
 **     BSS_HIGH_MEDIUM_BOOT_CODE High Security Med Boot Flash
 **     BSS_MEDIUM_FLASH_HIGH     High Security Med Boot Flash
 **     BSS_HIGH_SMALL_BOOT_CODE  High Security Small Boot Flash
 **     BSS_SMALL_FLASH_HIGH      High Security Small Boot Flash
 **     BSS_LARGE_FLASH_STD       Standard Security Lar Boot Flash
 **     BSS_STRD_LARGE_BOOT_CODE  Standard Security Lar Boot Flash
 **     BSS_MEDIUM_FLASH_STD      Standard Security Med Boot Flash
 **     BSS_STRD_MEDIUM_BOOT_CODE Standard Security Med Boot Flash
 **     BSS_SMALL_FLASH_STD       Standard Security Small Boot Flash
 **     BSS_STRD_SMALL_BOOT_CODE  Standard Security Small Boot Flash
 **     BSS_NO_BOOT_CODE          No Boot Segment Program Memory
 **     BSS_NO_FLASH              No Boot Segment Program Memory
 **
 **    Write Protect :
 **     BWRP_WRPROTECT_ON     Enabled
 **  -->BWRP_WRPROTECT_OFF    Disabled
 **      Note: since this is off, size bits above don't matter.
 \endcode
 */
_FBS(BWRP_WRPROTECT_OFF);

/* FSS: Secure Code Segment Configuration Register
** Not present on this chip.
*/

/** FGS: General Code Segment Configuration Register
 ** \code
 **   Code Protect:
 **     GSS_HIGH              high security protect on
 **     GSS_STD               standard security code protect on
 **  -->GSS_OFF              code protect off
 **
 **   Code Protect:
 **     GCP_ON               Enabled
 **  -->GCP_OFF              Disabled
 **     These bits aren't mentioned in the manuals!
 **     Probably a typo in the .h file.
 **
 **   Write Protect:
 **     GWRP_ON              Enabled
 **  -->GWRP_OFF             Disabled
 **
 \endcode
 */
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);


/** FOSCSEL: Oscillator Source Selection Register
 ** \code
 **   Oscillator Source Selection:
 **  -->FNOSC_FRC            Fast RC oscillator
 **     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
 **     FNOSC_PRI            Primary oscillator (XT, HS, EC)
 **     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
 **     FNOSC_SOSC           Secondary oscillator
 **     FNOSC_LPRC           Low power RC oscillator
 **     FNOSC_FRCDIV16       Fast RC oscillator w/ divide by 16
 **     FNOSC_LPRCDIVN        Low power Fast RC oscillator w/divide by N
 **
 **   Two-speed Oscillator Startup :
 **     IESO_ON              Enabled
 **  -->IESO_OFF             Disabled
 **
 \endcode
 */
_FOSCSEL(FNOSC_FRC & IESO_OFF);

/** FOSC: Oscillator Configuration Register
 ** \code
 **   Clock switching and clock monitor:
 **     FCKSM_CSECME         Both enabled
 **  -->FCKSM_CSECMD         Only clock switching enabled
 **     FCKSM_CSDCMD         Both disabled
 **      Clock switching must be enabled to allow a switch
 **      up to the PLL.
 **
 **   Single configuration for remappable I/O:
 **  -->IOL1WAY_OFF          Disabled
 **     IOL1WAY_ON           Enabled
 **
 **   OSC2 Pin function:
 **  -->OSCIOFNC_ON          Digital I/O
 **     OSCIOFNC_OFF         OSC2 is clock O/P
 **      Note: this frees up OSC1 for digitial I/O when
 **      not in HS or XT modes (per POSCMD_SEL).
 **
 **   Oscillator Selection:
 **     Taken from POSCMD_SEL
 **
 \endcode
 */
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_SEL);


/** FWDT: Watchdog Timer Configuration Register
 ** \code
 **   Watchdog Timer:
 **  -->FWDTEN_OFF           Disabled
 **     FWDTEN_ON            Enabled
 **
 **   Windowed WDT:
 **     WINDIS_ON            Enabled
 **  -->WINDIS_OFF           Disabled
 **
 **   Watchdog prescaler:
 **     WDTPRE_PR32          1:32
 **  -->WDTPRE_PR128         1:128
 **
 **   Watchdog postscaler:
 **     WDTPOST_PS1          1:1
 **     WDTPOST_PS2          1:2
 **     WDTPOST_PS4          1:4
 **     WDTPOST_PS8          1:8
 **     WDTPOST_PS16         1:16
 **     WDTPOST_PS32         1:32
 **     WDTPOST_PS64         1:64
 **     WDTPOST_PS128        1:128
 **     WDTPOST_PS256        1:256
 **  -->WDTPOST_PS512        1:512
 **     WDTPOST_PS1024       1:1,024
 **     WDTPOST_PS2048       1:2,048
 **     WDTPOST_PS4096       1:4,096
 **     WDTPOST_PS8192       1:8,192
 **     WDTPOST_PS16384      1:16,384
 **     WDTPOST_PS32768      1:32,768
 **      128*512 = 65536 ~ 0.5 Hz ~ 2 secs (WDT is ~ 32 KHz)
 \endcode
 */
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);

/** FPOR: POR Configuration Register
 ** \code
 **   Power-on Reset Value:
 **     FPWRT_PWR1           Disabled
 **     FPWRT_PWR2           2ms
 **     FPWRT_PWR4           4ms
 **     FPWRT_PWR8           8ms
 **  -->FPWRT_PWR16          16ms
 **     FPWRT_PWR32          32ms
 **     FPWRT_PWR64          64ms
 **     FPWRT_PWR128         128ms
 **
 **   Aletrnate I2C Pins:
 **     ALTI2C_ON            I2C mapped to ASDA1/ASCL1
 **  -->ALTI2C_OFF           I2C mapped to SDA1/SCL1
 **
 \endcode
 */
_FPOR(FPWRT_PWR16 & ALTI2C_OFF);

/** FICD: the debugger configuration word.
 ** \code
 **   JTAG Enable Bit:
 **  -->JTAGEN_OFF           JTAG is disabled
 **     JTAGEN_ON            JTAG is enabled
 **       The one important thing in this
 **       field for normal use is to disable the JTAG mode. If you do not
 **       disable the JTAG mode, then the TDI, TMS, TDO, TCK pins are
 **       not usable which severly limits the GP202/GP201 processors.
 **
 **   ICD communication channel select bits:
 **     ICS_NONE             Reserved
 **     ICS_PGD3             communicate on PGC3/EMUC3 and PGD3/EMUD3
 **     ICS_PGD2             communicate on PGC2/EMUC2 and PGD2/EMUD2
 **  -->ICS_PGD1             communicate on PGC1/EMUC1 and PGD1/EMUD1
 **
 \endcode
 */
_FICD(JTAGEN_OFF & ICS_PGD1);

///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond

#endif // #ifdef (lots of PIC24H devices)
//@}


#if defined(EXPLORER16_100P) && defined(__PIC24HJ256GP610__)
_FBS(BWRP_WRPROTECT_OFF);
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF);
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_SEL);
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
_FPOR(FPWRT_PWR16);
_FICD(JTAGEN_OFF & ICS_PGD1);
#define CONFIG_BITS_DEFINED
#endif


/// \name PIC24F configuration bits
//@{
#if (defined(__PIC24FJ64GA002__) ) || defined(__DOXYGEN__)

/** Register CONFIG1
 ** \code
 **   JTAG:
 **  -->JTAGEN_OFF           Disabled
 **     JTAGEN_ON            Enabled
 **
 **   Code Protect:
 **     GCP_ON               Enabled
 **  -->GCP_OFF              Disabled
 **
 **   Write Protect:
 **     GWRP_ON              Enabled
 **  -->GWRP_OFF             Disabled
 **
 **   Background Debugger:
 **     BKBUG_ON             Enabled
 **  -->BKBUG_OFF            Disabled
 **
 **   Clip-on Emulation mode:
 **     COE_ON               Enabled
 **  -->COE_OFF              Disabled
 **
 **   ICD pins select:
 **     ICS_PGx3             EMUC/EMUD share PGC3/PGD3
 **     ICS_PGx2             EMUC/EMUD share PGC2/PGD2
 **  -->ICS_PGx1             EMUC/EMUD share PGC1/PGD1
 **
 **   Watchdog Timer:
 **  -->FWDTEN_OFF           Disabled
 **     FWDTEN_ON            Enabled
 **
 **   Windowed WDT:
 **     WINDIS_ON            Enabled
 **  -->WINDIS_OFF           Disabled
 **
 **   Watchdog prescaler:
 **     FWPSA_PR32           1:32
 **  -->FWPSA_PR128          1:128
 **
 **   Watchdog postscale:
 **     WDTPS_PS1            1:1
 **     WDTPS_PS2            1:2
 **     WDTPS_PS4            1:4
 **     WDTPS_PS8            1:8
 **     WDTPS_PS16           1:16
 **     WDTPS_PS32           1:32
 **     WDTPS_PS64           1:64
 **     WDTPS_PS128          1:128
 **     WDTPS_PS256          1:256
 **  -->WDTPS_PS512          1:512
 **     WDTPS_PS1024         1:1,024
 **     WDTPS_PS2048         1:2,048
 **     WDTPS_PS4096         1:4,096
 **     WDTPS_PS8192         1:8,192
 **     WDTPS_PS16384        1:16,384
 **     WDTPS_PS32768        1:32,768
 **      128*512 = 65536 ~ 0.5 Hz ~ 2 secs (WDT is ~ 31 KHz)
 \endcode
 */
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & ICS_PGx1 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS512);


/** Register CONFIG2
 ** \code
 **   Two Speed Start-up:
 **  -->IESO_OFF             Disabled
 **     IESO_ON              Enabled
 **
 **   Secondary Oscillator:
 **     SOSCSEL_LPSOSC       Low Power Secondary Oscillator
 **     SOSCSEL_SOSC         Default Secondary Oscillator
 **
 **   Voltage Regulator Standby-mode Wake-up Timer:
 **     WUTSEL_FST           Fast Wake-up timer selected
 **     WUTSEL_LEG           Legacy Wake-up timer selected
 **
 **   Oscillator Selection:
 **  -->FNOSC_FRC            Fast RC oscillator
 **     FNOSC_FRCPLL         Fast RC oscillator w/ divide and PLL
 **     FNOSC_PRI            Primary oscillator (XT, HS, EC)
 **     FNOSC_PRIPLL         Primary oscillator (XT, HS, EC) w/ PLL
 **     FNOSC_SOSC           Secondary oscillator
 **     FNOSC_LPRC           Low power RC oscillator
 **     FNOSC_FRCDIV         Fast RC oscillator with divide
 **
 **   Clock switching and clock monitor:
 **     FCKSM_CSECME         Both enabled
 **  -->FCKSM_CSECMD         Only clock switching enabled
 **     FCKSM_CSDCMD         Both disabled
 **
 **   OSCO/RC15 function:
 **  -->OSCIOFNC_ON          RC15
 **     OSCIOFNC_OFF         OSCO or Fosc/2
 **
 **   RP Register Protection:
 **  -->IOL1WAY_OFF          Unlimited Writes To RP Registers
 **     IOL1WAY_ON           Write RP Registers Once
 **
 **   I2C1 pins Select:
 **     I2C1SEL_SEC          Use Secondary I2C1 pins
 **  -->I2C1SEL_PRI          Use Primary I2C1 pins
 **
 **   Oscillator Selection:
 **     Taken from POSCMD_SEL
 **
\endcode
*/
_CONFIG2(IESO_OFF & FNOSC_FRC & FCKSM_CSECMD & OSCIOFNC_ON & IOL1WAY_OFF & POSCMD_SEL);


///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
//@}
#endif // #ifdef PIC24F processors

#if defined(EXPLORER16_100P) && defined(__PIC24FJ128GA010__)
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & ICS_PGx1 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS512);
_CONFIG2(IESO_OFF & FNOSC_FRC & FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_SEL);
#define CONFIG_BITS_DEFINED
#endif

#if defined(__PIC24FJ64GB002__) ||(__PIC24FJ64GB004__) 
_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF  & ICS_PGx1 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS512);
_CONFIG2(IESO_OFF & FNOSC_FRC & FCKSM_CSECMD & OSCIOFNC_ON & IOL1WAY_OFF & POSCMD_SEL & PLL96MHZ_OFF & PLLDIV_DIV2 );
_CONFIG4(DSWDTPS_DSWDTPSF & DSWDTEN_OFF & DSBOREN_OFF)
#define CONFIG_BITS_DEFINED
///\endcond
#endif

//default config bits, use these if a processor is not defined.
#ifndef CONFIG_BITS_DEFINED
#ifdef __PIC24H__
_FBS(BWRP_WRPROTECT_OFF);
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);

#ifdef RSS_NO_RAM
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF); 
#endif

#ifdef IOL1WAY_OFF
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_SEL);
#else
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL);
#endif
_FOSCSEL(FNOSC_FRC & IESO_OFF);
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
_FPOR(FPWRT_PWR16);
_FICD(JTAGEN_OFF & ICS_PGD1);

#warning Warning: Using default config bit settings in 'common/pic24_configbits.c' for PIC24H family.
#warning edit 'common/pic24_configbits.c' to define bits for your processor!
///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif

#ifdef __PIC24F__

#ifndef BKBUG_OFF
#define BKBUG_OFF 0xFFFF
#endif
#ifndef COE_OFF
#define COE_OFF 0xFFFF
#endif

_CONFIG1(JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_OFF & COE_OFF & ICS_PGx1 & FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS512);

#ifndef IOL1WAY_OFF
#define IOL1WAY_OFF 0xFFFF
#endif
_CONFIG2(IESO_OFF & FNOSC_FRC & FCKSM_CSECMD & OSCIOFNC_ON & IOL1WAY_OFF & POSCMD_SEL);

#warning Using default config bit settings in 'common/pic24_configbits.c' for PIC24F family.
#warning edit 'common/pic24_configbits.c' to define bits for your processor!
///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif

/* The PIC24FK is a subfamily of the PIC24F -- functionality like the PIC24F, but config bits like the PIC24H */
#ifdef __PIC24FK__
_FBS(BSS_OFF & BWRP_OFF);
_FGS(GCP_OFF & GWRP_OFF);

#if  (POSC_FREQ < 100000L) 
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL & POSCFREQ_LS);
#elif (POSC_FREQ > 8000000L) 
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL & POSCFREQ_HS);
#else
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL & POSCFREQ_MS);
#endif


_FOSCSEL(FNOSC_FRC & IESO_OFF);
_FWDT(FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS512);
_FPOR(PWRTEN_ON & MCLRE_ON & I2C1SEL_PRI);
_FICD(BKBUG_OFF & ICS_PGx1);

//new config word for deep sleep operation, set these for your needs
_FDS(DSWDTEN_OFF & DSBOREN_OFF & RTCOSC_LPRC & DSWDTOSC_SOSC);

#warning Warning: Using default config bit settings in 'common/pic24_configbits.c' for PIC24FK family.
#warning edit 'common/pic24_configbits.c' to define bits for your processor!
///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif


#ifdef __dsPIC33F__
_FBS(BWRP_WRPROTECT_OFF);
_FGS(GSS_OFF & GCP_OFF & GWRP_OFF);
_FOSCSEL(FNOSC_FRC & IESO_OFF);
#ifdef RSS_NO_RAM
_FSS(RSS_NO_RAM & SSS_NO_FLASH & SWRP_WRPROTECT_OFF); 
#endif
#ifdef IOL1WAY_OFF
_FOSC(FCKSM_CSECMD & IOL1WAY_OFF & OSCIOFNC_ON & POSCMD_SEL);
#else
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_SEL);
#endif
_FWDT(FWDTEN_OFF & WINDIS_OFF & WDTPRE_PR128 & WDTPOST_PS512);
_FPOR(FPWRT_PWR16);
_FICD(JTAGEN_OFF & ICS_PGD1);
#warning Using default config bit settings in 'common/pic24_configbits.c' for dsPIC33F family.
#warning edit 'common/pic24_configbits.c' to define bits for your processor!
///\cond doxygen_ignore
#define CONFIG_BITS_DEFINED
///\endcond
#endif
#endif


#ifndef CONFIG_BITS_DEFINED
#error Edit 'common/pic24_configbits.c' to add config bits for your processor!
#endif
