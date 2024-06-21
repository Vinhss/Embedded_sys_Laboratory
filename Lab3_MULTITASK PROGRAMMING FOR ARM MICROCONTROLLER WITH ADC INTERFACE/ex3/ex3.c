#include <LPC17xx.h>
#include <PIN_LPC17xx.h>
#include <GPIO_LPC17xx.h>
#include <GLCD_Config.h>
#include <Board_GLCD.h>
#include <GLCD_Fonts.h>

#include <Driver_SPI.h>

char myString[]={"HEHE_BOIZ"};
int y = 0;
int main(void){
	GLCD_Initialize()	;      
	GLCD_SetFont(&GLCD_Font_16x24)	;
	GLCD_SetBackgroundColor	(GLCD_COLOR_LIGHT_GREY);
	GLCD_SetBackgroundColor	(GLCD_COLOR_WHITE)	;
	for (int i = 0; i < 160; i++) {
			y = y -5;
			GLCD_DrawString	(10,y,myString);
    }
}