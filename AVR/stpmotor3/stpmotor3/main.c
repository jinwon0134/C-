#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
static const uint8_t Step[8] = {
	0x09, 0x08, 0x0C, 0x04, 0x06, 0x02, 0x03, 0x01
};

int main(void)
{
	uint8_t t = 0;

	// PB3..PB0 출력
	DDRB |= 0x0F;
	// 초기값(코일 OFF)
	PORTB = (PORTB & ~0x0F);

	while (1) {
		// 90도 회전(24스텝)
		for (uint8_t i = 0; i < 24; i++) {
			// 하위 4비트만 갱신(상위 비트 보존)
			PORTB = (PORTB & ~0x0F) | Step[t];
			t++;
			if (t >= 8) t = 0;       // 시퀀스 순환
			_delay_ms(10);           // 스텝 속도(느리게 하려면 값↑)
		}
		_delay_ms(1000);             // 1초 대기
	}
}
