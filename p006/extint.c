#include "extint.h"
#include "usbd12.h"

void extint0_isr(void) __interrupt (0)
{
	u8 val = 0;

	usbd12_write_cmd(READ_INT_REG);
	val = usbd12_read_byte();
	if (val & SUSPEND_CHANGE);
	if (val & BUS_RESET);
	if (val & EP2_IN);
	if (val & EP2_OUT);
	if (val & EP1_IN);
	if (val & EP1_OUT);
	if (val & EP0_IN);
	if (val & EP0_OUT);

	val = usbd12_read_byte();
	if (val & DMA_EOT);
}

void extint1_isr(void) __interrupt (2)
{
}

void extint_init(u8 pin, u8 trigger_type)
{
	if (INT0 == pin) {
		IT0 = trigger_type;
		EX0 = 1;
	}

	if (INT1 == pin) {
		IT1 = trigger_type;
		EX1 = 1;
	}
}

