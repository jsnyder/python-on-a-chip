/*
# This file is Copyright 2006, 2007, 2009 Dean Hall.
#
# This file is part of the Python-on-a-Chip program.
# Python-on-a-Chip is free software: you can redistribute it and/or modify
# it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1.
# 
# Python-on-a-Chip is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# A copy of the GNU LESSER GENERAL PUBLIC LICENSE Version 2.1
# is seen in the file COPYING up one directory from this.
*/


#ifndef __LIBMMB103_H__
#define __LIBMMB103_H__


/*
 * MMB103 Library Header
 */


/** Circuit board versions */
#define MMB103_v1j 1       /**< 3 PCBs made, 1 populated */
#define MMB103_v1m 2       /**< This is a v1j with reworked motor traces */

/** Pick the target circuit board version, from above */
#define MMB103_VER MMB103_v1m

/** Digital input Read latch */
#define DIG_LATCH (*(volatile uint8_t *)0xB800)

/** Dip-switch input Read latch */
#define DIP_LATCH (*(volatile uint8_t *)0xA800)

/**
 * UART Baud Rate Values
 *
 * Pass one of these definitions in the first argument of mmb_init().
 */
#define BAUD_2400 103
#define BAUD_4800 51
#define BAUD_9600 25
#define BAUD_14400 16
#define BAUD_19200 12
#define BAUD_28800 8
#define BAUD_38400 6
#define BAUD_57600 3
#define BAUD_76800 2
#define BAUD_115200 1

/**
 * ADC Divide Values
 *
 * Pass one of the ADC_CK_DIV_* definitions
 * in the second argument of mmb_init()
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


#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define MAX(a,b) (((a) > (b)) ? (a) : (b))

/** Hitach character LCD */
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
#define LCD_DISP_CURS_BLOCK 0x03
#define LCD_DISP_CURS_ULINE 0x02
#define LCD_DISP_CURS_BLINK 0x01
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
#define LCD_LINE(n)         LCD_CURSOR(((n) & 0x02) ? 0x20 : 0x00 \
                                       + ((n) & 0x01) ? 0x40 : 0x00)
/* LCD mini-macros */
#define LCD_ENTRY_DECR      (LCD_ENTRY)
#define LCD_ENTRY_INCR      (LCD_ENTRY | LCD_ENTRY_CURS_INCR)
#define LCD_DISP_OFF        (LCD_DISP)
#define LCD_DISP_ON         (LCD_DISP | LCD_DISP_DISP_ON)
#define LCD_CURS_ULINE      (LCD_DISP | LCD_DISP_DISP_ON | LCD_DISP_CURS_ULINE)
#define LCD_CURS_BLOCK      (LCD_DISP | LCD_DISP_DISP_ON | LCD_DISP_CURS_BLOCK)
#define LCD_CURS_BLINK      /*TBD*/
#define LCD_CURS_LEFT       (LCD_CURS)
#define LCD_CURS_RIGHT      (LCD_CURS | LCD_CURS_SHFT_R)
#define LCD_DISP_LEFT       (LCD_CURS | LCD_CURS_DISP_SHFT)
#define LCD_DISP_RIGHT      (LCD_CURS | LCD_CURS_DISP_SHFT | LCD_CURS_SHFT_R)
#define LCD_MODE_MULTILINE  (LCD_FUNC | LCD_FUNC_8B_DATA | LCD_FUNC_MULTI_LINE)


/**
 * Init the ISRs, system time, SCI, SPI, ADC, PWM, LCD
 * and other peripherals.
 * If any value is 0, don't init it.
 * Clear global vals.
 *
 * @param uart_rate UART baud rate; use defined BAUD_#
 * @param adc_rate adc sample rate; use ORs of _BV(ADPS2..0)
 * @param pwm_rate pwm period
 * @param num_lcd_lines num lines in lcd display
 * @param num_lcd_cols num columns in lcd display
 */
void mmb_init(uint8_t uart_rate,
              uint8_t adc_rate,
              uint8_t pwm_rate,
              uint8_t num_lcd_lines,
              uint8_t num_lcd_cols);

/**
 * Returns the adc value of the given pin
 *
 * @param p adc pin to read (0..7).
 * @return analog value on the pin.
 */
uint8_t mmb_adc_get(uint8_t ch);

/**
 * Returns the masked value on the digital input port.
 *
 * @param p number of bit to get (0..7).
 * @return masked value.
 */
#define mmb_dig_get(p) (uint8_t)((DIG_LATCH & _BV(p)) ? 1 : 0)

/** Returns the combined binary value of all 8 digital input pins */
#define mmb_dig_get_byte() (DIG_LATCH)

