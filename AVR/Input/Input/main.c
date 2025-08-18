/*
 * Input.c
 *
 * Created: 2025-08-12 오후 2:09:10
 * Author : COMPUTER
 */ 
#include <avr/io.h>
#include <util/delay.h>

unsigned char font[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};
//1.
// #define FIRST_DIGIT 0x0E
// 
// //PORTE = PIND; 포트 D로 들어오는 입력값을 포트E로 전달
// 
// int main(void)
// {
// 	DDRE = 0xFF; // FND 출력포트
// 	DDRD = 0x00; // 버튼 입력포트
// 	DDRG = 0xFF; // 자리 선택
// 
// 	PORTD = 0x00; // 내부 풀업 끄기 (필요에 따라 조정)
// 
// 	while(1)
// 	{
// 		
// 		unsigned char buttons = PIND; // PIND 직접 읽기
// 
// 		if(buttons == 0x00) // 버튼 아무것도 안 눌렸으면
// 		{
// 			PORTE = 0x00;   // FND 끄기
// 			PORTG = 0x0F;   // 자리 선택 OFF (LOW 활성)
// 		}
// 		else
// 		{
// 			for(int i=0; i<8; i++)
// 			{
// 				if(buttons & (1 << i)) // PIND 해당 비트가 1이면 눌림
// 				{
// 					PORTE = font[i+1]; // 숫자 출력 (1~8)
// 					PORTG = FIRST_DIGIT;
// 					break;
// 				}
// 			}
// 		}
// 		_delay_ms(5);
// 	}
// }

//2.
// #define FIRST_DIGIT 0x0E
// 
// int main(void)
// {
// 	DDRE = 0xFF; // FND 출력
// 	DDRD = 0x00; // 버튼 입력
// 	DDRG = 0xFF; // 자리 선택
// 
// 	PORTD = 0x00; // 내부 풀업 끄기 (필요에 따라 조정)
// 
// 	while(1)
// 	{
// 		unsigned char buttons = PIND;
// 
// 		if(buttons == 0x00)
// 		{
// 			PORTE = 0x00;  // FND 끄기
// 			PORTG = 0x0F;  // 자리 선택 끄기
// 		}
// 		else if(buttons & 0x01)
// 		{
// 			PORTE = font[1];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x02)
// 		{
// 			PORTE = font[2];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x04)
// 		{
// 			PORTE = font[3];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x08)
// 		{
// 			PORTE = font[4];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x10)
// 		{
// 			PORTE = font[5];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x20)
// 		{
// 			PORTE = font[6];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x40)
// 		{
// 			PORTE = font[7];
// 			PORTG = FIRST_DIGIT;
// 		}
// 		else if(buttons & 0x80)
// 		{
// 			PORTE = font[8];
// 			PORTG = FIRST_DIGIT;
// 		}
// 
// 		_delay_ms(5);
// 	}
// }

//3.

int main(void)
{
	DDRE = 0xFF; // 7세그먼트 출력
	DDRD = 0x00; // 버튼 입력
	DDRG = 0xFF; // 자리 선택

	PORTD = 0x00; // 내부 풀업 OFF

	unsigned int number = 0; // 0~999까지 숫자 저장
	unsigned char prev_button_state = 0;

	while(1)
	{
		unsigned char buttons = PIND;

		// 버튼 8 (0x80) 누르면 초기화
		if(buttons & 0x80)
		{
			number = 0;
		}
		// 버튼 1 (0x01) 누르고, 이전 상태와 달라졌을 때만 증가 (간단한 누름 감지)
		else if((buttons & 0x01) && !(prev_button_state & 0x01))
		{
			if(number < 999) number++;
			else number = 0; // 999 넘으면 다시 0으로
		}

		prev_button_state = buttons;

		// 숫자 분리
		int hundreds = number / 100;
		int tens = (number / 10) % 10;
		int ones = number % 10;

		// 멀티플렉싱으로 3자리 표시
		// 1의 자리
		PORTE = font[ones];
		PORTG =  0x0B;
		_delay_ms(3);

		// 10의 자리
		PORTE = font[tens];
		PORTG = 0x0D;
		_delay_ms(3);

		// 100의 자리
		PORTE = font[hundreds];
		PORTG = 0x0E;
		_delay_ms(3);
	}
}