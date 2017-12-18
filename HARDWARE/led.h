#ifndef __LED_H
#define __LED_H	 
#include "sys.h"



#define LED1 PFout(9)
#define LED0 PFout(10)	

#define LED1_ON 	LED1 = 0;
#define LED1_OFF  	LED1 = 1;
#define LED0_ON  	LED0 = 0;	
#define LED0_OFF 	LED0 = 1;	

void LED_Init(void);
	 				    
#endif
