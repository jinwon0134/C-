#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

void putch(unsigned char data) {
	/*while ((UCSR0A & 0x20) == 0) ;*/  // UDRE0 대기
	while(!(UCSR0A & 0x20));
	UDR0 = data;
	// UCSR0A |= 0x20;  // <- 이 줄은 굳이 필요 없음(오타는 아님)
}

void putstr(unsigned char* str){
	while(*str){
		putch(*str++);
	}
}

int main(void)
{
	unsigned char text[] = "Hello World!\r\n";
	unsigned char i = 0;

	DDRE = 0xfe;
	UCSR0A = 0x00;
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);           // 0x18
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);         // 0x06
	UBRR0H = 0x00;
	UBRR0L = 0x07;                                      // 세미콜론 OK

// 	while (text[i] != '\0') {                        // ← 여기 수정
// 		putch(text[i++]);
// 	}
// 	return 0;                                        // ← 루프 밖으로 이동

	while(1){
		putstr(text);
		_delay_ms(1000);
	}
	return 0;
}
