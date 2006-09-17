#ifndef __LIBMMB103_H__
#define __LIBMMB103_H__
/**
 * MMB103 Library Header
 *
 * @author  Dean Hall (Dean.Hall@computer.org)
 * @file    libmmb103.h
 * @copyright   Copyright 2002 Dean Hall.  All rights reserved.
 *
 * 2002/10/04   Refresh.
 * 2002/02/20   First.
 */

/***************************************************************
 * Includes
 **************************************************************/

/* avr system headers */
#ifdef __AVR__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

/* headers */
#include "dwh_types.h"



/***************************************************************
 * Configurables
 **************************************************************/

/** PORT: set this to the compiler's inline declaration */
#define INLINE  __inline__

/** Circuit board version */
#define MMB103_v1j          1       /**< alpha: 3 boards made */
#define MMB103_v1m          2       /**< beta: reworked alpha */

/** Pick the target circuit board version, from above */
#define MMB103_VER          MMB103_v1m

/**** SENSORS ****/
/** ADC port where left encoder plugs in */
#define ADC_ENC_L   0
/** ADC port where right encoder plugs in */
#define ADC_ENC_R   1
/** ADC port where frobpot plugs in */
#define ADC_FROB    5
/** ADC port where front left CDS plugs in */
#define ADC_CDS_FL  6
/** ADC port where front right CDS plugs in */
#define ADC_CDS_FR  7



/***************************************************************
 * Constants (hardwired)
 **************************************************************/

/** MCU crystal freq in Hz */
#define CK 4000000L

/**
 * SCI Baud Values
 *
 * Pass one of the BAUD* definitions
 * in the first argument of init()
 * to set the UART baud rate
 * These constants assume a 4MHz XTAL.
 */
#if CK == 4000000L

#define BAUD2400            103     /**< 2400 baud, 0.2% err */
#define BAUD4800            51      /**< 4800 baud, 0.2% err */
#define BAUD9600            25      /**< 9600 baud, 0.2% err */
#define BAUD14400           16      /**< 14.4k baud, 2.1% err */
#define BAUD19200           12      /**< 19.2k baud, 0.2% err */
#define BAUD28800           8       /**< 28.8k baud, 3.7% err */
#define BAUD38400           6       /**< 38.4k baud, 7.5% err */
#define BAUD57600           3       /**< 57.6k baud, 7.8% err */
#define BAUD76800           2       /**< 76.8k baud, 7.8% err */
#define BAUD115200          1       /**< 115.2k baud, 7.8% err */
#else
#error BAUD values only defined for 4MHz Xtal
#endif /* CK=4MHz */

/** ASCII CRLF newline */
#define CRLF                ('\n')  /* ascii carriage return (linefeed) */
/** ASCII ACK acknowledge */
#define ACK                 0x06
/** ASCII BEL bell */
#define BEL                 0x07
/** ASCII BS backspace */
#define BS                  0x08

/** Digital input Read latch */
#define DIG_LATCH           (*(volatile U8 *)0xB800)
/** Dip-switch input Read latch */
#define DIP_LATCH           (*(volatile U8 *)0xA800)
/** LCD data Write latch */
#define LCD_DAT_LATCH       (*(volatile U8 *)0xB800)
/** LCD control Write latch */
#define LCD_CTL_LATCH       (*(volatile U8 *)0x9800)

/**
 * ADC Divide Values
 *
 * Pass one of the ADC_CK_DIV_* definitions
 * in the second argument of init()
 * to prescale the ADC's timer.
 * The ADC takes 15 cycles for one conversion.
 * The sample rate would be 4MHz / 15 / ADC_CK_DIV_?.
 *
 * example: ADC_CK_DIV_16 yields 16.7K samples per second,
 *          divided among 8 channels,
 *          each channel is sampled 2083 times per second.
 */
#define ADC_STOP            0
#define ADC_CK_DIV_2        (_BV(ADPS0))
#define ADC_CK_DIV_4        (_BV(ADPS1))
#define ADC_CK_DIV_8        (_BV(ADPS1) | _BV(ADPS0))
#define ADC_CK_DIV_16       (_BV(ADPS2))
#define ADC_CK_DIV_32       (_BV(ADPS2) | _BV(ADPS0))
#define ADC_CK_DIV_64       (_BV(ADPS2) | _BV(ADPS1))
#define ADC_CK_DIV_128      (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0)) /* 2Ksps */


