/* Standard copyright does not go in this file because
* of the use of Microchip provided macros, see comments below.
*/
// Documentation for this file. If the \file tag isn't present,
// this file won't be documented.
/** \file
 *  To do.
 */

#ifndef  _PIC24_ADC_H_
#define _PIC24_ADC_H_


/**
 *  Prototype PIC24_ADC library functions here
 *      (functions live in the common/pic24_adc.c file)
 */
uint16 convertADC1(void);
void configADC1_ManualCH0(uint16 u16_Ch0PositiveMask,uint8 u8_autoSampleTime,uint8 u8_Use12bits);
void configADC1_AutoScanIrqCH0(uint16 u16_ch0ScanMask,uint8 u8_autoSampleTime,uint8 u8_12bit);
void configADC1_AutoHalfScanIrqCH0(uint16 u16_ch0ScanMask,uint8 u8_autoSampleTime,uint8 u8_12bit);
void configADC1_Simul4ChanIrq(uint8 u8_ch0Select, uint16 u16_ch123SelectMask, uint16 u16_numTcyMask);

/** Determines if the conversion on AD1 is done.
 *  Returns 1 if the conversion has completed, or 0 if the conversion
 *  has not started or is in progress.
 *  \return True (1) if the conversion has completed, 0 if not.
 */
#define IS_CONVERSION_COMPLETE_ADC1()    AD1CON1bits.DONE

/** Waits until the conversion is completed. */
inline static void WAIT_UNTIL_CONVERSION_COMPLETE_ADC1() {
  while (!IS_CONVERSION_COMPLETE_ADC1())
    doHeartbeat();
}

/** Determines if the AD1 sample-and-hold amplifier(s) are sampling.
 *  Returns 1 if the sample-and-hold amplifier(s) are sampling,
 *  or 0 if sample-and-hold amplifier(s) are holding.
 *  \return True (1) if the sample-and-hold amplifier(s) are sampling, 0 if not.
 */
#define IS_SAMPLING_ADC1()         AD1CON1bits.SAMP
#define SET_SAMP_BIT_ADC1()        AD1CON1bits.SAMP=1

/*
The following macros are a subset of the AND/OR macros found in the
the MPLAB C30/src/peripheral_24F/include/adc.h file and placed
in this header for use solely and exclusively on Microchip
PICmicro Microcontroller products as
specified in the MPLAB C30/src/peripheral_24F/include/adc.h header.

Edits have been made in the comments to correct some
minor typos.
*/
/* AD1CON1 Configuration Bit Definitions */

#define ADC_MODULE_ON               0x8000 /* A/D Converter on */
#define ADC_MODULE_OFF              0x0000 /* A/D Converter off */
#define ADC_MODULE_MASK             (~ADC_MODULE_ON)

#define ADC_IDLE_CONTINUE           0x2000 /* A/D Operate in Idle mode */
#define ADC_IDLE_STOP               0x0000 /* A/D Stop in Idle mode */
#define ADC_IDLE_MASK               (~ADC_IDLE_CONTINUE)

#define ADC_ADDMABM_SCATTER         0x0000 /* DMA buffers are written in Scatter/Gather mode */
#define ADC_ADDMABM_ORDER           0x1000 /* DMA buffers are written in the order of conversion */
#define ADC_ADDMABM_MASK            (~ADC_ADDMABM_ORDER)

#define ADC_12BIT                   0x0400 /* A/D conversion is 12bits instead of 10bits */
#define ADC_10BIT                   0x0000 /* A/D conversion is normal 10bits */

#define ADC_FORMAT_SIGN_FRACT       0x0300 /* A/D data format signed fractional */
#define ADC_FORMAT_FRACT            0x0200 /* A/D data format fractional */
#define ADC_FORMAT_SIGN_INT         0x0100 /* A/D data format signed integer */
#define ADC_FORMAT_INTG             0x0000 /* A/D data format integer */
#define ADC_FORMAT_MASK             (~ADC_FORMAT_SIGN_FRACT)

#define ADC_CLK_AUTO                0x00E0  /* Internal counter ends sampling and starts conversion (Auto convert) */
#define ADC_CLK_MPWM                0x0060  /* MPWM interval ends sampling and starts conversion */
#define ADC_CLK_TMR                 0x0040  /* GP Timer compare ends sampling and starts conversion */
#define ADC_CLK_INT0                0x0020  /* Active transition on INTx ends sampling and starts conversion */
#define ADC_CLK_MANUAL              0x0000  /* Clearing sample (SAMP) bit ends sampling and starts conversion */
#define ADC_CLK_MASK                (~ADC_CLK_AUTO)

#define ADC_SAMPLE_SIMULTANEOUS     0x0008  /* 10bit Only: samples CH0/1 or CH0/1/2/3 simultaneously depending on ADxCON2.CHPS bits */
#define ADC_SAMPLE_INDIVIDUAL       0x0000  /* Samples channels sequentially */

#define ADC_AUTO_SAMPLING_ON        0x0004  /* Sampling begins immediately after last conversion */
#define ADC_AUTO_SAMPLING_OFF       0x0000  /* Sampling begins when SAMP bit is set */
#define ADC_AUTO_SAMPLING_MASK      (~ADC_AUTO_SAMPLING_ON)

#define ADC_SAMP_ON                 0x0002  /* sample / hold amplifiers are sampling */
#define ADC_SAMP_OFF                0x0000 /* sample / hold amplifiers are holding */
#define ADC_SAMP_MASK               (~ADC_SAMP_ON)


