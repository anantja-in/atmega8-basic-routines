#include <avr/io.h>

int main(void) {
	DDRB = 0x1E;
	PORTB = 0x1E;
	
	DDRD = 0x00;
	PORTD = 0x03;
	
	/* 	PORT D0 : Left sensor
		PORT D1 : Front sensor
		PORT D2 : Right sensor
	*/
	
	/* Assume white is high */
	while(1) {
		if(!(PIND & 0x01)) {
			/* Left sensor is on black */
			PORTB = 0x08;
		}
		else if (!(PIND & 0x04)) {
			/* right sensor is on black */
			PORTB = 0x04;
		}
		else
			PORTB = 0x0C;

	}
	return 0;
}