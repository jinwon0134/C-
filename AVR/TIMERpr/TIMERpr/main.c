#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint8_t Duty = 0;

	DDRD |= (1<<PD7);                         // OC2 (PD7) PWM 출력
	TCCR2 = (1<<WGM21)|(1<<WGM20)             // Fast PWM
	| (1<<COM21)                        // 비반전
	| (1<<CS22)|(1<<CS20);              // 분주 /128
	TIMSK &= ~((1<<TOIE2)|(1<<OCIE2));        // 인터럽트 미사용
	TCNT2 = 0;
	OCR2  = 0;

	while (1) {
		_delay_ms(100);
		Duty++;            // 0→255 순환
		OCR2 = Duty;
	}
}