/* defines for the ADCON2 register */
#define ADC_VREF_EXT_AVSS           0x2000  /* A/D Voltage reference configuration Vref+ external and Vref- is AVss */
#define ADC_VREF_AVDD_EXT           0x4000  /* A/D Voltage reference configuration Vref+ AVdd and Vref- external */
#define ADC_VREF_EXT_EXT            0x6000  /* A/D Voltage reference configuration both Vref+ and Vref- are external */
#define ADC_VREF_AVDD_AVSS          0x8000  /* A/D Voltage reference configuration Vref+ is AVdd and Vref- is AVss */
#define ADC_VREF_MASK               (~(ADC_VREF_AVDD_AVSS | ADC_VREF_EXT_EXT))/* A/D Voltage reference configuration Vref+ is AVdd and Vref- is AVss */

#define ADC_SCAN_ON                 0x0400  /* A/D Scan Input Selections for CH0 during SAMPLE A */
#define ADC_SCAN_OFF                0x0000  /* A/D Do notScan Input Selections for CH0+ during SAMPLE A */
#define ADC_SCAN_MASK               (~ADC_SCAN_ON)

#define ADC_CONVERT_CH0             0x0000  /* 10bit Only: A/D converts CH0 */
#define ADC_CONVERT_CH01            0x0100  /* 10bit Only: A/D converts CH0, CH1 */
#define ADC_CONVERT_CH0123          0x0300  /* 10bit Only: A/D converts CH0, CH1, CH2, CH3 */

#define ADC_INTR_EACH_CONV          0x0000  /* Interrupts at the completion of conversion of each sample */
#define ADC_INTR_2_CONV             0x0004  /* Interrupts at the completion of conversion of 2 samples */
#define ADC_INTR_3_CONV             0x0008  /* Interrupts at the completion of conversion of 3 samples */
#define ADC_INTR_4_CONV             0x000C  /* Interrupts at the completion of conversion of 4 samples */
#define ADC_INTR_5_CONV             0x0010  /* Interrupts at the completion of conversion of 5 samples */
#define ADC_INTR_6_CONV             0x0014  /* Interrupts at the completion of conversion of 6 samples */
#define ADC_INTR_7_CONV             0x0018  /* Interrupts at the completion of conversion of 7 samples */
#define ADC_INTR_8_CONV             0x001C  /* Interrupts at the completion of conversion of 8 samples */
#define ADC_INTR_9_CONV             0x0020  /* Interrupts at the completion of conversion of 9 samples */
#define ADC_INTR_10_CONV            0x0024  /* Interrupts at the completion of conversion of 10 samples */
#define ADC_INTR_11_CONV            0x0028  /* Interrupts at the completion of conversion of 11 samples */
#define ADC_INTR_12_CONV            0x002C  /* Interrupts at the completion of conversion of 12 samples */
#define ADC_INTR_13_CONV            0x0030  /* Interrupts at the completion of conversion of 13 samples */
#define ADC_INTR_14_CONV            0x0034  /* Interrupts at the completion of conversion of 14 samples */
#define ADC_INTR_15_CONV            0x0038  /* Interrupts at the completion of conversion of 15 samples */
#define ADC_INTR_16_CONV            0x003C  /* Interrupts at the completion of conversion of 16 samples */
#define ADC_INTR_MASK               (~ADC_INTR_16_CONV)

/* BUFM bit defines */
#define ADC_ALT_BUF_ON              0x0002 /* Buffer configured as 2 8-word buffers */
#define ADC_ALT_BUF_OFF             0x0000 /* Buffer configured as 1 16-word buffer */
#define ADC_ALT_BUF_MASK            (~ADC_ALT_BUF_ON)
/* BUFS bit define */
#define ADC_ALT_BUF_STATUS_2        0x0080    /* ADC is 2nd half of buffer, read from 1st half */
#define ADC_ALT_BUF_STATUS_MASK     (~ADC_ALT_BUF_STATUS_MASK)

/* A/D Uses channel input selects for SAMPLE A on first sample and SAMPLE B on next sample */
#define ADC_ALT_INPUT_ON            0x0001 /* alternate between MUXA and MUXB */
/* A/D Always uses channel input selects for SAMPLE A */
#define ADC_ALT_INPUT_OFF           0x0000 /* use MUXA only */
#define ADC_ALT_MASK                (~ADC_ALT_INPUT_ON)

/* defines for ADCON3 register */
#define ADC_CONV_CLK_INTERNAL_RC    0x8000 /* A/D internal RC clock */
#define ADC_CONV_CLK_SYSTEM         0x0000 /* Clock derived from system clock */
#define ADC_CONV_CLK_SOURCE_MASK    (~ADC_CONV_CLK_INTERNAL_RC)

