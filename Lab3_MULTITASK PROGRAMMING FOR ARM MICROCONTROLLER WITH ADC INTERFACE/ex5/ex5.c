#include <LPC17xx.h>
#include <PIN_LPC17xx.h>
#include <GPIO_LPC17xx.h>
#include <GLCD_Config.h>
#include <Board_GLCD.h>
#include <GLCD_Fonts.h>
#include <Driver_SPI.h>
#include <stdio.h>
char myString[]={"hello, world"};
char ADC_String[20]=" ";
#define VREF       3.3 //Reference Voltage at VREFP pin, given VREFN = 0V(GND)
#define ADC_CLK_EN (1<<12)
#define SEL_AD0_2  (1<<6) //Select Channel AD0.0 
#define CLKDIV     1 //ADC clock-divider (ADC_CLOCK=PCLK/CLKDIV+1) = 12.5Mhz      
                     //25Mhz PCLK
#define PWRUP      (1<<21) //setting it to 0 will power it down
#define START_CNV  (1<<24) //001 for starting the conversion immediately
#define ADC_DONE   (1U<<31) //define it as unsigned value Done Bit
#define ADCR_SETUP_SCM ((CLKDIV<<8) | PWRUP)

int main( void ) {
	GLCD_Initialize()	;      
	GLCD_SetFont(&GLCD_Font_16x24)	;
	GLCD_SetBackgroundColor	(GLCD_COLOR_GREEN)	;
	GLCD_SetBackgroundColor	(GLCD_COLOR_LIGHT_GREY);
	GLCD_ClearScreen()	;
	
	LPC_SC->PCONP |= ADC_CLK_EN; //Enable ADC clock
	LPC_ADC->ADCR =  ADCR_SETUP_SCM | SEL_AD0_2;
	LPC_PINCON->PINSEL0 |= (1<<7) ; //select AD0.2 for P0.25
	int result = 0;
	int bar_value;
	float volts = 0;

	while ( 1 ) {		
		LPC_ADC->ADCR |= START_CNV; //Start new Conversion
		while((LPC_ADC->ADDR6 & ADC_DONE) == 0); //Wait untill conversion is     
                                                     //finished
		result = (LPC_ADC->ADDR6>>4) & 0xFFF; //12 bit Mask to extract                     
                                                  //result
		volts = (result*VREF)/4096.0; //Convert result to Voltage
		bar_value = volts*100/3.3;
		sprintf(ADC_String, "Volts: %f V", volts);
		GLCD_DrawString	(5,200,ADC_String);	
	}
}