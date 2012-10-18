#include <avr/io.h>

void _delay_ms(unsigned int t) {
	unsigned int i,j;
	for (j=0;j<t;j++) {
		for(i=0;i<6500;i++) {}
	}
}

int main(void) {
	DDRD = 0xff;
	PORTD = 0x00;
	while(1) {
		PORTD = PORTD ^ 0xff;
		_delay_ms(80);
	}
	return 0;
}