#define ADC_SAMPLE_TIME_0           0x0000 /* A/D Auto Sample Time 0 Tad */
#define ADC_SAMPLE_TIME_1           0x0100 /* A/D Auto Sample Time 1 Tad */
#define ADC_SAMPLE_TIME_2           0x0200 /* A/D Auto Sample Time 2 Tad */
#define ADC_SAMPLE_TIME_3           0x0300 /* A/D Auto Sample Time 3 Tad */
#define ADC_SAMPLE_TIME_4           0x0400 /* A/D Auto Sample Time 4 Tad */
#define ADC_SAMPLE_TIME_5           0x0500 /* A/D Auto Sample Time 5 Tad */
#define ADC_SAMPLE_TIME_6           0x0600 /* A/D Auto Sample Time 6 Tad */
#define ADC_SAMPLE_TIME_7           0x0700 /* A/D Auto Sample Time 7 Tad */
#define ADC_SAMPLE_TIME_8           0x0800 /* A/D Auto Sample Time 8 Tad */
#define ADC_SAMPLE_TIME_9           0x0900 /* A/D Auto Sample Time 9 Tad */
#define ADC_SAMPLE_TIME_10          0x0A00 /* A/D Auto Sample Time 10 Tad */
#define ADC_SAMPLE_TIME_11          0x0B00 /* A/D Auto Sample Time 11 Tad */
#define ADC_SAMPLE_TIME_12          0x0C00 /* A/D Auto Sample Time 12 Tad */
#define ADC_SAMPLE_TIME_13          0x0D00 /* A/D Auto Sample Time 13 Tad */
#define ADC_SAMPLE_TIME_14          0x0E00 /* A/D Auto Sample Time 14 Tad */
#define ADC_SAMPLE_TIME_15          0x0F00 /* A/D Auto Sample Time 15 Tad */
#define ADC_SAMPLE_TIME_16          0x1000 /* A/D Auto Sample Time 16 Tad */
#define ADC_SAMPLE_TIME_17          0x1100 /* A/D Auto Sample Time 17 Tad */
#define ADC_SAMPLE_TIME_18          0x1200 /* A/D Auto Sample Time 18 Tad */
#define ADC_SAMPLE_TIME_19          0x1300 /* A/D Auto Sample Time 19 Tad */
#define ADC_SAMPLE_TIME_20          0x1400 /* A/D Auto Sample Time 20 Tad */
#define ADC_SAMPLE_TIME_21          0x1500 /* A/D Auto Sample Time 21 Tad */
#define ADC_SAMPLE_TIME_22          0x1600 /* A/D Auto Sample Time 22 Tad */
#define ADC_SAMPLE_TIME_23          0x1700 /* A/D Auto Sample Time 23 Tad */
#define ADC_SAMPLE_TIME_24          0x1800 /* A/D Auto Sample Time 24 Tad */
#define ADC_SAMPLE_TIME_25          0x1900 /* A/D Auto Sample Time 25 Tad */
#define ADC_SAMPLE_TIME_26          0x1A00 /* A/D Auto Sample Time 26 Tad */
#define ADC_SAMPLE_TIME_27          0x1B00 /* A/D Auto Sample Time 27 Tad */
#define ADC_SAMPLE_TIME_28          0x1C00 /* A/D Auto Sample Time 28 Tad */
#define ADC_SAMPLE_TIME_29          0x1D00 /* A/D Auto Sample Time 29 Tad */
#define ADC_SAMPLE_TIME_30          0x1E00 /* A/D Auto Sample Time 30 Tad */
#define ADC_SAMPLE_TIME_31          0x1F00 /* A/D Auto Sample Time 31 Tad */
#define ADC_SAMPLE_TIME_MASK        (~ADC_SAMPLE_TIME_31)

