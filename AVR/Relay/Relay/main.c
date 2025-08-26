/*
 * Relay.c
 *
 * Created: 2025-08-21 오전 9:21:34
 * Author : COMPUTER
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 14745600UL
int main(void)
{
   DDRB = 0x01;
    while (1) 
    {
		PORTB = 1;
		_delay_ms(5000);
		PORTB = 0;
		_delay_ms(5000);
    }
}

