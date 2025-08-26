#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

#define LCD_WDATA PORTB
#define LCD_WINST PORTB
#define LCD_CTRL  PORTG
#define LCD_EN    0
#define LCD_RW    1
#define LCD_RS    2

void PortInit(void){
	DDRB = 0xFF;
	DDRG = 0x0F;
}

void LCD_Data(Byte ch){
	LCD_CTRL |=(1<<LCD_RS);
	LCD_CTRL &= ~(1<<LCD_RW);
	LCD_CTRL |= (1<<LCD_EN);
	_delay_us(50);
	LCD_WDATA = ch;
	_delay_us(50);
	LCD_CTRL&= ~(1<<LCD_EN);
}

void LCD_Comm(Byte ch){
	LCD_CTRL &= ~(1<<LCD_RS);
	LCD_CTRL &= ~(1<<LCD_RW);
	LCD_CTRL |= (1<< LCD_EN);
	_delay_us(50);
	LCD_WINST = ch;
	_delay_us(50);
	LCD_CTRL &= ~(1<<LCD_EN);
}

void LCD_CHAR(Byte c){
	LCD_Data(c);
	_delay_ms(1);
}

void LCD_STR(Byte *str){
	while(*str !=0){
		LCD_CHAR(*str);
		str++;
	}
}

void LCD_pos(unsigned char col, unsigned char row){
	LCD_Comm(0x80 | (row+col*0x40));
}

void LCD_Clear(void){
	LCD_Comm(0x01);
	_delay_ms(2);
}

void LCD_Init(void){
	LCD_Comm(0x38);
	_delay_ms(2);
	LCD_Comm(0x38);
	_delay_ms(2);
	LCD_Comm(0x38);
	_delay_ms(2);
	LCD_Comm(0x0e);
	_delay_ms(2);
	LCD_Comm(0x06);
	_delay_ms(2);
	LCD_Clear();
}