/* A/D conversion clock select bit ADCS<7:0>*/
#define ADC_CONV_CLK_256Tcy        0x00FF
#define ADC_CONV_CLK_255Tcy        0x00FE
#define ADC_CONV_CLK_254Tcy        0x00FD
#define ADC_CONV_CLK_253Tcy        0x00FC
#define ADC_CONV_CLK_252Tcy        0x00FB
#define ADC_CONV_CLK_251Tcy        0x00FA
#define ADC_CONV_CLK_250Tcy        0x00F9
#define ADC_CONV_CLK_249Tcy        0x00F8
#define ADC_CONV_CLK_248Tcy        0x00F7
#define ADC_CONV_CLK_247Tcy        0x00F6
#define ADC_CONV_CLK_246Tcy        0x00F5
#define ADC_CONV_CLK_245Tcy        0x00F4
#define ADC_CONV_CLK_244Tcy        0x00F3
#define ADC_CONV_CLK_243Tcy        0x00F2
#define ADC_CONV_CLK_242Tcy        0x00F1
#define ADC_CONV_CLK_241Tcy        0x00F0
#define ADC_CONV_CLK_240Tcy        0x00EF
#define ADC_CONV_CLK_239Tcy        0x00EE
#define ADC_CONV_CLK_238Tcy        0x00ED
#define ADC_CONV_CLK_237Tcy        0x00EC
#define ADC_CONV_CLK_236Tcy        0x00EB
#define ADC_CONV_CLK_235Tcy        0x00EA
#define ADC_CONV_CLK_234Tcy        0x00E9
#define ADC_CONV_CLK_233Tcy        0x00E8
#define ADC_CONV_CLK_232Tcy        0x00E7
#define ADC_CONV_CLK_231Tcy        0x00E6
#define ADC_CONV_CLK_230Tcy        0x00E5
#define ADC_CONV_CLK_229Tcy        0x00E4
#define ADC_CONV_CLK_228Tcy        0x00E3
#define ADC_CONV_CLK_227Tcy        0x00E2
#define ADC_CONV_CLK_226Tcy        0x00E1
#define ADC_CONV_CLK_225Tcy        0x00E0
#define ADC_CONV_CLK_224Tcy        0x00DF
#define ADC_CONV_CLK_223Tcy        0x00DE
#define ADC_CONV_CLK_222Tcy        0x00DD
#define ADC_CONV_CLK_221Tcy        0x00DC
#define ADC_CONV_CLK_220Tcy        0x00DB
#define ADC_CONV_CLK_219Tcy        0x00DA
#define ADC_CONV_CLK_218Tcy        0x00D9
#define ADC_CONV_CLK_217Tcy        0x00D8
#define ADC_CONV_CLK_216Tcy        0x00D7
#define ADC_CONV_CLK_215Tcy        0x00D6
#define ADC_CONV_CLK_214Tcy        0x00D5
#define ADC_CONV_CLK_213Tcy        0x00D4
#define ADC_CONV_CLK_212Tcy        0x00D3
#define ADC_CONV_CLK_211Tcy        0x00D2
#define ADC_CONV_CLK_210Tcy        0x00D1
#define ADC_CONV_CLK_209Tcy        0x00D0
#define ADC_CONV_CLK_208Tcy        0x00CF
#define ADC_CONV_CLK_207Tcy        0x00CE
#define ADC_CONV_CLK_206Tcy        0x00CD
#define ADC_CONV_CLK_205Tcy        0x00CC
#define ADC_CONV_CLK_204Tcy        0x00CB
#define ADC_CONV_CLK_203Tcy        0x00CA
#define ADC_CONV_CLK_202Tcy        0x00C9
#define ADC_CONV_CLK_201Tcy        0x00C8
#define ADC_CONV_CLK_200Tcy        0x00C7
#define ADC_CONV_CLK_199Tcy        0x00C6
#define ADC_CONV_CLK_198Tcy        0x00C5
#define ADC_CONV_CLK_197Tcy        0x00C4
#define ADC_CONV_CLK_196Tcy        0x00C3
#define ADC_CONV_CLK_195Tcy        0x00C2
#define ADC_CONV_CLK_194Tcy        0x00C1
#define ADC_CONV_CLK_193Tcy        0x00C0
#define ADC_CONV_CLK_192Tcy        0x00BF
#define ADC_CONV_CLK_191Tcy        0x00BE
#define ADC_CONV_CLK_190Tcy        0x00BD
#define ADC_CONV_CLK_189Tcy        0x00BC
#define ADC_CONV_CLK_188Tcy        0x00BB
#define ADC_CONV_CLK_187Tcy        0x00BA
#define ADC_CONV_CLK_186Tcy        0x00B9
#define ADC_CONV_CLK_185Tcy        0x00B8
#define ADC_CONV_CLK_184Tcy        0x00B7
#define ADC_CONV_CLK_183Tcy        0x00B6
#define ADC_CONV_CLK_182Tcy        0x00B5
#define ADC_CONV_CLK_181Tcy        0x00B4
#define ADC_CONV_CLK_180Tcy        0x00B3
#define ADC_CONV_CLK_179Tcy        0x00B2
#define ADC_CONV_CLK_178Tcy        0x00B1
#define ADC_CONV_CLK_177Tcy        0x00B0
#define ADC_CONV_CLK_176Tcy        0x00AF
#define ADC_CONV_CLK_175Tcy        0x00AE
#define ADC_CONV_CLK_174Tcy        0x00AD
#define ADC_CONV_CLK_173Tcy        0x00AC
#define ADC_CONV_CLK_172Tcy        0x00AB
#define ADC_CONV_CLK_171Tcy        0x00AA
#define ADC_CONV_CLK_170Tcy        0x00A9
#define ADC_CONV_CLK_169Tcy        0x00A8
#define ADC_CONV_CLK_168Tcy        0x00A7
#define ADC_CONV_CLK_167Tcy        0x00A6
#define ADC_CONV_CLK_166Tcy        0x00A5
#define ADC_CONV_CLK_165Tcy        0x00A4
#define ADC_CONV_CLK_164Tcy        0x00A3
#define ADC_CONV_CLK_163Tcy        0x00A2
#define ADC_CONV_CLK_162Tcy        0x00A1
#define ADC_CONV_CLK_161Tcy        0x00A0
#define ADC_CONV_CLK_160Tcy        0x009F
#define ADC_CONV_CLK_159Tcy        0x009E
#define ADC_CONV_CLK_158Tcy        0x009D
#define ADC_CONV_CLK_157Tcy        0x009C
#define ADC_CONV_CLK_156Tcy        0x009B
#define ADC_CONV_CLK_155Tcy        0x009A
#define ADC_CONV_CLK_154Tcy        0x0099
#define ADC_CONV_CLK_153Tcy        0x0098
#define ADC_CONV_CLK_152Tcy        0x0097
#define ADC_CONV_CLK_151Tcy        0x0096
#define ADC_CONV_CLK_150Tcy        0x0095
#define ADC_CONV_CLK_149Tcy        0x0094
#define ADC_CONV_CLK_148Tcy        0x0093
#define ADC_CONV_CLK_147Tcy        0x0092
#define ADC_CONV_CLK_146Tcy        0x0091
#define ADC_CONV_CLK_145Tcy        0x0090
#define ADC_CONV_CLK_144Tcy        0x008F
#define ADC_CONV_CLK_143Tcy        0x008E
#define ADC_CONV_CLK_142Tcy        0x008D
#define ADC_CONV_CLK_141Tcy        0x008C
#define ADC_CONV_CLK_140Tcy        0x008B
#define ADC_CONV_CLK_139Tcy        0x008A
#define ADC_CONV_CLK_138Tcy        0x0089
#define ADC_CONV_CLK_137Tcy        0x0088
#define ADC_CONV_CLK_136Tcy        0x0087
#define ADC_CONV_CLK_135Tcy        0x0086
#define ADC_CONV_CLK_134Tcy        0x0085
#define ADC_CONV_CLK_133Tcy        0x0084
#define ADC_CONV_CLK_132Tcy        0x0083
#define ADC_CONV_CLK_131Tcy        0x0082
#define ADC_CONV_CLK_130Tcy        0x0081
#define ADC_CONV_CLK_129Tcy        0x0080
#define ADC_CONV_CLK_128Tcy        0x007F
#define ADC_CONV_CLK_127Tcy        0x007E
#define ADC_CONV_CLK_126Tcy        0x007D
#define ADC_CONV_CLK_125Tcy        0x007C
#define ADC_CONV_CLK_124Tcy        0x007B
#define ADC_CONV_CLK_123Tcy        0x007A
#define ADC_CONV_CLK_122Tcy        0x0079
#define ADC_CONV_CLK_121Tcy        0x0078
#define ADC_CONV_CLK_120Tcy        0x0077
#define ADC_CONV_CLK_119Tcy        0x0076
#define ADC_CONV_CLK_118Tcy        0x0075
#define ADC_CONV_CLK_117Tcy        0x0074
#define ADC_CONV_CLK_116Tcy        0x0073
#define ADC_CONV_CLK_115Tcy        0x0072
#define ADC_CONV_CLK_114Tcy        0x0071
#define ADC_CONV_CLK_113Tcy        0x0070
#define ADC_CONV_CLK_112Tcy        0x006F
#define ADC_CONV_CLK_111Tcy        0x006E
#define ADC_CONV_CLK_110Tcy        0x006D
#define ADC_CONV_CLK_109Tcy        0x006C
#define ADC_CONV_CLK_108Tcy        0x006B
#define ADC_CONV_CLK_107Tcy        0x006A
#define ADC_CONV_CLK_106Tcy        0x0069
#define ADC_CONV_CLK_105Tcy        0x0068
#define ADC_CONV_CLK_104Tcy        0x0067
#define ADC_CONV_CLK_103Tcy        0x0066
#define ADC_CONV_CLK_102Tcy        0x0065
#define ADC_CONV_CLK_101Tcy        0x0064
#define ADC_CONV_CLK_100Tcy        0x0063
#define ADC_CONV_CLK_99Tcy         0x0062
#define ADC_CONV_CLK_98Tcy         0x0061
#define ADC_CONV_CLK_97Tcy         0x0060
#define ADC_CONV_CLK_96Tcy         0x005F
#define ADC_CONV_CLK_95Tcy         0x005E
#define ADC_CONV_CLK_94Tcy         0x005D
#define ADC_CONV_CLK_93Tcy         0x005C
#define ADC_CONV_CLK_92Tcy         0x005B
#define ADC_CONV_CLK_91Tcy         0x005A
#define ADC_CONV_CLK_90Tcy         0x0059
#define ADC_CONV_CLK_89Tcy         0x0058
#define ADC_CONV_CLK_88Tcy         0x0057
#define ADC_CONV_CLK_87Tcy         0x0056
#define ADC_CONV_CLK_86Tcy         0x0055
#define ADC_CONV_CLK_85Tcy         0x0054
#define ADC_CONV_CLK_84Tcy         0x0053
#define ADC_CONV_CLK_83Tcy         0x0052
#define ADC_CONV_CLK_82Tcy         0x0051
#define ADC_CONV_CLK_81Tcy         0x0050
#define ADC_CONV_CLK_80Tcy         0x004F
#define ADC_CONV_CLK_79Tcy         0x004E
#define ADC_CONV_CLK_78Tcy         0x004D
#define ADC_CONV_CLK_77Tcy         0x004C
#define ADC_CONV_CLK_76Tcy         0x004B
#define ADC_CONV_CLK_75Tcy         0x004A
#define ADC_CONV_CLK_74Tcy         0x0049
#define ADC_CONV_CLK_73Tcy         0x0048
#define ADC_CONV_CLK_72Tcy         0x0047
#define ADC_CONV_CLK_71Tcy         0x0046
#define ADC_CONV_CLK_70Tcy         0x0045
#define ADC_CONV_CLK_69Tcy         0x0044
#define ADC_CONV_CLK_68Tcy         0x0043
#define ADC_CONV_CLK_67Tcy         0x0042
#define ADC_CONV_CLK_66Tcy         0x0041
#define ADC_CONV_CLK_65Tcy         0x0040
#define ADC_CONV_CLK_64Tcy         0x003F
#define ADC_CONV_CLK_63Tcy         0x003E
#define ADC_CONV_CLK_62Tcy         0x003D
#define ADC_CONV_CLK_61Tcy         0x003C
#define ADC_CONV_CLK_60Tcy         0x003B
#define ADC_CONV_CLK_59Tcy         0x003A
#define ADC_CONV_CLK_58Tcy         0x0039
#define ADC_CONV_CLK_57Tcy         0x0038
#define ADC_CONV_CLK_56Tcy         0x0037
#define ADC_CONV_CLK_55Tcy         0x0036
#define ADC_CONV_CLK_54Tcy         0x0035
#define ADC_CONV_CLK_53Tcy         0x0034
#define ADC_CONV_CLK_52Tcy         0x0033
#define ADC_CONV_CLK_51Tcy         0x0032
#define ADC_CONV_CLK_50Tcy         0x0031
#define ADC_CONV_CLK_49Tcy         0x0030
#define ADC_CONV_CLK_48Tcy         0x002F
#define ADC_CONV_CLK_47Tcy         0x002E
#define ADC_CONV_CLK_46Tcy         0x002D
#define ADC_CONV_CLK_45Tcy         0x002C
#define ADC_CONV_CLK_44Tcy         0x002B
#define ADC_CONV_CLK_43Tcy         0x002A
#define ADC_CONV_CLK_42Tcy         0x0029
#define ADC_CONV_CLK_41Tcy         0x0028
#define ADC_CONV_CLK_40Tcy         0x0027
#define ADC_CONV_CLK_39Tcy         0x0026
#define ADC_CONV_CLK_38Tcy         0x0025
#define ADC_CONV_CLK_37Tcy         0x0024
#define ADC_CONV_CLK_36Tcy         0x0023
#define ADC_CONV_CLK_35Tcy         0x0022
#define ADC_CONV_CLK_34Tcy         0x0021
#define ADC_CONV_CLK_33Tcy         0x0020
#define ADC_CONV_CLK_32Tcy         0x001F
#define ADC_CONV_CLK_31Tcy         0x001E
#define ADC_CONV_CLK_30Tcy         0x001D
#define ADC_CONV_CLK_29Tcy         0x001C
#define ADC_CONV_CLK_28Tcy         0x001B
#define ADC_CONV_CLK_27Tcy         0x001A
#define ADC_CONV_CLK_26Tcy         0x0019
#define ADC_CONV_CLK_25Tcy         0x0018
#define ADC_CONV_CLK_24Tcy         0x0017
#define ADC_CONV_CLK_23Tcy         0x0016
#define ADC_CONV_CLK_22Tcy         0x0015
#define ADC_CONV_CLK_21Tcy         0x0014
#define ADC_CONV_CLK_20Tcy         0x0013
#define ADC_CONV_CLK_19Tcy         0x0012
#define ADC_CONV_CLK_18Tcy         0x0011
#define ADC_CONV_CLK_17Tcy         0x0010
#define ADC_CONV_CLK_16Tcy         0x000F
#define ADC_CONV_CLK_15Tcy         0x000E
#define ADC_CONV_CLK_14Tcy         0x000D
#define ADC_CONV_CLK_13Tcy         0x000C
#define ADC_CONV_CLK_12Tcy         0x000B
#define ADC_CONV_CLK_11Tcy         0x000A
#define ADC_CONV_CLK_10Tcy         0x0009
#define ADC_CONV_CLK_9Tcy          0x0008
#define ADC_CONV_CLK_8Tcy          0x0007
#define ADC_CONV_CLK_7Tcy          0x0006
#define ADC_CONV_CLK_6Tcy          0x0005
#define ADC_CONV_CLK_5Tcy          0x0004
#define ADC_CONV_CLK_4Tcy          0x0003
#define ADC_CONV_CLK_3Tcy          0x0002
#define ADC_CONV_CLK_2Tcy          0x0001
#define ADC_CONV_CLK_1Tcy          0x0000
#define ADC_CONV_CLK_MASK          (~ADC_CONV_CLK_256Tcy)

