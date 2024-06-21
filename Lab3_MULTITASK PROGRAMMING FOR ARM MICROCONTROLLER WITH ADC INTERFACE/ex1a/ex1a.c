#include <LPC17xx.h>
#include <PIN_LPC17xx.h>
#include <GPIO_LPC17xx.h>
#include <GLCD_Config.h>
#include <Board_GLCD.h>
#include <GLCD_Fonts.h>

#include <Driver_SPI.h>
 

int main( void ) {
	GLCD_Initialize()	;      
	GLCD_SetBackgroundColor	(GLCD_COLOR_WHITE);
	GLCD_SetForegroundColor(GLCD_COLOR_RED);
	GLCD_ClearScreen();
	GLCD_DrawRectangle(100,50,50,100);
	
	while ( 1 ) {
	
	}
}