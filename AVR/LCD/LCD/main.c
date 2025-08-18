/*
 * LCD.c
 *
 * Created: 2025-08-13 오전 9:29:57
 * Author : COMPUTER
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //인터럽트 헤더 파일
#include <util/delay.h> //딜레이 헤더 파일

#define LCD_WDATA PORTB//LCD데이터 포트 정의
#define LCD_WINST PORTB
#define LCD_CTRL PORTG	//LCD 제어 포트 정의
#define LCD_EN 0		//LCD 제어(PING0~2)정의
#define LCD_RW 1
#define LCD_RS 2
#define Byte unsigned char //Byte 선언
#define On 1
#define Off 2

void PortInit(void){
	DDRB = 0xFF;
	DDRG = 0x0F;
}

void LCD_Data(Byte ch){
	LCD_CTRL |=(1<<LCD_RS); //RS=1, R/W=0으로 데이터 쓰기 싸이클
	LCD_CTRL &= ~(1<<LCD_RW);
	LCD_CTRL |= (1<<LCD_EN); //LCD 사용
	_delay_us(50);
	LCD_WDATA = ch; //데이터 출력
	_delay_us(50);
	LCD_CTRL&= ~(1<<LCD_EN);//LCD사용안함
}

void LCD_Comm(Byte ch){ //PG0-EN, PG1-RW, PG@-RS, PG4-TOSC1핀(사용안함)
	LCD_CTRL &= ~(1<<LCD_RS);//LCD_CTRL = LCD제어부 포트(4핀인데 실질적인 사용 3핀)
	LCD_CTRL &= ~(1<<LCD_RW);//RS =0, RW=0으로 정의
	LCD_CTRL |= (1<< LCD_EN);
	_delay_us(50);
	LCD_WINST = ch;//명령어 쓰기
	_delay_us(50);
	LCD_CTRL &= ~(1<<LCD_EN);//LCD 사용 안함
}

void LCD_CHAR(Byte c){//한문자 출력 함수
	LCD_Data(c);
	_delay_ms(1);
}
void LCD_STR(Byte *str){//문자열을 한문자씩 출력함수로 전달
	while(*str !=0)
	{
		
		LCD_CHAR(*str);
		str++;
	}
}
void LCD_pos(unsigned char col, unsigned char row){ //LCD 포지션 설정
	LCD_Comm(0x80 | (row+col*0x40));//row=행, col=열, DDRAM주소 설정
}

void LCD_Clear(void){//화면 클리어
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
int main(void)
{
	char buf[16]; // LCD 한 줄 크기 (최대 16글자)
	PortInit();
	LCD_Init();

	for (int dan = 2; dan <= 9; dan++) {        // 2단 ~ 9단
		for (int i = 1; i <= 9; i++) {          // 각 단의 1~9
			LCD_Clear();                        // 화면 지우기
			LCD_pos(0,0);                       // 첫 줄
			snprintf(buf, sizeof(buf), "%d x %d = %d", dan, i, dan*i);
			LCD_STR((Byte*)buf);                 // 문자열 출력

			_delay_ms(1000);                    // 1초 대기
		}
	}

	while (1) { } // 무한 대기
}
