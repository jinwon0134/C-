#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include "Lcd/lcd.h"

// 키패드 행, 열 정의
#define ROWS 4
#define COLS 3
#define PASSWORD "1101"   // 정답 비밀번호

void keypad_Init(){
	DDRD = 0xF0;   // PD4~PD7 = 출력(Row), PD0~PD2 = 입력(Col)
}

char getKey(void)
{
	// ---------------- Row 0 ----------------
	PORTD = 0x10;
	_delay_us(50);
	if(PIND & 0x01) return '1';
	if(PIND & 0x02) return '2';
	if(PIND & 0x04) return '3';

	// ---------------- Row 1 ----------------
	PORTD = 0x20;
	_delay_us(50);
	if(PIND & 0x01) return '4';
	if(PIND & 0x02) return '5';
	if(PIND & 0x04) return '6';

	// ---------------- Row 2 ----------------
	PORTD = 0x40;
	_delay_us(50);
	if(PIND & 0x01) return '7';
	if(PIND & 0x02) return '8';
	if(PIND & 0x04) return '9';

	// ---------------- Row 3 ----------------
	PORTD = 0x80;
	_delay_us(50);
	if(PIND & 0x01) return '*';
	if(PIND & 0x02) return '0';
	if(PIND & 0x04) return '#';

	return 0; // 아무 키도 안눌림
}

int main(void)
{
	Port_Init();
	LCD_Init();
	keypad_Init();

	LCD_pos(0,0);

	char input[5] = {0};  // 최대 4자리 + 종료문자
	int idx = 0;

	while(1)
	{
		char key = getKey();

		if(key) // 키가 눌렸을 때만
		{
			if(key == '#')  // 확인키
			{
				input[idx] = '\0';  // 문자열 끝 표시

				if(strcmp(input, PASSWORD) == 0)
				{
					LCD_Clear();
					LCD_pos(0,0);
					LCD_STR("success");
					PORTA =0xFF;
				}
				else
				{
					LCD_Clear();
					LCD_pos(0,0);
					LCD_STR("fail");
					PORTA = 0x00;
					
				}
				idx = 0; // 다시 처음부터 입력
			}
			
			else
			{
				if(idx < 4) // 최대 4자리까지만 저장
				{
					input[idx++] = key;
					LCD_CHAR(key); // 입력한 값 LCD에 표시
				}
				
			}
			
			_delay_ms(200); // 디바운스
		}
	}
}
