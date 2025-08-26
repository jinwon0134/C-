#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Lcd/lcd.h"   // LCD 라이브러리 포함

// ====================== UART ======================
void UART_init(void){
	DDRE |= (1<<PE0);    // TXD0 출력
	DDRE &= ~(1<<PE1);   // RXD0 입력

	unsigned int ubrr = 7; // 115200bps @ 14.7456MHz
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	UCSR0A = 0x00;
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);   // 송수신 enable
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // 8bit, 1 stop, no parity
}

void UART_transmit(unsigned char data){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char UART_receive(void){
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void UART_print(const char *str){
	while(*str) UART_transmit(*str++);
}

// ====================== Baseball Game ======================
char answer[5];
char input[5];
int idx = 0;
int attempt = 0;

void generateAnswer(uint8_t announce){
	char used[10] = {0};
	for(int i=0;i<4;i++){
		int r;
		do{
			r = rand()%10;
		}while(used[r]);
		used[r] = 1;
		answer[i] = '0'+r;
	}
	answer[4] = '\0';

	if(announce){
		UART_print("[Game] New Answer Generated\r\n");
	}
}

void checkAnswer(char *guess){
	int strike=0, ball=0;
	for(int i=0;i<4;i++){
		if(guess[i]==answer[i]) strike++;
		else{
			for(int j=0;j<4;j++){
				if(i!=j && guess[i]==answer[j]) ball++;
			}
		}
	}

	char buf[32];
	sprintf(buf,"%s -> %dS %dB", guess, strike, ball);
	UART_print(buf);
	UART_print("\r\n");

	if(strike==4){
		// 정답 맞춤
		UART_print("[Game] HOME RUN!!\r\n");

		LCD_Clear();
		LCD_pos(0,0);
		LCD_STR("Mission Success");

		generateAnswer(1);  // 새 답 생성
		attempt = 0;
	}
}

// ====================== Main ======================
int main(void){
	
	UART_init();
	Port_Init();   // LCD 핀 출력 설정
	LCD_Init();    // LCD 초기화

	UART_print("[Game] Baseball Game Start!\r\n");
	generateAnswer(1);

	while(1){
		char key = UART_receive();

		// * 입력 시 게임 초기화
		if(key == '*'){
			generateAnswer(1);
			attempt = 0;
			idx = 0;
			UART_print("[Game] Reset by *\r\n");

			LCD_Clear();
			LCD_pos(0,0);
			LCD_STR("Game Reset!");
			continue;
		}

		// 숫자만 입력 허용
		if(key >= '0' && key <= '9'){
			input[idx++] = key;
		}

		// 4자리 입력되면 자동 채점
		if(idx == 4){
			input[4] = '\0';
			checkAnswer(input);
			idx = 0;
			attempt++;

			if(attempt >= 10){
				UART_print("[Game] FAIL: Max attempts\r\n");

				LCD_Clear();
				LCD_pos(0,0);
				LCD_STR("Fail");

				generateAnswer(1);
				attempt = 0;
			}
		}
	}
}
