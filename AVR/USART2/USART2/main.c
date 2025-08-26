#define F_CPU 14745600UL

#include <util/delay.h>
#include <avr/io.h>

void Init_USART()
{
	UCSR0A = 0x00;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0H = 0x00;
	UBRR0L = 0x07;
}

void USART0_tx(unsigned char data)       // 송신
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

unsigned char USART0_rx()                // 수신
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

void USART_str(unsigned char* str)
{
	while(*str){
		USART0_tx(*str++);
	}
}
// 
// int main(void)
// {
// /*	unsigned char str[] = "Hello world!! \r\n";*/
// 	Init_USART();
// DDRB = 0x01;
// 	while (1)
// 	{
// 		
// // 		USART_str(str);
// // 		//unsigned char data = USART0_rx();
// // 		//USART0_tx(data);
// // 		_delay_ms(500);
// unsigned char data = USART0_rx();
// USART0_tx(data);
int main(void)
{
    Init_USART();
    DDRB = 0xFF;   // PORTB 전체 출력 (LED 8개)
	unsigned char str[] = "Hello world!! \r\n";
	USART_str(str);
    while (1)
    {
        unsigned char data = USART0_rx(); // 시리얼 입력
        USART0_tx(data);                  // 에코 출력
		if (data == '1') PORTB = 0x01;
            else if (data == '2') PORTB = 0x02;
            else if (data== '3') PORTB = 0x03;
            else if (data == '4') PORTB = 0x04;
            else if (data== '5') PORTB = 0x05;
            else if (data== '6') PORTB = 0x06;
            else if (data== '7') PORTB = 0x07;
            else if (data== '8') PORTB = 0x08;
            else if (data== '9') PORTB = 0x09;

    }
}
