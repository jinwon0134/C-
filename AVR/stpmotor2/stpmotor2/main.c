// ATmega128A / Microchip Studio (AVR-GCC)
// PORTB 하위 4비트에 0x03 → 0x09 → 0x0C → 0x06 시퀀스를
// 10ms 간격으로 12회 반복 후 5초 대기

#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	// PB3..PB0 출력
	DDRB |= 0x0F;

	// 시퀀스 테이블
	const uint8_t seq[4] = { 0x03, 0x09, 0x0C, 0x06 };

	while (1) {
		for (uint8_t i = 0; i < 12; i++) {
			for (uint8_t k = 0; k < 4; k++) {
				// 하위 4비트만 갱신(상위 비트 보존)
				PORTB = (PORTB & ~0x0F) | seq[k];
				_delay_ms(10);
			}
		}
		_delay_ms(1000);
	}
}