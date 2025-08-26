#define F_CPU 14745600UL   // 보드 클럭에 맞게 수정
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

void Segment(int N);
volatile int t_cnt = 0;
volatile int m_cnt = 0;

// -------------------- Timer0 OVF ISR --------------------
ISR(TIMER0_OVF_vect)
{
	// 16MHz, /1024 기준: TCNT0=0xF2 → 약 0.896 ms/OVF
	// (정확 1ms에 가깝게 하려면 0xF0 ≈ 1.024 ms)
	TCNT0 = 0xF2; // 타이머/카운터 초기값을 Re-Load

	t_cnt++;
	if (t_cnt >= 1000) {   // ≈1초 주기(정확도는 클럭/리로드에 의존)
		t_cnt = 0;
		m_cnt++;
		if (m_cnt > 9999) m_cnt = 0;  // 4자리 롤오버
	}
}

// -------------------- 4자리 7세그 표시 함수 --------------------
void Segment (int N)
{
	int i;
	uint8_t N1000, N100, N10, N1;
	int Buff;

	if (N < 0) N = 0;
	if (N > 9999) N = 9999;

	N1000 = (uint8_t)(N / 1000);
	Buff  = N % 1000;
	N100  = (uint8_t)(Buff / 100);
	Buff  = Buff % 100;
	N10   = (uint8_t)(Buff / 10);
	N1    = (uint8_t)(Buff % 10);

	// 간단한 멀티플렉싱(가시성 위해 소량 반복)
	for (i = 0; i < 30; i++)
	{
		// 자리 선택: PORTC 하위 4비트 사용(활성 Low 가정: 0이 켬)
		PORTC = 0x0E; // 1110b → 1번째 자리 ON
		PORTA = Font[N1000];
		_delay_ms(1);

		PORTC = 0x0D; // 1101b → 2번째 자리 ON
		PORTA = Font[N100];
		_delay_ms(1);

		PORTC = 0x0B; // 1011b → 3번째 자리 ON
		PORTA = Font[N10];
		_delay_ms(1);

		PORTC = 0x07; // 0111b → 4번째 자리 ON
		PORTA = Font[N1];
		_delay_ms(1);
	}
}

// -------------------- 메인 --------------------
int main(void)
{
	// 포트 방향 설정
	DDRA = 0xFF;   // 세그먼트 데이터(a~g, dp)
	DDRC = 0x0F;   // 자리 선택(하위 4비트 출력)
	PORTA = 0x00;  // 공통캐소드 기준 초기값
	PORTC = 0x0F;  // 모든 자리 OFF(활성 Low 가정)

	// Timer0 설정: 내부 클럭, /1024 분주
	// ATmega128A는 TIMSK(일반 타이머) 사용
	TCCR0 = (1<<CS02) | (1<<CS01) | (1<<CS00); // 0b111 → /1024
	TCNT0 = 0xF2;                               // 요청값(≈0.896ms/OVF)
	TIFR  |= (1<<TOV0);                         // 이전 OVF 플래그 클리어(1을 써서 클리어)
	TIMSK |= (1<<TOIE0);                        // Timer0 Overflow 인터럽트 Enable

	sei(); // 전역 인터럽트 허용

	while (1)
	{
		// ISR이 m_cnt를 1초마다 증가
		Segment(m_cnt);
		// 필요시 다른 작업을 여기서 수행
	}
}