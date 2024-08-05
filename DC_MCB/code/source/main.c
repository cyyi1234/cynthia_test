#include "dcmcb.h"

//orignal round down (-0.2 -> -1); custom round down (-0.2 -> 0)
int floor_custom(float num, unsigned int adc_value)
{
    int intPart = (int)num; //integer
    if (num < 0 && num > (-0.5f))  //negative -1<num<0
    {
         intPart= (int)(num+1) ;
    }
		if(intPart>0)
		{			
        return (int)(0.984*adc_value-62.5);
		}
		else
		{			
        return intPart;
		}
}

void Relay_close()
{
	P32 = 1;
	delay_1ms(70);   // delay 70ms
	P32 = 0;
	
	P15=0;
	P55=1;
	//printf("Relay_close\n"); ///debug 
}

void Relay_open()
{
	P33 = 1;    //P3.3 relay_open high pluse
	delay_1ms(70);   // delay 70ms
	P33= 0;
	
	P15=1;
	P55=0;
	//printf("Relay_open\n"); ///debug 
}

unsigned int Is_out_Current(int value)
{
	if((abs(value)<=ACTION_CURRENT) && (0<abs(value)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void main(void)
{
	unsigned int adcValue0, adcValue1,adc_current=0;	
	int RMS_current=0,tmp=0;  //not uesed yet
	unsigned int firstPos=0;

	
  bool howlactive=false; //0---close, 1----open
  bool relayactive=false; //0---close, 1----open
	
  Uart_Init();
	IO_Init();
	ADC_Init();	
	//Led_On();	
	
	//Uart_SendString("hello world!\r\n");
	Set_LGBT_Low();//initial status is low
	delay_1ms(10);
	Relay_open();//initial status is disable	
	
	
	firstPos = ADC_Read(0); //read value in P1.0///debug
	
	while(1)
	{
		adcValue0 = ADC_Read(0); //read value in P1.0 
		adcValue1 = ADC_Read(1); //read value in P1.1,not use
		adc_current = ADC_Read(2); //read value in P1.2
		RMS_current = floor_custom(SLOPE_CURRENT*adc_current-OFFSET_CURRENT,adc_current);
/////debug////
    //printf("v0=%d\n",adcValue0);
		RMS_current+=2;
		////////////////
		
		if((adcValue0<=RELAY_OPEN)&&(howlactive==true))
		{			
			howlactive=false;
			relayactive=false;
		}
		else if((adcValue0>RELAY_CLOSE)&&(howlactive==false))
		{		
	    //just one time for initial
	    if(firstPos>RELAY_CLOSE)
	    {
		    relayactive=true;
				firstPos=0;
			}
	    else
			{
			    howlactive=true;
	    }
		}
		else
		{ 
			firstPos=0;
		}
				
		//set the adc value!!!!!!adcValue0!=lastPos!!!!!!!compare 1 time or not!!!!!!
		if(howlactive==true)
		{	
			if(Is_out_Current(RMS_current)&&(relayactive==false))
			{
					Relay_close();
					Set_LGBT_High();		
				  relayactive=true;
				  delay_1ms(15); //delay 500ms
					Set_LGBT_Low();
					delay_1ms(10);  //delay_1ms 
					Relay_open();					
			}				
		}				
		//delay_100us(1);		
		//delay_1ms(100); //test	
	}
}
