#include "uart.h"

void main(void)
{
	unsigned char c = 0;

	P2 = 0;
	uart_init(115200UL);
//	timer0_init(100);
	EA = 1;
	printf("build: %s %s\r\n", __TIME__, __DATE__);	
	while (1) {
		printf("%u\r\n", c++);
	}
}

