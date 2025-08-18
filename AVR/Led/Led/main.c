/*
 * Led.c
 *
 * Created: 2025-08-11 오후 2:28:23
 * Author : COMPUTER
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0xff; // 포트 선택
	DDRE = 0xff;
	DDRB = 0xff;
	DDRA = 0xff;
	while (1)
	{
		PORTD = 0xff;  // 모든 LED OFF
		_delay_ms(500);
		PORTD = 0x00;  // PE0 LED ON
		_delay_ms(500);
	}
}
