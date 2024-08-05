#ifndef __ADC_H_
#define __ADC_H_
#include <stc15.h>
#include <intrins.h>
#include <stdio.h> 
#include "uart.h"

// Defination of ADC
#define ADC_FLAG  0x10  //ADC finish flag
#define ADC_START   0x08            //ADC start bit
#define ADC_POWER 0x80  // ADC power regiter 
#define ADC_SPEEDLL 0x00  // ADC control speed 540TIMERS

void ADC_Init(void);
unsigned int ADC_Read(unsigned char channel);

#endif