/**
 * PWM Divide Values
 *
 * Pass one of the PWM_CK_DIV_* definitions
 * in the third parameter of init() to prescale Timer1.
 * Timer1 supplies PWM1B and PWM1B used by MMB103.
 * Assuming 10-bit PWM as set in init().
 * The PWM freq would be 4MHz / 2046 / PWM_CK_DIV_?.
 *
 *      DIV     freq [Hz]
 *      -----------------
 *      1       1955.0
 *      8       244.38
 *      64      30.574
 *      256     7.6369
 *      1024    1.9092
 */
#define PWM_STOP            0
#define PWM_CK_DIV_1        _BV(CS10)                /* 15 KHz */
#define PWM_CK_DIV_8        _BV(CS11)                /* 2 KHz  */
#define PWM_CK_DIV_64       (_BV(CS11) | _BV(CS10))   /* 244 Hz */
#define PWM_CK_DIV_256      _BV(CS12)
#define PWM_CK_DIV_1024     (_BV(CS12) | _BV(CS10))


/**
 * BIT VECTORS
 *
 * For the dipGet and digGet functions,
 * pass the desired logical OR of these values
 */
#define BIT0                _BV(0)
#define BIT1                _BV(1)
#define BIT2                _BV(2)
#define BIT3                _BV(3)
#define BIT4                _BV(4)
#define BIT5                _BV(5)
#define BIT6                _BV(6)
#define BIT7                _BV(7)


/**** LCD ****/
/* LCD ctl pins, grouped by fxn */
#define LCD_CLS             0x01
#define LCD_HOME            0x02
/* entry mode set */
#define LCD_ENTRY           0x04
#define LCD_ENTRY_CURS_INCR 0x02
#define LCD_ENTRY_DISP_SHFT 0x01
/* display ctl */
#define LCD_DISP            0x08
#define LCD_DISP_DISP_ON    0x04
#define LCD_DISP_CURS_ULINE 0x02
#define LCD_DISP_CURS_BLOCK 0x01
/* cursor/display shift */
#define LCD_CURS            0x10
#define LCD_CURS_DISP_SHFT  0x08
#define LCD_CURS_SHFT_R     0x04
/* function set */
#define LCD_FUNC            0x20
#define LCD_FUNC_8B_DATA    0x10
#define LCD_FUNC_MULTI_LINE 0x08
#define LCD_FUNC_FONT_5x10  0x04    /* no effect */
/* set CGRAM addr */
#define LCD_CGRAM(n)        (0x40 + ((n) << 3))
/* set DDRAM addr */
/* these might not work for 4 line displays */
#define LCD_CURSOR(n)       (0x80 + ((n) & 0x7f))
#define LCD_LINE0           LCD_CURSOR(0)
#define LCD_LINE1           LCD_CURSOR(0x40)
#define LCD_LINE(n)         LCD_CURSOR(0x40 * ((n) & 0x03))
/* LCD mini-macros */
#define LCD_ENTRY_DECR      (LCD_ENTRY)
#define LCD_ENTRY_INCR      (LCD_ENTRY | LCD_ENTRY_CURS_INCR)
#define LCD_DISP_OFF        (LCD_DISP)
#define LCD_DISP_ON         (LCD_DISP | LCD_DISP_DISP_ON)
#define LCD_CURS_ULINE      (LCD_DISP | LCD_DISP_DISP_ON | LCD_DISP_CURS_ULINE)
#define LCD_CURS_BLOCK      (LCD_DISP | LCD_DISP_DISP_ON | LCD_DISP_CURS_BLOCK)
#define LCD_CURS_LEFT       (LCD_CURS)
#define LCD_CURS_RIGHT      (LCD_CURS | LCD_CURS_SHFT_R)
#define LCD_DISP_LEFT       (LCD_CURS | LCD_CURS_DISP_SHFT)
#define LCD_DISP_RIGHT      (LCD_CURS | LCD_CURS_DISP_SHFT | LCD_CURS_SHFT_R)
#define LCD_MODE_MULTILINE  (LCD_FUNC | LCD_FUNC_8B_DATA | LCD_FUNC_MULTI_LINE)

/** LCD control latch bit which controls motor port A */
#define MOTOR_A 0x02
/** LCD control latch bit which controls motor port B */
#define MOTOR_B 0x01

/** MotCtl linear correction hysterisis */
#define MOTCTL_HYST 20 /* 20 == 2 tps */
/** MotCtl most significant PWM bit */
#define MOTCTL_STATE_MAX    0x200 /* for 10-bit PWM */


