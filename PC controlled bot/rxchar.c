#include<avr/io.h>
#include "uart.h"

int main(void) {
	uart_init();
	while(1) {
		uart_tx_char(uart_rx_char());
	}
	return 0;
}