/* ADxCON4 register */
#define ADC_DMA_BUF_LOC_128         0x0007 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_64          0x0006 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_32          0x0005 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_16          0x0004 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_8           0x0003 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_4           0x0002 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_2           0x0001 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_1           0x0000 /* Allocates words of buffer to each analog input */
#define ADC_DMA_BUF_LOC_MASK        (~ADC_DMA_BUF_LOC_128)

/* ADC1 Input channel 0 select register (AD1CHS0 regsiter) */
#define ADC_CH0_NEG_SAMPLEB_AN1     0x8000  /* CH0 negative input is AN1 */
#define ADC_CH0_NEG_SAMPLEB_VREFN   0x0000  /* CH0 negative input is VREF- */
#define ADC_CH0_NEG_SAMPLEB_MASK    (~ADC_CH0_NEG_SAMPLEB_AN1)

#define ADC_CH0_POS_SAMPLEB_AN15    0x0F00  /* A/D CH0 pos i/p sel for SAMPLE B is AN15 */
#define ADC_CH0_POS_SAMPLEB_AN14    0x0E00  /* A/D CH0 pos i/p sel for SAMPLE B is AN14 */
#define ADC_CH0_POS_SAMPLEB_AN13    0x0D00  /* A/D CH0 pos i/p sel for SAMPLE B is AN13 */
#define ADC_CH0_POS_SAMPLEB_AN12    0x0C00  /* A/D CH0 pos i/p sel for SAMPLE B is AN12 */
#define ADC_CH0_POS_SAMPLEB_AN11    0x0B00  /* A/D CH0 pos i/p sel for SAMPLE B is AN11 */
#define ADC_CH0_POS_SAMPLEB_AN10    0x0A00  /* A/D CH0 pos i/p sel for SAMPLE B is AN10 */
#define ADC_CH0_POS_SAMPLEB_AN9     0x0900  /* A/D CH0 pos i/p sel for SAMPLE B is AN9 */
#define ADC_CH0_POS_SAMPLEB_AN8     0x0800  /* A/D CH0 pos i/p sel for SAMPLE B is AN8 */
#define ADC_CH0_POS_SAMPLEB_AN7     0x0700  /* A/D CH0 pos i/p sel for SAMPLE B is AN7 */
#define ADC_CH0_POS_SAMPLEB_AN6     0x0600  /* A/D CH0 pos i/p sel for SAMPLE B is AN6 */
#define ADC_CH0_POS_SAMPLEB_AN5     0x0500  /* A/D CH0 pos i/p sel for SAMPLE B is AN5 */
#define ADC_CH0_POS_SAMPLEB_AN4     0x0400  /* A/D CH0 pos i/p sel for SAMPLE B is AN4 */
#define ADC_CH0_POS_SAMPLEB_AN3     0x0300  /* A/D CH0 pos i/p sel for SAMPLE B is AN3 */
#define ADC_CH0_POS_SAMPLEB_AN2     0x0200  /* A/D CH0 pos i/p sel for SAMPLE B is AN2 */
#define ADC_CH0_POS_SAMPLEB_AN1     0x0100  /* A/D CH0 pos i/p sel for SAMPLE B is AN1 */
#define ADC_CH0_POS_SAMPLEB_AN0     0x0000 /* A/D CH0 pos i/p sel for SAMPLE B is AN0 */
#define ADC_CH0_POS_SAMPLEB_MASK    (~ADC_CH0_POS_SAMPLEB_AN15)