/**
 * Returns the binary value of the given dip switch
 * in its native position.
 * (example: if dip3 is high, dipGet(3) == 0x08).
 *
 * @param p dip pin to read (0..7).
 * @return value of the pin.
 */
#define mmb_dip_get(p) (uint8_t)((DIP_LATCH & _BV(p)) ? 1 : 0)

/** Returns the combined binary value of all 8 dip switches */
#define mmb_dip_get_byte() (DIP_LATCH)

/** Initializes the SPI peripheral */
void mmb_spi_init(uint8_t spi_rate);

/**
 * Blocking read of the SPI port.
 *
 * @param void
 * @return uint8_t: character read.
 */
uint8_t mmb_spiGetByte(void);

/**
 * Blocking write to the SPI port,
 *
 * @param c character to send
 */
void mmb_spiPutByte(uint8_t c);

/**
 * Blocking read from the SPI port.
 * Fills the packet, p, with received bytes.
 * Packet space must already be allocated.
 *
 * @param p pointer to empty packet of chars.
 * @param n number of bytes to get.
 */
uint8_t mmb_spiGetByteN(uint8_t *p, uint8_t n);

/**
 * Blocking write to the SPI port.
 * Sends the first n bytes pointed to by p.
 *
 * @param p pointer to full packet of bytes.
 * @param n number of bytes to get.
 */
void mmb_spiPutByteN(uint8_t *p, uint8_t n);

/**
 * Clears the LCD screen and set cursor to home.
 *
 */
void mmb_lcd_clr_scr(void);


/**
 * Set the cursor's position
 *
 * @param line line number.
 * @param col column number.
 */
void mmb_lcd_set_cursor(uint8_t line, uint8_t col);


/**
 * Writes the character, ch, to the LCD
 * in character mode (LCD_RS == 1).
 *
 * @param ch character to print to LCD
 */
void mmb_lcd_print_char(uint8_t ch);

/**
 * Prints the string pointed to by s
 * to the LCD display.
 * The string must be null-terminated.
 * The lcd print line is incremented
 * with wrap-around when a '\n' is encountered.
 *
 * @param s pointer to string
 */
void mmb_lcd_print_str(char *s);

/**
 * @param v8:    value to print in hex
 * prints the 8-bit value in hex
 *          to the LCD display.
 */
void mmb_lcd_print_hex8(uint8_t v8);

/**
 * prints the 16-bit value in hex
 *          to the LCD display.
 * @param val:    value to print in hex
 */
void mmb_lcd_print_hex16(uint16_t v16);

/**
 * Writes the value, val, to the LCD
 * in control mode (LCD_RS == 0).
 *
 * @param val control value to write to LCD
 */
void mmb_lcd_put_ctl(uint8_t val);

/** Prints the title screen with logo to the LCD */
void mmb_lcd_title_screen(void);

/**
 * Sets the 10-bit PWM value for motor A.
 * Speed < 0 indicates reverse.
 * Speed > 0 indicates forward.
 * Larger absolute values indicate higher speed.
 *
 * @param dc_10bit speed and direction (range: -1024...1023)
 */
void mmb_set_mota_pwm(int16_t dc_10bit);

/**
 * Sets the 10-bit PWM value for motor B.
 * Speed < 0 indicates reverse.
 * Speed > 0 indicates forward.
 * Larger absolute values indicate higher speed.
 *
 * @param dc_10bit speed and direction (range: -1024...1023)
 */
void mmb_set_motb_pwm(int16_t dc_10bit);

/** Initializes Timer2 for PWM mode */
void mmb_motc_init(void);

/** Sets the 8-bit PWM value for motor C */
void mmb_set_motc_pwm(uint8_t dc_8b);

/**
 * Sets OC2 to generate a desired frequency
 * in the range 20 - 65535Hz for the given duration.
 * PB7 (pin 17) toggles to generate the tone.
 * WARN: this only works accurately if TICKRATE is 1000.
 *
 * @param freq frequency to generate.
 * @param ms num milliseconds to generate.
 */
void mmb_beep(int16_t freq, int16_t ms);

/** Initialize Timer1 to drive two servos (must not be use Motor A and B) */
void mmb_servo_init(uint8_t enable);

/** 
 * Sets the position of the servo connected to PB5/OC1A.
 *
 * @param pos Position value (0 == full-left, 255 == full-right)
 */
void mmb_set_servo_a(int8_t pos);

/** 
 * Sets the position of the servo connected to PB6/OC1B.
 *
 * @param pos Position value (0 == full-left, 255 == full-right)
 */
void mmb_set_servo_b(int8_t pos);

#endif /* __LIBMMB103_H__ */
