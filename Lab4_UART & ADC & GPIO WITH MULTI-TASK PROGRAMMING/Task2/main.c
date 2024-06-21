#include "LPC17xx.h"                      // Device header
#include "Uart.h"
#include "Led.h"

int main(void)
{
  UART_Initialize(9600);
	Led_Initialize();
	
  while(1)
  {
		if(UART_Buffer_Count>0)
		{
			if(UART_Buffer[UART_Buffer_Count-1] == 0xFF)
			{
				Leds_Set_Value(0xFF);
				UART_Send("\nLEDs are turned on",19);
			}
			else if(UART_Buffer[UART_Buffer_Count-1] == 0xF0)
			{
				Leds_Set_Value(0x00);
				UART_Send("\nLEDs are turned off",20);
			}
			UART_Buffer_Count = 0;
		}
  }
}