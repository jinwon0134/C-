#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

#define LCD_WDATA PORTB
#define LCD_WINST PORTB
#define LCD_CTRL  PORTG
#define LCD_RS    0
#define LCD_RW    1
#define LCD_EN    2
#define Byte unsigned char
#define On 1
#define off 0

void Port_Init(void);
void LCD_Data(Byte ch);
void LCD_Comm(Byte ch);
void LCD_CHAR(Byte c);
void LCD_STR(char *str);   // char*로 통일
void LCD_pos(unsigned char col, unsigned char row);
void LCD_Clear(void);
void LCD_Init(void);

#endif