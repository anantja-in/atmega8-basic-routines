#include<avr/io.h>
#include "uart.h"

int main(void) {
	DDRD = 0xc0;
	PORTD = 0x1c;
	uart_init();
	/* First initialize DDRD and then uart. o/w when initializing DDRD later,
	selectively set bits 2 and 3 to 0. e.g. DDRD &=F3*/
	while(1) {
		if(!(PIND & 0x04))
			uart_tx_string("\n\rSwitch 1 is pressed.");
		else if (!(PIND & 0x08))
			uart_tx_string("\n\rSwitch 2 is pressed.");
		if (!(PIND & 0x04) & !(PIND & 0x08))
			uart_tx_string("\n\rBoth switches are pressed.");
		else
			uart_tx_string("\n\rNo switch is pressed.");
		
	}
	return 0;
}
	