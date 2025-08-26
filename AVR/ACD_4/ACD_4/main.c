#define F_CPU 14745600UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char Font[18] = {
	0x3F,0x06,0x5B,0x4F,
	0x66,0x6D,0x7C,0x07,
	0x7F,0x67,0x77,0x7C,
	0x39,0x5E,0x79,0x71,
	0x08,0x80
};

volatile unsigned int adc_data = 0;

void Segment(int N)
{
	int i;
	unsigned char N1000, N100, N10, N1;
	int Buff;

	N1000 = N/1000;
	Buff = N%1000;
	N100 = Buff/100;
	Buff = Buff%100;
	N10 = Buff/10;
	N1 = Buff%10;

	for(i=0;i<30;i++){
		PORTC=0x0e; PORTA=Font[N1000]; _delay_ms(1);
		PORTC=0x0d; PORTA=Font[N100];  _delay_ms(1);
		PORTC=0x0b; PORTA=Font[N10];   _delay_ms(1);
		PORTC=0x07; PORTA=Font[N1];    _delay_ms(1);
	}
}

ISR(ADC_vect) {
	adc_data = ADCW;
	ADCSRA |= (1<<ADSC);   // 다음 변환 계속
}

int main(void)
{
	DDRA=0xFF;
	DDRC=0x0F;
	PORTA=0xFF;
	PORTC=0x0F;

	DDRF=0x00;             // PF3 입력
	ADMUX = 0x03;          // ADC3 선택 (PF3)
	ADCSRA = (1<<ADEN)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // ADC enable, interrupt enable, 128분주

	sei();                 // 전역 인터럽트 허용
	ADCSRA |= (1<<ADSC);   // 첫 변환 시작

	while(1) {
		Segment(adc_data);
	}
}
