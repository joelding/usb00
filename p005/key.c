#include "key.h"

#define STABLE 2
#define CURR 1
#define PREV 0

typedef struct {
	volatile u8 val[3];
	volatile u8 cnt;
} key_t;

static key_t key = {{0, 0, 0}, 0, 0, 0, 0};
static u8 is_getting = 0;

void key_isr(void) __interrupt (1) __using (2)
{
	TH0 = (65535 - FCLK / 1000 / 12 * 5) / 256; /* 5ms */
	TL0 = (65535 - FCLK / 1000 / 12 * 5) % 256;
	
	if (is_getting) return;

	key.val[CURR] = ~P1;

	if (key.val[PREV] != key.val[CURR]) {
		key.cnt = 0;
		key.val[PREV] = key.val[CURR];
		return;
	} else {
		if ((++key.cnt) > 20) { /* 100ms */
			key.cnt = 0;
			key.val[STABLE] = key.val[PREV];
		}
	}
}

void key_init(void)
{
	/* set timer 0 as mode 1 */
	TMOD &= 0xF0;
	TMOD |= 0x01;
	TH0 = (65535 - FCLK / 1000 / 12 * 5) / 256; /* 5ms */
	TL0 = (65535 - FCLK / 1000 / 12 * 5) % 256;
	ET0 = 1; /* enable timer 0 interrupt */
	TR0 = 1; /* enable timer 0 */

	is_getting = 0;
}

u8 key_get_val(void)
{
	u8 val = 0;

	is_getting = 1;
	val = key.val[STABLE];
	is_getting = 0;

	return val;
}

