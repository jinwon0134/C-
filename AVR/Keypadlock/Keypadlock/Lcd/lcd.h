#ifndef LCD_H
#define LCD_H

#include <avr/io.h>

#define LCD_WDATA PORTB
#define LCD_WINST PORTB
#define LCD_CTRL  PORTG
#define LCD_RS    0				//LCD RS 신호
#define LCD_RW    1				//LCD RW 신호
#define LCD_EN    2				//LCD EN 신호
#define Byte unsigned char
#define On 1
#define off 0
//#define TLCD_EN { TLCD_E = 0; TLCD_E = 1;}
//#define DATA PORTC							//데이터 신호
								
void Port_Init(void);				//128a 포트 초기화 함수
void LCD_Data(Byte ch);	//LCD에 데이터 입력 함수
void LCD_Comm(Byte ch);
void LCD_CHAR(Byte c);
void LCD_STR(Byte *str);
void LCD_pos(unsigned char col, unsigned char row);
void LCD_Clear(void);
void LCD_Init(void);			//LCD 초기화 함수

#endif
오후 3:44 2025-08-21