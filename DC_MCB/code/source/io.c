#include "io.h"

//set p1.3 p1.4 p3.3 p3.2 push-pull mode
void IO_Init(void)
{
    P1M0 |= 0x18; P1M1 &= ~0x18;    
    P3M0 |= 0x0c; P3M1 &= ~0x0c; 	
	  P33=0;
	  P32=0;
}

//turn on p1.5 p5.5 
void Led_On()
{
	P15=0;
	P55=0;
}

#if 0
//turn on p1.5 p5.5 
void Led_Off()
{
	P15=0;
	P55=0;
}
#endif

void Set_LGBT_High()
{
	P13=1;
	P14=1;
}

void Set_LGBT_Low()
{
	P13=0;
	P14=0;
}
