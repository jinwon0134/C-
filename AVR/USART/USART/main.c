/*
 * USART.c
 *
 * Created: 2025-08-13 오후 3:35:19
 * Author : COMPUTER
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void usart0_init();
void USART0_char(char data);
void USART0_str(char* str);
char rx_buf = 0;

ISR(USART0_RX_vect){
	rx_buf = UDR0;
}
void usart0_init(){
	UCSR0A=0x00;
	UCSR0B=0x98;	// 송신, 수신, 수신 인터럽트
	UCSR0C=0x06;
	UBRR0H=0x00;
	UBRR0L=0x07;	//보오레이트 115200
	sei(); //전체 인터럽트 활성화?
}

void USART0_char(char data){
	while(!(UCSR0A&0x20))
	UDR0 = data;
}

void USART0_str(char* str){
	while(*str)
		USART0_char(*str++);
}

int main(void)
{
	usart0_init();
	
    while (1) 
    {
		USART0_str("Test\n");
		if(rx_buf){
			USART0_char(rx_buf);
			rx_buf = 0;
		}
		_delay_ms(1000);

    }
}

