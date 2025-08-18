#define F_CPU 14745600UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char LED_Data = 0x00;
volatile int cnt = 0;

ISR(TIMER0_OVF_vect) {
	TCNT0 = 0xF2;  // 타이머 초기화
	cnt++;
	if (cnt >= 1000) {
		cnt = 0;
		LED_Data++;  // LED 상태 변경
	}
}

int main(void)
{
	DDRB = 0xFF;    // 포트 B 출력
	DDRE = 0xFF;    // 포트 E 출력

	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);  // 1024분주
	TCNT0 = 0xF2;                // 타이머 초기값
	TIMSK |= (1 << TOIE0);       // Timer0 오버플로우 인터럽트 허용
	TIFR |= (1 << TOV0);         // 인터럽트 플래그 클리어
	sei();                       // 전역 인터럽트 허용

	while (1)
	{
		PORTB = LED_Data;  // LED에 출력
	}
}
