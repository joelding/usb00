//#include <at89x52.h>
#include <stdio.h>
#include "stc89c5xrc.h"

#define FCLK 22118400UL /* Hz */
#define MAGIC 0
#define HI_BYTE (0)
#define LO_BYTE (1)

#define PARITY_NONE	(0)
#define PARITY_ODD	(1)
#define PARITY_EVEN	(2)
#define PARITY_MARK	(3)
#define PARITY_SPACE	(4)
#define PARITY_BIT	PARITY_NONE

void uart_init(unsigned long baudrate)
{
#if ((PARITY_BIT == PARITY_ODD) || \
     (PARITY_BIT == PARITY_EVEN) || \
     (PARITY_BIT == PARITY_MARK))
	SCON = 0xDA;
#elif (PARITY_BIT == PARITY_SPACE)
	SCON = 0xD2;
#else /* PARITY_NONE */
	SCON = 0x50;
#endif

	TMOD &= 0x0F; /* set timer 1 as mode 2, autoload */
	TMOD |= 0x20;
	TH1 = TL1 = 256 - (FCLK / (12 * 16 * baudrate));
	PCON |= 0x80;
	ES = 1; /* enable uart interrupt */
	TR1 = 1; /* start timer 1 */
	REN = 1; /* enable input */
}

static unsigned char is_tx_busy = 0;

void putchar(char c)
{
	while (is_tx_busy);

	ACC = c; /* calculate parity */

	if (P) {
#if (PARITY_BIT == PARITY_ODD)
		TB8 = 0;
#elif (PARITY_BIT == PARITY_EVEN)
		TB8 = 1;
#endif
	} else {
#if (PARITY_BIT == PARITY_ODD)
		TB8 = 1;
#elif (PARITY_BIT == PARITY_EVEN)
		TB8 = 0;
#endif

	}

	is_tx_busy = 1;
	SBUF = ACC;
}

void uart_isr(void) __interrupt (4) __using (1)
{
	char c = SBUF;

	if (RI) {
		RI = 0;
		printf("%c", c);
		if ('\r' == c)
			printf("\n");
	}

	if (TI) {
		TI = 0;
		is_tx_busy = 0;
	}
}

unsigned char t0_initval[2];
void timer0_init(unsigned ms)
{
	TMOD &= 0xF0; /* set timer0 as mode 1, 16-bit timer/counter */
	TMOD |= 0x01;
	
	TH0 = t0_initval[HI_BYTE] = (65536 - FCLK/1000/12 * ms - MAGIC) / 256;
	TL0 = t0_initval[LO_BYTE] = (65536 - FCLK/1000/12 * ms - MAGIC) % 256;
	
	ET0 = 1; /* enable timer0 interrupt */
	TR0 = 1; /* start timer0 */
}

volatile unsigned char val = 0x55;
//volatile unsigned cnt = 0;
volatile unsigned toggle = 0;
void timer0_isr(void) __interrupt (1) __using (1)
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

void main(void)
{
	char c;

	P2 = val;
	uart_init(115200UL);
	timer0_init(100);
	EA = 1;
	printf("build: %s %s\r\n", __TIME__, __DATE__);	
	while (1) {
#if 1 
		if (!toggle) {
			val = ~val;
			P2 = val;
		} 
#endif
	}
}

