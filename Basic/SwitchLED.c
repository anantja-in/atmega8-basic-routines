#include <avr/io.h>

int main (void) {

	DDRD = 0xc0;
	PORTD = 0x1c;
	
	while(1) {
		if(!(PIND & 0x04))
			PORTD = 0x7F;
		else if (!(PIND & 0x08))
			PORTD = 0xBF;
		if (!(PIND & 0x04) & !(PIND & 0x08))
			PORTD = 0x3F;
		else
			PORTD = 0xFF;
	}
	return 0;
}