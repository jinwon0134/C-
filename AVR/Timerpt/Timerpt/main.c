#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define LED_ACTIVE_LOW 1
#define PWM_STEPS 16
#define RAMP_STEP_MS 20
#define DEBOUNCE_MS 50

volatile uint8_t pwm_phase = 0;
volatile uint8_t led_level[8] = {0};
uint8_t led_target[8] = {0};

// 소프트웨어 PWM용 Timer2 초기화
void timer2_init(void) {
	TCCR2 = (1 << WGM21) | (1 << CS22); // CTC, /64
	OCR2  = 124;                        // 2kHz
	TIMSK |= (1 << OCIE2);              // Compare Match 인터럽트
}

// Timer2 ISR: 소프트웨어 PWM
ISR(TIMER2_COMP_vect) {
	pwm_phase++;
	if (pwm_phase >= PWM_STEPS) pwm_phase = 0;

	uint8_t bits = 0;
	for (uint8_t i = 0; i < 8; i++) {
		if (led_level[i] > pwm_phase) bits |= (1u << i);
	}

	#if LED_ACTIVE_LOW
	PORTB = ~bits;
	#else
	PORTB = bits;
	#endif
}

// 버튼 입력 처리: 한 번 누르면 LED 밝기 설정
static inline void update_targets_from_buttons(void) {
	static uint8_t last_state = 0;
	static uint16_t last_time[8] = {0};
	static uint16_t ms_counter = 0;

	ms_counter += 2; // 루프에서 2ms씩 증가

	uint8_t current_state = ~PIND;       // 현재 버튼 상태 (풀업)
	uint8_t new_press = current_state & ~last_state; // 새로 눌린 버튼 감지

	for (uint8_t i = 0; i < 8; i++) {
		if (new_press & (1 << i)) {
			if ((ms_counter - last_time[i]) > DEBOUNCE_MS) {
				uint8_t level = ((i + 1) * PWM_STEPS) / 8;
				if (level < 1) level = 1;
				led_target[i] = level;
				if (led_level[i] == 0) led_level[i] = 1;
				last_time[i] = ms_counter;
			}
		}
	}

	last_state = current_state;
}

// LED 밝기를 목표로 한 단계씩 변화
static inline void ramp_one_step(void) {
	for (uint8_t i = 0; i < 8; i++) {
		if (led_level[i] < led_target[i]) led_level[i]++;
		else if (led_level[i] > led_target[i]) led_level[i]--;
	}
}

int main(void) {
	// LED 출력 설정
	DDRB = 0xFF;
	#if LED_ACTIVE_LOW
	PORTB = 0xFF;
	#else
	PORTB = 0x00;
	#endif

	// 버튼 입력 설정 (PD0~PD7) + 내부 풀업
	DDRD  = 0x00;
	PORTD = 0xFF;

	timer2_init();
	sei();

	uint16_t ramp_timer = 0;

	while (1) {
		update_targets_from_buttons();

		_delay_ms(2);
		ramp_timer += 2;
		if (ramp_timer >= RAMP_STEP_MS) {
			ramp_timer = 0;
			ramp_one_step();
		}
	}
}
