#include<avr/io.h>
#include "uart.h"

int main(void) {
	uart_init();
	while(1) {
		char string[] = "Hello World !\t";
		int a=0;
		while(string[a] !='\0') {
			uart_tx_char(string[a]);
			a+=1;
		}
		
	}
	return 0;
}
