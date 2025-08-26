#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
// #include <stdio.h>  // snprintf 쓸 때만

int main(void){
	PortInit();
	LCD_Init();

	LCD_pos(0,0);
	LCD_STR((Byte*)"ATmega 128");
	LCD_pos(0,1);
	LCD_STR((Byte*)"Hello LCD");

	while(1){
		// 필요하면 여기서 갱신
		_delay_ms(500);
	}
}
