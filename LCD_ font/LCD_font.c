#include "font.h"

///

/// send single character to the LCD
void LCD_send_char (char ch)
{
		ch = ch - ' ';
		int index = ch * 5;
		for(int i=0;i<5;i++)
		{
			send_SPI(font5x8[index++]);
		}
		send_SPI(0x00);
}

///

/// send string to the LCD
void LCD_puts (char *ch) 
{
	while(*ch)
	{
		LCD_send_char(*ch++);
	}
}

///

