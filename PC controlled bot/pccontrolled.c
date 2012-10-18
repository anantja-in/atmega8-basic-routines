#include<avr/io.h>
#include<time.h>
#include "uart.h"

int main(void) {
	DDRB = 0x1E;
	PORTB = 0x1E;
	uart_init();
	unsigned char a;
	while(1) {
		a=uart_rx_char();
		if (a=='w') {
			PORTB = 0x12;
			uart_tx_string("Moving forward. \n\r");
		}
		else if (a=='a') {
			PORTB = 0x0A;
			uart_tx_string("Turning left.\n\r");
		}
		else if (a=='d') {
			PORTB = 0x14;
			uart_tx_string("Turning right.\n\r");
		}
		else if (a=='s') {
			PORTB = 0x0c;
			uart_tx_string("Moving backward.\n\r");
		}
		else if (a=='x') {
			PORTB = 0x00;
			uart_tx_string("STOP.\n\r");
		}
	}
	return 0;
}
	