#include "usbd12.h"

u8 usbd12_read_byte(void)
{
	u8 retval;

	USBD12_A0 = DATA;
	USBD12_RD = 0;
	retval = USBD12_DATA;
	USBD12_RD = 1;

	return retval;
}

void usbd12_write_byte(u8 addr, u8 data)
{
	USBD12_A0 = addr;
	USBD12_WR = 0;
	USBD12_DATA = data;
	USBD12_WR = 1;
	USBD12_DATA = 0xFF;
}

u16 usbd12_read_id(void)
{
	u16 retval = 0;

	usbd12_write_byte(CMD, READ_ID);
	retval = usbd12_read_byte();
	retval |= ((u16)usbd12_read_byte()) << 8;

	return retval;
}

void usbd12_is_plugin(bool is_plugin)
{
	usbd12_write_byte(CMD, SET_MODE);

	if (is_plugin) {
		usbd12_write_byte(DATA,
				  MODE_NON_ISO | BUS_CONN | 
				  INTMOD_OK | CLOCK_RUNNING |
				  SET_LAZYCLK);
		usbd12_write_byte(DATA, DMA_RDWR | CLK_DIV);

	} else {
		usbd12_write_byte(DATA,
				  MODE_NON_ISO | BUS_DISCONN | 
				  INTMOD_OK | CLOCK_RUNNING |
				  SET_LAZYCLK);
		usbd12_write_byte(DATA, DMA_RDWR | CLK_DIV);
		delayms(1000); // delay 1s
	}
}

void usbd12_isr_handler(void *arg)
{
	u8 val = ((struct _isr_status *)arg)->usbd12_intreg[0];

	if (val & SUSPEND_CHANGE) {
		//TODO
		printf("SUSPEND_CHANGE\r\n");
	}

	if (val & BUS_RESET) {
		//TODO
		printf("BUS_RESET\r\n");
	}

	if (val & EP2_IN) {
		//TODO
		printf("EP2_IN\r\n");
	}

	if (val & EP2_OUT) {
		//TODO
		printf("EP2_OUT\r\n");
	}

	if (val & EP1_IN) {
		printf("EP1_IN\r\n");
	}

	if (val & EP1_OUT) {
		printf("EP1_OUT\r\n");
	}

	if (val & EP0_IN) {
		printf("EP0_IN\r\n");
	}

	if (val & EP0_OUT) {
		printf("EP0_OUT\r\n");
	}
	
	((struct _isr_status *)arg)->usbd12_intreg[0] = 0;
}

