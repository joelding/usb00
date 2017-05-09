#include "common.h"
#include "timer.h"

//volatile unsigned cnt = 0;
volatile unsigned toggle = 0;
unsigned char t0_initval[2];

static void timer0_isr(void) __interrupt (1) __using (1)
{
	TR0 = 0; /* stop timer0 */
	TH0 = t0_initval[HI_BYTE];
	TL0 = t0_initval[LO_BYTE]; /*
	if (cnt > 100) {
		val= ~val;
		P2 = val;
		cnt = 0;
	} else {
		++cnt;
	}*/
	if (toggle > 10)
		toggle = 0;
	else
		toggle++;

	TR0 = 1; /* start timer0 */
}

void timer0_init(unsigned ms)
{
	TMOD &= 0xF0; /* set timer0 as mode 1, 16-bit timer/counter */
	TMOD |= 0x01;
	
	TH0 = t0_initval[HI_BYTE] = (65536 - FCLK/1000/12 * ms - MAGIC) / 256;
	TL0 = t0_initval[LO_BYTE] = (65536 - FCLK/1000/12 * ms - MAGIC) % 256;
	
	ET0 = 1; /* enable timer0 interrupt */
	TR0 = 1; /* start timer0 */
}


