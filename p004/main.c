#include "uart.h"
#include "key.h"

void main(void)
{
	u8 keyval[2] = {0};

	uart_init(115200UL);
	key_init();
	P2 = 0xff;
	EA = 1;
	
	printf("build: %s %s\r\n", __TIME__, __DATE__);	

	while (1) {
#if 0
		if (!toggle) {
			val = ~val;
			P2 = val;
		} 
#endif
		keyval[1] = key_get_val();
		if (keyval[0] != keyval[1]) {
			keyval[0] = keyval[1];
			printf("%02X\r\n", keyval[0]);
			P2 = ~keyval[0];
		}
	}
}