#define ADC_CH0_NEG_SAMPLEA_AN1     0x0080  /*A/D CH0 neg I/P sel for SAMPLE A is AN1 */
#define ADC_CH0_NEG_SAMPLEA_VREFN   0x0000  /*A/D CH0 neg I/P sel for SAMPLE A is Vrefn */
#define ADC_CH0_NEG_SAMPLEA_MASK    (~ADC_CH0_NEG_SAMPLEA_AN1)

#define ADC_CH0_POS_SAMPLEA_AN15    0x000F  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN15 */
#define ADC_CH0_POS_SAMPLEA_AN14    0x000E  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN14 */
#define ADC_CH0_POS_SAMPLEA_AN13    0x000D  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN13 */
#define ADC_CH0_POS_SAMPLEA_AN12    0x000C  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN12 */
#define ADC_CH0_POS_SAMPLEA_AN11    0x000B  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN11 */
#define ADC_CH0_POS_SAMPLEA_AN10    0x000A  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN10 */
#define ADC_CH0_POS_SAMPLEA_AN9     0x0009  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN9 */
#define ADC_CH0_POS_SAMPLEA_AN8     0x0008  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN8 */
#define ADC_CH0_POS_SAMPLEA_AN7     0x0007  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN7 */
#define ADC_CH0_POS_SAMPLEA_AN6     0x0006  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN6 */
#define ADC_CH0_POS_SAMPLEA_AN5     0x0005  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN5 */
#define ADC_CH0_POS_SAMPLEA_AN4     0x0004  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN4 */
#define ADC_CH0_POS_SAMPLEA_AN3     0x0003  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN3 */
#define ADC_CH0_POS_SAMPLEA_AN2     0x0002  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN2 */
#define ADC_CH0_POS_SAMPLEA_AN1     0x0001  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN1 */
#define ADC_CH0_POS_SAMPLEA_AN0     0x0000  /* A/D Chan 0 pos i/p sel for SAMPLE A is AN0 */
#define ADC_CH0_POS_SAMPLEA_MASK    (~ADC_CH0_POS_SAMPLEA_AN15)

