/*
 * Led2.c
 *
 * Created: 2025-08-11 오후 3:48:33
 * Author : COMPUTER
	shift
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	unsigned char LED = 0x01;
    DDRE = 0xff; //PORTE를 출력핀으로 설정
    while (1) 
    {
		
		while(1)
		{	
			PORTE = LED;

			_delay_ms(500);
			LED = LED <<3;
			
			if(LED ==0x01)
			break;
		}
    }
}

