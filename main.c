/*
 * main.c
 *
 *  Created on: Feb 28, 2022
 *      Author: abdelrahman
 */
#include"lcd.h"
#include"ultrasonic.h"
#include<avr/io.h>
#include<avr/interrupt.h>

int main() {
	LCD_init(); /*initiating LCD */
	Ultrasonic_init();/*initiating Ultra-Sonic*/
	SREG |= (1 << 7); /*Enable interrupt Because callback Function in ICU */
	LCD_displayString("Distance =    cm");
	while (1) {
		LCD_moveCursor(0, 11);
		LCD_intgerToString(Ultrasonic_readDistance());
		if (Ultrasonic_readDistance() < 100)
		{
			 LCD_displayCharacter(' ');
		}
	}
}
