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

void usbd12_write_cmd(u8 cmd)
{
	USBD12_A0 = CMD;
	USBD12_WR = 0;
	USBD12_DATA = cmd;
	USBD12_WR = 1;
	USBD12_DATA = 0xFF;
}

u16 usbd12_read_id(void)
{
	u16 retval = 0;

	usbd12_write_cmd(READ_ID);
	retval = usbd12_read_byte();
	retval |= ((u16)usbd12_read_byte()) << 8;

	return retval;
}
