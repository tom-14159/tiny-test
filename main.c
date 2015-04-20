#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <avr/interrupt.h>

#define BUFF_SIZE	32
#define USART_RATE	9600
#define UBRR_VALUE (((F_CPU / (USART_RATE * 16UL))) - 1)

char str_buff[BUFF_SIZE];

void usart_init(void) {
	// Set baud rate
	UBRRH = (uint8_t)(UBRR_VALUE>>8);
	UBRRL = (uint8_t)UBRR_VALUE;

	// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSRC |= (1<<UCSZ1)|(1<<UCSZ0);

	//enable transmission and reception
	UCSRB |= (1<<RXEN)|(1<<TXEN);
}

void send_str(char* str) {
	int pos = 0;
	while (str[pos] != '\0') {
		while(!(UCSRA&(1<<UDRE))){};
		UDR = str[pos];
	}

	while(!(UCSRA&(1<<UDRE))){};
	UDR = '\r';
}

int main (void) {
	usart_init();

	while(1) {
	}

	return 0;
}