/* ADC1 Input channel 1,2,3 select register (AD1CHS123 register) */
#define ADC_CH123_NEG_SAMPLEB_AN9AN10AN11   0x0600  /* SAMPLE B neg.input for CHs 1,2,3 is AN9,AN10,AN11 */
#define ADC_CH123_NEG_SAMPLEB_AN6AN7AN8     0x0400  /* SAMPLE B neg.input for CHs 1,2,3 is AN6,AN7,AN8 */
#define ADC_CH123_NEG_SAMPLEB_VREFN         0x0000  /* SAMPLE B neg.input for CHs 1,2,3 is VREF- */
#define ADC_CH123_NEG_SAMPLEB_MASK          (~ADC_CH123_NEG_SAMPLEB_AN9_AN10_AN11)

#define ADC_CH123_POS_SAMPLEB_AN3AN4AN5     0x0100  /* SAMPLE B pos.input for CHs 1,2,3 is AN3,AN4,AN5 */
#define ADC_CH123_POS_SAMPLEB_AN0AN1AN2     0x0000  /* SAMPLE B pos.input for CHs 1,2,3 is AN3,AN4,AN5 */
#define ADC_CH123_POS_SAMPLEB_MASK          (~ADC_CH123_POS_SAMPLEB_AN3_AN4_AN5)

#define ADC_CH123_NEG_SAMPLEA_AN9AN10AN11   0x0006  /* SAMPLE A neg.input for CHs 1,2,3 is AN9,AN10,AN11 */
#define ADC_CH123_NEG_SAMPLEA_AN6AN7AN8     0x0004  /* SAMPLE A neg.input for CHs 1,2,3 is AN6,AN7,AN8 */
#define ADC_CH123_NEG_SAMPLEA_VREFN         0x0000  /* SAMPLE A neg.input for CHs 1,2,3 is VREF- */
#define ADC_CH123_NEG_SAMPLEA_MASK          (~ADC_CH123_NEG_SAMPLEA_AN9_AN10_AN11)

#define ADC_CH123_POS_SAMPLEA_AN3AN4AN5     0x0001  /* SAMPLE A pos.input for CHs 1,2,3 is AN3,AN4,AN5 */
#define ADC_CH123_POS_SAMPLEA_AN0AN1AN2     0x0000  /* SAMPLE A pos.input for CHs 1,2,3 is AN3,AN4,AN5 */
#define ADC_CH123_POS_SAMPLEA_MASK          (~ADC_CH123_POS_SAMPLEA_AN3_AN4_AN5)


