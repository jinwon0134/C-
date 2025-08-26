#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

static const uint8_t Font[18] = {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7C, 0x07,
	0x7F, 0x67, 0x77, 0x7C,
	0x39, 0x5E, 0x79, 0x71,
	0x08, 0x80
};

static inline void RSegment(int N)
{
	uint8_t N10 = N / 10;
	uint8_t N1  = N % 10;
	for (uint8_t i = 0; i < 5; i++) {
		PORTC = 0x0B; PORTA = Font[N10]; _delay_ms(1);
		PORTC = 0x07; PORTA = Font[N1];  _delay_ms(1);
	}
}

static inline void LSegment(int N)
{
	uint8_t N10 = N / 10;
	uint8_t N1  = N % 10;
	for (uint8_t i = 0; i < 5; i++) {
		PORTC = 0x0E; PORTA = Font[N10]; _delay_ms(1);
		PORTC = 0x0D; PORTA = Font[N1];  _delay_ms(1);
	}
}

volatile int tr_cnt = 0, mr_cnt = 0;
volatile int tl_cnt = 0, ml_cnt = 0;

ISR(TIMER0_OVF_vect)
{
	tr_cnt++;
	if (tr_cnt >= 56) {
		tr_cnt = 0;
		if (++mr_cnt > 99) mr_cnt = 0;
	}
}

ISR(TIMER0_COMP_vect)
{
	tl_cnt++;
	if (tl_cnt >= 28) {
		tl_cnt = 0;
		if (++ml_cnt > 99) ml_cnt = 0;
	}
}

int main(void)
{
	DDRA = 0xFF;
	DDRC = 0x0F;
	PORTA = 0x00;
	PORTC = 0x0F;

	DDRB |= (1<<PB4);

	TCCR0 = (1<<WGM01)|(1<<WGM00) | (1<<COM01) | (1<<CS02)|(1<<CS01)|(1<<CS00);
	TCNT0 = 0x00;
	OCR0  = 102;

	TIFR  |= (1<<TOV0) | (1<<OCF0);
	TIMSK |= (1<<TOIE0) | (1<<OCIE0);

	sei();

	while (1) {
		LSegment(ml_cnt);
		RSegment(mr_cnt);
	}
}
