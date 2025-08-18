
#include <avr/io.h>
#include <util/delay.h>

unsigned char Fnd_code[] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

unsigned char display_digits[4] = {0,0,0,0};
volatile unsigned char number = 0;

void scan_display(void){
	PORTG = ~0x01;         // 첫 번째 자리만 켜기 (필요에 따라 반전)
	PORTB = Fnd_code[display_digits[0]];
	_delay_ms(10);
}


int main(void){
	DDRD = 0x00;    // 버튼 입력 PD0
	PORTD = 0xFF;   // 풀업저항 활성화

	DDRB = 0xFF;    // FND 세그먼트 출력 포트 (PORTB)
	DDRG = 0x0F;    // FND 자리 선택 출력 포트 (PORTG 0~3)

	unsigned char last_btn_state = 1; // 버튼 안 눌림 (풀업)

	while(1){
		unsigned char btn_state = (PIND>>3) & 0x01; // PD0 버튼 상태 읽기

		// 버튼이 안 눌렸다가 눌렸을 때 감지
		if(last_btn_state == 1 && btn_state == 0){
			_delay_ms(20); // 디바운싱
			if(((PIND >> 3) & 0x01) == 0){ // 여전히 눌림 상태면
				number++;
				if(number > 9) number = 0;
				display_digits[0] = number;

				// 버튼이 떨어질 때까지 대기
				while(((PIND >> 3) & 0x01) == 0);
			}
		}
		last_btn_state = btn_state;

		scan_display();
	}
}
