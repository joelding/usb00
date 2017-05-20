#include "common.h"
#include "uart.h"
#include "tmr.h"
#include "usbd12.h"
#include "extint.h"

void main(void)
{
//	u8 keyval[2] = {0};
u32 val;

	uart_init(115200UL);
	tmr0_init();
	extint_init(INT0, TRIGGER_FALLING_EDGE);
	P2 = 0x55;
	EA = 1;
	
	printf("build: %s %s\r\n", __TIME__, __DATE__);	

	printf("USBD12 0x%04X\r\n", usbd12_read_id());

	while (1) {
		val = get_clk();

		if (!(val & 0x3FF)) P2 = ~P2;

		usbd12_isr_handler(&g_isr);
	}
}

