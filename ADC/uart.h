
void uart_init (void) {
	UCSRA = 0x00;
	UCSRB = 0x18;
	UCSRC = 0x86;
	UBRRH=0; 
	UBRRL = 103;
}


void uart_tx_char(unsigned char data) {
	UDR = data;
	while(!(UCSRA & (1<<TXC)));
	UCSRA |= 0x40;
}

void uart_tx_string(char string[15]) {
		int a=0;
		while(string[a] !='\0') {
			uart_tx_char(string[a]);
			a+=1;
		}
}
	
unsigned char uart_rx_char (void) {
	while(!(UCSRA & (1<<RXC)));
	UCSRA |= 0x80;
	return UDR;
}