#include<avr/io.h>

int main (void) {
	TCNT0 = 0x63;
	TCCR0 = 0x05;
	DDRD = 0xc0;
	PORTD = 0xc0;
	DDRB = 0x1E;
	PORTB = 0x1E;
	while(1) {
		for(int i=0;i!=10;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
			
		}
		PORTD ^= 0xc0;
		PORTB ^= 0x12;
	}
	return 0;
}