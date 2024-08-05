#ifndef __DC_MCB_H_
#define __DC_MCB_H_
#include <stc15.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "uart.h"
#include "adc.h"

#define OFFSET_CURRENT 61.8f //adc voltage value 5v
#define SLOPE_CURRENT 0.972f //adc surrent value 50mA

#define RELAY_OPEN   110 //howl voltage of postion 70V
#define RELAY_CLOSE  125 //voltage of postion 100V
#define ACTION_CURRENT 5//current of the protect line 48A

#define HANDLE_VOL 5 //adc voltage value 5v
#define SEVEOR_CURRENT 50 //adc surrent value 50mA
#define ADC_FLAG  0x10  //ADC finish flag
#define ADC_START   0x08            //ADC start bit

typedef enum 
{ 
	false = 0, 
  true  = 1
} bool;

#endif