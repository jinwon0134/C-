#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// --- 전역 변수 ---
volatile unsigned int t_cnt = 0;
volatile unsigned int m_cnt = 0;

unsigned char Font[18] = {
	0x3F, 0x06, 0x5B, 0x4F,
	0x66, 0x6D, 0x7C, 0x07,
	0x7F, 0x67, 0x77, 0x7C,
	0x39, 0x5E, 0x79, 0x71,
	0x08, 0x80
};

// --- 4자리 7-세그먼트 출력 함수 ---
void Segment(int N)
{
	int i;
	unsigned char N1000, N100, N10, N1;
	int Buff;

	N1000 = N / 1000;
	Buff = N % 1000;
	N100 = Buff / 100;
	Buff = Buff % 100;
	N10 = Buff / 10;
	N1 = Buff % 10;

	for (i = 0; i < 30; i++) {
		PORTC = 0x0E;
		PORTA = Font[N1000];
		_delay_ms(1);

		PORTC = 0x0D;
		PORTA = Font[N100];
		_delay_ms(1);

		PORTC = 0x0B;
		PORTA = Font[N10];
		_delay_ms(1);

		PORTC = 0x07;
		PORTA = Font[N1];
		_delay_ms(1);
	}
}

// --- Timer0 오버플로우 인터럽트 서비스 루틴 ---
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0x00;    // 초기값 설정 (0부터 시작)
	t_cnt++;
	if (t_cnt >= 244) {  // 약 1초 (244 × 4.096ms ≈ 1초)
		t_cnt = 0;
		m_cnt++;
	}
}

// --- 메인 함수 ---
int main(void)
{
	// 포트 초기화
	DDRA = 0xFF;  // 세그먼트 데이터 출력 (a~g + dp)
	DDRC = 0x0F;  // 자릿수 제어용
	PORTA = 0xFF;
	PORTC = 0x0F;

	// 타이머 설정 (분주비 256)
	TCCR0 = (1 << CS02);       // CS02=1, CS01=0, CS00=0 → 분주비 256
	TIMSK |= (1 << TOIE0);     // Timer0 overflow interrupt enable
	TCNT0 = 0x00;              // 타이머 초기값

	sei(); // 전역 인터럽트 허용

	while (1) {
		Segment(m_cnt);  // 증가된 m_cnt 표시
	}

	return 0;
}
