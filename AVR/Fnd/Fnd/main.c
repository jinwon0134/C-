/*
 * Fnd.c
 *
 * Created: 2025-08-12 오전 10:05:44
 * Author : COMPUTER
 anode: Vcc
 cathode:GND
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xff; //포트 B를 출력으로 설정
	DDRG = 0xff; //포트 B를 출력으로 설정
	PORTG = 0x07;//포트 G를 모두 0으로 출력(PG0 ~ PG3) ob0000 0111
	0E = 0000 1110 0D= 0000 1101
    while (1) 
    {
		PORTB = 0x01;
		_delay_ms(500);
		PORTB = 0x02;
		_delay_ms(500);
		PORTB = 0x04;
		_delay_ms(500);
		PORTB = 0x08;
		_delay_ms(500);
		PORTB = 0x010;
		_delay_ms(500);
		PORTB = 0x20;
		_delay_ms(500);
		PORTB = 0x40;
		_delay_ms(500);
		PORTB = 0x80;
		_delay_ms(500);
		
    }
}

