/** @file
 * PyMite - A flyweight Python interpreter for 8-bit and larger microcontrollers.
 * Copyright 2002 Dean Hall.  All rights reserved.
 * PyMite is offered through one of two licenses: commercial or open-source.
 * See the LICENSE file at the root of this package for licensing details.
 *
 * some sections based on code (C) COPYRIGHT 2008 STMicroelectronics
 */

#undef __FILE_ID__
#define __FILE_ID__ 0x70

#include <stdio.h>
#include "stm32f10x.h"
#include "platform_config.h"
#include "pm.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void RTC_Configuration(void);

void
RCC_Configuration(void)
{
    SystemInit();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}


void
GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure USARTx_Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_TxPin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    /* Configure USARTx_Rx as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_RxPin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}


void
NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the RTC Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  Configures the RTC.
  * @retval None
  */
void
RTC_Configuration(void)
{
    /* Enable PWR and BKP clocks */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    /* Allow access to BKP Domain */
    PWR_BackupAccessCmd(ENABLE);

    /* Reset Backup Domain */
    BKP_DeInit();

    /* Enable LSE */
    RCC_LSEConfig(RCC_LSE_ON);
    /* Wait till LSE is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
    {}

    /* Select LSE as RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

    /* Enable RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

    /* Set RTC prescaler: set RTC period to 1sec */
    RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
}


/*
 * Retargets the C library printf function to the USART.
 */
int fputc(int ch, FILE *f)
{
    plat_putByte((uint8_t) ch);
    return ch;
}


PmReturn_t
plat_init(void)
{
    USART_InitTypeDef USART_InitStructure;

#ifdef DEBUG
    debug();
#endif

    RCC_Configuration();
    NVIC_Configuration();
    GPIO_Configuration();
    RTC_Configuration();

    USART_InitStructure.USART_BaudRate = UART_BAUD;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure the USARTx */
    USART_Init(USARTx, &USART_InitStructure);

    /* Enable the USARTx */
    USART_Cmd(USARTx, ENABLE);

    return PM_RET_OK;
}


/* TODO: disable the peripherals and interrupts */
PmReturn_t
plat_deinit(void)
{
    return PM_RET_OK;
}


/*
 * Gets a byte from the address in the designated memory space
 * Post-increments *paddr.
 */
uint8_t
plat_memGetByte(PmMemSpace_t memspace, uint8_t const **paddr)
{
    uint8_t b = 0;

    switch (memspace)
    {
        case MEMSPACE_RAM:
        case MEMSPACE_PROG:
            b = **paddr;
            *paddr += 1;
            return b;
        case MEMSPACE_EEPROM:
        case MEMSPACE_SEEPROM:
        case MEMSPACE_OTHER0:
        case MEMSPACE_OTHER1:
        case MEMSPACE_OTHER2:
        case MEMSPACE_OTHER3:
        default:
            return 0;
    }
}


PmReturn_t
plat_getByte(uint8_t *b)
{
    int c;
    PmReturn_t retval = PM_RET_OK;

    while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
    {
    }

    c = (int) USART_ReceiveData(USARTx);
    *b = c & 0xFF;

    if (c > 0xFF)
    {
        PM_RAISE(retval, PM_RET_EX_IO);
    }

    return retval;
}


PmReturn_t
plat_putByte(uint8_t b)
{
    while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
    {
    }

    USART_SendData(USARTx, (uint8_t) (b & 0x1FF));

    return PM_RET_OK;
}


PmReturn_t
plat_getMsTicks(uint32_t *r_ticks)
{
    /* TODO: make access atomic */
    *r_ticks = pm_timerMsTicks;

    return PM_RET_OK;
}


void
plat_reportError(PmReturn_t result)
{
     /* Print error */
    printf("Error:     0x%02X\n", result);
    printf("  Release: 0x%02X\n", gVmGlobal.errVmRelease);
    printf("  FileId:  0x%02X\n", gVmGlobal.errFileId);
    printf("  LineNum: %d\n", gVmGlobal.errLineNum);

    /* Print traceback */
    {
        pPmObj_t pframe;
        pPmObj_t pstr;
        PmReturn_t retval;

        printf("Traceback (top first):\n");

        /* Get the top frame */
        pframe = (pPmObj_t)gVmGlobal.pthread->pframe;

        /* If it's the native frame, print the native function name */
        if (pframe == (pPmObj_t)&(gVmGlobal.nativeframe))
        {

            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)gVmGlobal.nativeframe.nf_func->
                                   f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK)
            {
                printf("  Unable to get native func name.\n");
                return;
            }
            else
            {
                printf("  %s() __NATIVE__\n", ((pPmString_t)pstr)->val);
            }

            /* Get the frame that called the native frame */
            pframe = (pPmObj_t)gVmGlobal.nativeframe.nf_back;
        }

        /* Print the remaining frame stack */
        for (;
             pframe != C_NULL;
             pframe = (pPmObj_t)((pPmFrame_t)pframe)->fo_back)
        {
            /* The last name in the names tuple of the code obj is the name */
            retval = tuple_getItem((pPmObj_t)((pPmFrame_t)pframe)->
                                   fo_func->f_co->co_names, -1, &pstr);
            if ((retval) != PM_RET_OK) break;

            printf("  %s()\n", ((pPmString_t)pstr)->val);
        }
        printf("  <module>.\n");
    }
}
