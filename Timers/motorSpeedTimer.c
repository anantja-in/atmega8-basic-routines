#include<avr/io.h>

void accelerate() {
	for(int j=0;j<100;j++) {
		PORTB = 0x12;
		for(int i=0;i!=j;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
		}
		PORTB = 0x00;
		for(int k=0;k!=100-j;k++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); 
		}
		}
		PORTB = 0x12;
}

void wait(int time) {
	for(int i=0;i!=time;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
		}
}

void decelerate() {
		for (int j=0;j<100;j++) { 
		PORTB = 0x00;
		for(int i=0;i!=j;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
		}
		PORTB = 0x12;
		for(int k=0;k!=100-j;k++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); 
		}
		}
		PORTB = 0x00;
}

int main (void) {
	TCNT0 = 0x63;
	TCCR0 = 0x03;
	DDRB = 0x1E;
	PORTB = 0x1E;
	int j=0; 
	while(1) {
		accelerate();
		wait(300);
		decelerate();
		wait(300);
		
	}
	return 0;
}