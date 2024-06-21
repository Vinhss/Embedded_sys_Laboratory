#include "LPC17xx.h"
void light_on(int gpio, int pin)
{
	if(gpio==1)
	{
		LPC_GPIO1->FIOSET = (1<<pin); //Turn ON LED with GPIO 1
	}
	else
	{
		LPC_GPIO2->FIOSET = (1<<pin); //Turn ON LED with GPIO 2
	}
}

void light_off_all(){
	LPC_GPIO1->FIOCLR=0xFFFFFFFF;//turn off all GPIO 1 LED
	LPC_GPIO2->FIOCLR=0xFFFFFFFF;//turn off all GPIO 2 LED
}

void light_off(int gpio,int pin)
{
	if(gpio==1)
	{
		LPC_GPIO1->FIOCLR = ~(1<<pin); //Turn OFF LED with GPIO 1
	}
	else
	{
		LPC_GPIO2->FIOCLR = ~(1<<pin); //Turn OFF LED with GPIO 2
	}
}