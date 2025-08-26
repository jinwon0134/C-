#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0x0F;  // PB3..PB0 출력

	while (1) {
		PORTB = (PORTB & ~0x0F) | 0x01; _delay_ms(10);
		PORTB = (PORTB & ~0x0F) | 0x02; _delay_ms(10);
		PORTB = (PORTB & ~0x0F) | 0x04; _delay_ms(10);
		PORTB = (PORTB & ~0x0F) | 0x08; _delay_ms(10);
	}
}