/*defines for ADxPCFGL register */
#define ENABLE_AN0_ANA              0x0001 /*Enable AN0 in analog mode */
#define ENABLE_AN1_ANA              0x0002 /*Enable AN1 in analog mode */
#define ENABLE_AN2_ANA              0x0004 /*Enable AN2 in analog mode */
#define ENABLE_AN3_ANA              0x0008 /*Enable AN3 in analog mode */
#define ENABLE_AN4_ANA              0x0010 /*Enable AN4 in analog mode */
#define ENABLE_AN5_ANA              0x0020 /*Enable AN5 in analog mode */
#define ENABLE_AN6_ANA              0x0040 /*Enable AN6 in analog mode */
#define ENABLE_AN7_ANA              0x0080 /*Enable AN7 in analog mode */
#define ENABLE_AN8_ANA              0x0100 /*Enable AN8 in analog mode */
#define ENABLE_AN9_ANA              0x0200 /*Enable AN9 in analog mode */
#define ENABLE_AN10_ANA             0x0400 /*Enable AN10 in analog mode */
#define ENABLE_AN11_ANA             0x0800 /*Enable AN11 in analog mode */
#define ENABLE_AN12_ANA             0x1000 /*Enable AN12 in analog mode */
#define ENABLE_AN13_ANA             0x2000 /*Enable AN13 in analog mode */
#define ENABLE_AN14_ANA             0x4000 /*Enable AN14 in analog mode */
#define ENABLE_AN15_ANA             0x8000 /*Enable AN15 in analog mode */

#define ENABLE_ALL_ANA_0_15         0xFFFF /*Enable AN0-AN15 in analog mode */
#define ENABLE_ALL_DIG_0_15         0x0000 /*Enable AN0-AN15 in Digital mode */

/*defines for ADxCSSL register */
#define ADC_SCAN_AN0      0x0001 /*Enable Input Scan AN0 */
#define ADC_SCAN_AN1      0x0002 /*Enable Input Scan AN1 */
#define ADC_SCAN_AN2      0x0004 /*Enable Input Scan AN2 */
#define ADC_SCAN_AN3      0x0008 /*Enable Input Scan AN3 */
#define ADC_SCAN_AN4      0x0010 /*Enable Input Scan AN4 */
#define ADC_SCAN_AN5      0x0020 /*Enable Input Scan AN5 */
#define ADC_SCAN_AN6      0x0040 /*Enable Input Scan AN6 */
#define ADC_SCAN_AN7      0x0080 /*Enable Input Scan AN7 */
#define ADC_SCAN_AN8      0x0100 /*Enable Input Scan AN8 */
#define ADC_SCAN_AN9      0x0200 /*Enable Input Scan AN9 */
#define ADC_SCAN_AN10     0x0400 /*Enable Input Scan AN10 */
#define ADC_SCAN_AN11     0x0800 /*Enable Input Scan AN11 */
#define ADC_SCAN_AN12     0x1000 /*Enable Input Scan AN12 */
#define ADC_SCAN_AN13     0x2000 /*Enable Input Scan AN13 */
#define ADC_SCAN_AN14     0x4000 /*Enable Input Scan AN14 */
#define ADC_SCAN_AN15     0x8000 /*Enable Input Scan AN15 */

#define ENABLE_ALL_INPUT_SCAN       0xFFFF /*Enable Input Scan AN0-AN15 */
#define DISABLE_ALL_INPU_SCAN       0x0000 /*Disable Input Scan AN0-AN15 */

/*defines for ADxCSSH register */
#define ADC_SCAN_AN16     0x0001 /*Enable Input Scan AN16 */
#define ADC_SCAN_AN17     0x0002 /*Enable Input Scan AN17 */
#define ADC_SCAN_AN18     0x0004 /*Enable Input Scan AN18 */
#define ADC_SCAN_AN19     0x0008 /*Enable Input Scan AN19 */
#define ADC_SCAN_AN20     0x0010 /*Enable Input Scan AN20 */
#define ADC_SCAN_AN21     0x0020 /*Enable Input Scan AN21 */
#define ADC_SCAN_AN22     0x0040 /*Enable Input Scan AN22 */
#define ADC_SCAN_AN23     0x0080 /*Enable Input Scan AN23 */
#define ADC_SCAN_AN24     0x0100 /*Enable Input Scan AN24 */
#define ADC_SCAN_AN25     0x0200 /*Enable Input Scan AN25 */
#define ADC_SCAN_AN26     0x0400 /*Enable Input Scan AN26 */
#define ADC_SCAN_AN27     0x0800 /*Enable Input Scan AN27 */
#define ADC_SCAN_AN28     0x1000 /*Enable Input Scan AN28 */
#define ADC_SCAN_AN29     0x2000 /*Enable Input Scan AN29 */
#define ADC_SCAN_AN30     0x4000 /*Enable Input Scan AN30 */
#define ADC_SCAN_AN31     0x8000 /*Enable Input Scan AN31 */

/* Setting the priority of adc interrupt */
#define ADC_INT_PRI_0               0x0000
#define ADC_INT_PRI_1               0x0001
#define ADC_INT_PRI_2               0x0002
#define ADC_INT_PRI_3               0x0003
#define ADC_INT_PRI_4               0x0004
#define ADC_INT_PRI_5               0x0005
#define ADC_INT_PRI_6               0x0006
#define ADC_INT_PRI_7               0x0007

/* enable / disable interrupts */

#define ADC_INT_ENABLE              0x0008
#define ADC_INT_DISABLE             ~ADC_INT_ENABLE

/* ADxCON4  */
#define ADC_1_WORD_PER_INPUT        0
#define ADC_2_WORD_PER_INPUT        1
#define ADC_4_WORD_PER_INPUT        2
#define ADC_8_WORD_PER_INPUT        3
#define ADC_16_WORD_PER_INPUT       4
#define ADC_32_WORD_PER_INPUT       5
#define ADC_64_WORD_PER_INPUT       6
#define ADC_128_WORD_PER_INPUT      7




#endif          // _PIC24_ADC_H_
