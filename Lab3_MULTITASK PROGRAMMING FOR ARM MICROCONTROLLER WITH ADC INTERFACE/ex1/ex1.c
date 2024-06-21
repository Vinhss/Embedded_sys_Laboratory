#include <LPC17xx.h>
#include <PIN_LPC17xx.h>
#include <GPIO_LPC17xx.h>
#include <GLCD_Config.h>
#include <Board_GLCD.h>
#include <GLCD_Fonts.h>
#include <Driver_SPI.h>
#define PRESCALE (25000-1)  // PCLK=50.000.000/50.000 = 1000Hz=> T_PCLK=1ms
void delayms(unsigned int milliseconds);
void Timer1_Init(void);
int x = 50;
int y = 50;
int main( void ) {
	Timer1_Init();
	GLCD_Initialize(); 
	GLCD_SetBackgroundColor	(GLCD_COLOR_GREEN);
	GLCD_ClearScreen();
	
	while ( 1 ) {
		delayms(1000);
		x = x+20;
		GLCD_SetForegroundColor(GLCD_COLOR_BLACK);
		GLCD_DrawRectangle(x,y,50,100);
		delayms(500);
		GLCD_SetForegroundColor(GLCD_COLOR_GREEN);
		GLCD_DrawRectangle(x,y,50,100);
		if(x == 100){
			y += 20;
		}
}
	}
void Timer1_Init(void)
{
	LPC_SC->PCONP |= (1<<2);       // turn on Timer1 module
	LPC_SC->PCLKSEL0 &=~(0x03<<5);//0b010000; systemcore clock/4= 100MHz/4 =25MHz
	LPC_TIM1->PR = PRESCALE;	// 25 000 000/25 000 = 1000Hz => t = 1/1000 = 1ms
	LPC_TIM1->TCR = 0x02;
}
 
void delayms(unsigned int milliseconds)
{
	LPC_TIM1->TCR = 0x02;   // reset counter b1 of TCR =1
	LPC_TIM1->TCR = 0x01;   // enable couter to count
	while(LPC_TIM1->TC < milliseconds);
	LPC_TIM1->TCR = 0x00;
}

