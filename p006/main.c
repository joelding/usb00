#include "uart.h"
#include "key.h"
#include "usbd12.h"

void main(void)
{
	u8 keyval[2] = {0};

	uart_init(115200UL);
	key_init();
	P2 = 0xff;
	EA = 1;
	
	printf("build: %s %s\r\n", __TIME__, __DATE__);	

	printf("USBD12 0x%04X\r\n", usbd12_read_id());

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
		}
	}
}

