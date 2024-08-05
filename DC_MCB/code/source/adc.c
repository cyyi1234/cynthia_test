#include "adc.h"

void ADC_Init(void)
{
    P1M1 |= 0x07;  // P1.0, P1.1, P1.2 for ADC
    P1M0 |= 0x00;  // P1.0, P1.1, P1.2 for ADC
	  P1ASF = 0x07;                   //set p1 for adc
    ADC_RES = 0;                   //clear high 8 bit
	  
	  CLK_DIV = 0x00;    // set ADC clock
    AUXR1 |= 0x08;     // ADC fast work mode
    
	  ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
	  ADC_CONTR |= 0x40; //enable adc
    delay_1ms(2);                       //ADC 
}

// Read ADC 
unsigned int ADC_Read(unsigned char channel) 
{
    ADC_CONTR = (ADC_CONTR & 0xF8)|(channel & 0x07)|ADC_START; // init ADC cmp,change channel
    _nop_();                       
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  while (!(ADC_CONTR & ADC_FLAG));     //waiting CMP
    ADC_CONTR &= ~ADC_FLAG;                  // clear the finish flag
    return ADC_RES; //return 8 bit.
}