/***************************************************************
 * Macros
 **************************************************************/

/***************************************************************
 * Types
 **************************************************************/

/** struct to hold all of libmmb103's globals */
typedef struct {

    /** system time in millisecs (50 day rollover) */
    volatile U32 sys_toc;

    /** storage for analog vals */
    volatile U8 adc[8];
    /** storage for analog BMA vals */
    volatile U8 adc_bma[8];
    /** Left encoder count */
    volatile S16 encL;
    /** Right encoder count */
    volatile S16 encR;
    /** threshold for left adc encoder */
    U8 adcEncThreshL;
    /** threshold for right adc encoder */
    U8 adcEncThreshR;
    /** Left adc encoder state */
    U8 adcEncStateL : 1;
    /** Right adc encoder state */
    U8 adcEncStateR : 1;

    /** motctl state and successive approx val */
    S16 ctlState;
    /** motctl pwm val on motor B */
    S16 pwmB;
    /** motctl velocity measured on motor B */
    volatile S16 VmeasB;
    /** motctl desired velocity on motor B */
    volatile S16 VsetB;

    /** value on control latch */
    U8 lcd_ctl;
    /** LCD line the cursor is on */
    U8 cur_line;
    /** number of lines on LCD display */
    U8 lcd_lines;


} mmbGlobals_t, *pmmbGlobals_t;


/***************************************************************
 * Global Declarations
 **************************************************************/

/** struct that holds all globals */
extern mmbGlobals_t mmb_glob;


/***************************************************************
 * Function Protos (public)
 **************************************************************/

/**
 * Init the ISRs, system time, SCI, SPI, ADC, PWM, LCD
 * and other peripherals.
 * If any value is 0, don't init it.
 * Clear global vals.
 *
 * @param sci_rate SCI baud rate; use BAUD#
 * @param adc_rate adc sample rate; use ORs of _BV(ADPS2..0)
 * @param pwm_rate pwm period
 * @param lcd_lines num lines in lcd display (not used yet)
 * @return void
 */
void mmb_init(U8 sci_rate,
              U8 adc_rate,
              U8 pwm_rate,
              U8 num_lcd_lines);

/** calibrate encoders */
void mmb_initEnc(void);

/**
 * Returns the adc value of the given pin
 * from the most recent reading performed
 * by the ADC interrupt service routine.
 *
 * @param p adc pin to read (0..7).
 * @return analog value on the pin.
 */
#define mmb_adcGet(p)       (mmb_glob.adc[p])

/**
 * Returns the adc value of the given pin
 * from the binary moving average
 * performed during the ADC interrupt service routine.
 * BMA is defined as:
 * BMA(t) = S(t)/2 + S(t-1)/4 + S(t-2)/8 + ...
 * BMA is an inexpensive low-pass (smoothing) filter.
 *
 * @param p adc pin to read (0..7).
 * @return analog value on the pin.
 */
#define mmb_adcGetBMA(p)    (mmb_glob.adc_bma[p])

/**
 * Returns the masked value on the digital input port.
 *
 * @param p number of bit to get (0..7).
 * @return masked value.
 */
#define mmb_digGet(p)       (DIG_LATCH & _BV(p))

/**
 * Returns the combined binary value
 * of all 8 digital input pins.
 *
 * @param none.
 * @return value of the port.
 */
#define mmb_digGetByte()    (DIG_LATCH)

/**
 * Returns the binary value of the given dip switch
 * in its native position.
 * (example: if dip3 is high, dipGet(3) == 0x08).
 *
 * @param p dip pin to read (0..7).
 * @return value of the pin.
 */
#define mmb_dipGet(p)       (DIP_LATCH & _BV(p))

/**
 * Returns the combined binary value
 * of all 8 dip switches.
 *
 * @return value of the dips.
 */
#define mmb_dipGetByte()    (DIP_LATCH)

/**
 * Returns the number of milliseconds 
 * since mmb_init() was called.
 *
 * @return milliseconds since mmb_init() was called.
 */
#define mmb_toc()           (mmb_glob.sys_toc)

/**
 * Blocking read of the SCI port.
 *
 * @return character read; or 0 on framing error.
 */
U8 mmb_sciGetByte(void);

/**
 * Blocking write to the SCI port.
 *
 * @param c character to send.
 * @return void
 */
