#include <lpc17xx.h>
#define PRESCALE (25000-1) //25000 PCLK clock cycles to increment TC by 1 
void initTimer2();
int main(void) 
{
	//SystemInit(); //called by Startup Code before main(), hence no need to call again.
	LPC_GPIO2->FIODIR |= (1<<4); //set P2.4 as output
	initTimer2();
	
	while(1)
	{
		
	}
	//return 0; //normally this won't execute
}

void initTimer2(void)
{
	/*Assuming that PLL0 has been setup with CCLK = 100Mhz and PCLK = 25Mhz.*/
	LPC_SC->PCONP |= (1<<22); //Power up TIM0. By default TIM0 and TIM1 are enabled.
	LPC_SC->PCLKSEL1 &= ~(0x3<<13); //Set PCLK for timer = CCLK/4 = 100/4 (default)
	
	LPC_TIM2->CTCR = 0x0;
	LPC_TIM2->PR = PRESCALE; //Increment LPC_TIM0->TC at every 24999+1 clock cycles
	//25000 clock cycles @25Mhz = 1 mS
	
	LPC_TIM2->MR0 = 3000; //Toggle Time in mS
	LPC_TIM2->MCR |= (1<<0) | (1<<1); // Interrupt & Reset on MR0 match
	LPC_TIM2->TCR |= (1<<1); //Reset Timer0

	NVIC_EnableIRQ(TIMER2_IRQn); //Enable timer interrupt
	
	LPC_TIM2->TCR = 0x01; //Enable timer
}

extern "C" void TIMER2_IRQHandler(void) //Use extern "C" so C++ can link it properly, for C it is not required
{
	LPC_TIM2->IR |= (1<<0); //Clear MR0 Interrupt flag
	LPC_GPIO2->FIOPIN ^= (1<<4); //Toggle LED
}