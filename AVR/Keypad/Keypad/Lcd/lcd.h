#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#define Byte unsigned char

void PortInit(void);
void LCD_Data(Byte ch);
void LCD_Comm(Byte ch);
void LCD_CHAR(Byte c);
void LCD_STR(Byte *str);
void LCD_pos(unsigned char col, unsigned char row);
void LCD_Clear(void);
void LCD_Init(void);

#endif