void mmb_sciPutByte(U8 c);

/**
 * Blocking write to the SCI port,
 * of the null-terminated string.
 *
 * @param s pointer to null-term string.
 * @return void
 */
void mmb_sciPutStr(P_U8 s);

/**
 * Blocking read of the SPI port.
 *
 * @param void
 * @return U8: character read.
 */
U8 mmb_spiGetByte(void);

/**
 * Blocking write to the SPI port,
 *
 * @param c character to send
 * @return void
 */
void mmb_spiPutByte(U8 c);

/**
 * Blocking read from the SPI port.
 * Fills the packet, p, with received bytes.
 * Packet space must already be allocated.
 *
 * @param p pointer to empty packet of chars.
 * @param n number of bytes to get.
 * @return void
 */
U8 mmb_spiGetByteN(P_U8 p, U8 n);

/**
 * Blocking write to the SPI port.
 * Sends the first n bytes pointed to by p.
 *
 * @param p pointer to full packet of bytes.
 * @param n number of bytes to get.
 * @return void
 */
void mmb_spiPutByteN(P_U8 p, U8 n);

/**
 * Clears the LCD screen and set cursor to home.
 *
 * @return void
 */
void mmb_lcdClrScr(void);


/**
 * Set cursor to the given line number.
 *
 * @param n line number.
 * @return void
 */
void mmb_lcdSetLine(U8 n);


/**
 * Writes the character, ch, to the LCD
 * in character mode (LCD_RS == 1).
 *
 * @param ch character to print to LCD
 * @return void
 */
void mmb_lcdPrintChar(U8 ch);

/**
 * Prints the string pointed to by s
 * to the LCD display.
 * The string must be null-terminated.
 * The lcd print line is incremented
 * with wrap-around when a '\n' is encountered.
 *
 * @param s pointer to string
 * @return void
 */
void mmb_lcdPrintStr(P_U8 s);

/**
 * @param v8:    value to print in hex
 * prints the 8-bit value in hex
 *          to the LCD display.
 * @return void
 */
void mmb_lcdPrintHex8(U8 v8);

/**
 * prints the 16-bit value in hex
 *          to the LCD display.
 * @param val:    value to print in hex
 * @return void
 */
void mmb_lcdPrintHex16(U16 v16);

/**
 * Writes the value, val, to the LCD
 * in control mode (LCD_RS == 0).
 *
 * @param val control value to write to LCD
 * @return void
 */
void mmb_lcdPutCtl(U8 val);

/**
 * print the title screen to the LCD.
 *
 * "MonkeeProject on MMB103v1m" with logo.
 */
void mmb_lcdTitleScreen(void);

/**
 * Sets the PWM value for motor A.
 * Speed < 0 indicates reverse.
 * Speed > 0 indicates forward.
 * Larger absolute values indicate higher speed.
 *
 * @param speed speed and direction (range: -1024...1023)
 * @return void
 */
void mmb_pwmA(S16 pwm);

/**
 * Sets the PWM value for motor B.
 * Speed < 0 indicates reverse.
 * Speed > 0 indicates forward.
 * Larger absolute values indicate higher speed.
 *
 * @param speed speed and direction (range: -1024...1023)
 * @return void
 */
void mmb_pwmB(S16 pwm);

/** set motor B velocity */
void mmb_velB(S16 vset);

/**
 * Blocking wait for desired number of milliseconds.
 * Does NOT put CPU in a low-power mode.
 * WARN: this only works accurately if TICKRATE is 1000.
 *
 * @param ms milliseconds to wait
 * @return void
 */
void mmb_sleepms(S16 ms);

/**
 * Sets OC2 to generate a desired frequency
 * in the range 20 - 65535Hz for the given duration.
 * PB7 (pin 17) toggles to generate the tone.
 * WARN: this only works accurately if TICKRATE is 1000.
 *
 * @param freq frequency to generate.
 * @param ms num milliseconds to generate.
 * @return void
 */
void mmb_beep(S16 freq, S16 ms);

/**
 * Toggles the given pin on the given port for the
 * given number of times.  The wiggle freq is roughly
 * 1Hz, but depends on TICKRATE.
 *
 * @param port CPU port of pin to wiggle.
 * @param pin Number of pin to wiggle (0..7).
 * @param n Number of times to toggle.
 * @return void
 */
void mmb_wiggle(U8 port, U8 pin, U8 n);

#endif /* __LIBMMB103_H__ */
