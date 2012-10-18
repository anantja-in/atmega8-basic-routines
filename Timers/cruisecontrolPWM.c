#include<avr/io.h>
#include "uart.h"

unsigned char d5,d4,d3,d2,d1;
unsigned int temp,a;

void hextobcd(unsigned int hex) {
	d1= hex/10000;
	temp = hex%10000;
	d2 = temp/1000;
	temp = hex%1000;
	d3 = temp/100;
	temp = hex%100;
	d4 = temp/10;
	d5 = temp%10;
}

void speed(int j, int mode) {
	if(j>30) j=30;
		if(mode == 1) 
			PORTB = 0x12;
		else if (mode==-1)
			PORTB = 0x0c;
			
		for(int i=0;i!=j;i++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); /* Timer restarts as soon as you configure this. 
			Hence TCNT0 must be written before TIFR */
		}
		PORTB = 0x00;
		for(int k=0;k!=30-j;k++) {
			while(!(TIFR & (1<<TOV0)));
			TCNT0 = 0x63;
			TIFR |= (1<<TOV0); 
		}

}

int main (void) {
	TCNT0 = 0x63;
	TCCR0 = 0x03;
	DDRB = 0x1E;
	PORTB = 0x1E;
	
	ADMUX = 0x40;
	ADCSRA = 0xE7;
	uart_init();
	
	while(1) {
		while(!(ADCSRA & (1<<ADIF)));
		a=ADC;
		if (a<0x64) {
			int b = 0x64-a;
			speed(b,1);
			uart_tx_string("Moving forward !!! Value = ");
		}
		else {
			int b = a-0x64;
			speed(b,-1);
			uart_tx_string("Moving backward!!! Value = ");
		}
		hextobcd(a);
		uart_tx_char(d1+0x30);
		uart_tx_char(d2+0x30);
		uart_tx_char(d3+0x30);
		uart_tx_char(d4+0x30);
		uart_tx_char(d5+0x30);
		uart_tx_char('\n');
		uart_tx_char('\r');
		
	}
	return 0;
}