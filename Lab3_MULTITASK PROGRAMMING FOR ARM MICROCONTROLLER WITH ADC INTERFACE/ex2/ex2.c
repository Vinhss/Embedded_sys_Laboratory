#include <LPC17xx.h>
#include <PIN_LPC17xx.h>
#include <GPIO_LPC17xx.h>
#include <GLCD_Config.h>
#include <Board_GLCD.h>
#include <GLCD_Fonts.h>

#include <Driver_SPI.h>

void delayms(unsigned int milliseconds);

#define Joystick_key_up 23
#define Joystick_key_down 25
#define Joystick_key_left 26
#define Joystick_key_right 24

int static x = 10;
int static y = 10;

int main( void ) {
	LPC_GPIO1->FIODIR &= ~((1<<Joystick_key_up)|(1<<Joystick_key_down)|(1<<Joystick_key_left)|(1<<Joystick_key_right));
	GLCD_Initialize()	;      
	GLCD_ClearScreen();
	GLCD_SetBackgroundColor	(GLCD_COLOR_BLACK)	;
	GLCD_SetBackgroundColor	(GLCD_COLOR_WHITE);
	GLCD_DrawBargraph((uint32_t)x,(uint32_t)y,50,50,20);
	while ( 1 ) {
		
		if((LPC_GPIO1->FIOPIN & (1<<Joystick_key_up))==0)
			{
				delayms(100);
				y-=5;
				GLCD_DrawBargraph((uint32_t)x,(uint32_t)y,50,50,20);
			}
		if((LPC_GPIO1->FIOPIN & (1<<Joystick_key_down))==0)
			{
				delayms(100);
				y+=5;
				GLCD_DrawBargraph((uint32_t)x,(uint32_t)y,50,50,20);
			}
	
		if((LPC_GPIO1->FIOPIN & (1<<Joystick_key_left))==0)
			{
				delayms(100);
				x-=5;
				GLCD_DrawBargraph((uint32_t)x,(uint32_t)y,50,50,20);			
			}
		if((LPC_GPIO1->FIOPIN & (1<<Joystick_key_right))==0)
			{
				delayms(100);
				x+=5;
				GLCD_DrawBargraph((uint32_t)x,(uint32_t)y,50,50,20);		
			}

	}
}

 
void delayms(unsigned int milliseconds)
{
	LPC_TIM0->TCR = 0x02;
	LPC_TIM0->TCR = 0x01;
 
	while(LPC_TIM0->TC < milliseconds);
 
	LPC_TIM0->TCR = 0x00;
}