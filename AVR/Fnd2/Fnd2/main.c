/*
 * Fnd2.c
 *
 * Created: 2025-08-12 오전 10:39:44
 * Author : COMPUTER
 */ 

#include <avr/io.h>
#include <util/delay.h>
//1.
//  unsigned char Font[16] = {
//  	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 
//  	0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 
//  	0x39,0x5E, 0x79,0x71
//  };
// 
// 
// int main(void)
// {
// 	DDRB = 0xff;
// 	DDRG = 0xff;
// 	/*PORTG = 0x00;*/ // 0b 1111 1110
//     while (1) 
//     {
//  		for(int i=0; i<16;i++){
//  			PORTB=Font[i];
//  			_delay_ms(500);
//  		}
//  		
//     }
// }
//
//2.  
// unsigned char Font1[4] = {0x06, 0x5B, 0x4F,0x66};
// unsigned char Select[4] = {0x0e, 0x0d, 0x0b, 0x07} ;
// 	
// int main(void){
// 	DDRB = 0xff;
// 	DDRG = 0xff;
// 	while(1){
// 		for(int i =0; i<4; i++)
// 		{
// 			PORTG =0x00;
// 			
// 			PORTB = Font1[i];
// 			PORTG = Select[i];
// 			_delay_ms(5);
// 			
// 		}
// 	}
// }

//3.
unsigned char font[10] = {
	0x3F,0x06,0x5B,0x4F,0x66,
	0x6D,0x7D,0x07,0x7F,0x6F
};

unsigned char select_digit[4] = {0x0E, 0x0D, 0x0B, 0x07};

void display_number(int num) {
	int d[4];
	d[0] = (num / 1000) % 10;
	d[1] = (num / 100) % 10;
	d[2] = (num / 10) % 10;
	d[3] = num % 10;

	for (int i = 0; i < 4; i++) {
		PORTG = 0x00;
		PORTB = font[d[i]];
		PORTG = select_digit[i];
		_delay_ms(2);
	}
}

int main(void) {
	DDRB = 0xFF;
	DDRG = 0xFF;

	while (1) {
		for (int num = 1; num <= 9999; num++) {
			for (int t = 0; t < 50; t++) {
				display_number(num);
			}
		}
	}
}