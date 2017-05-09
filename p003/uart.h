#ifndef _UART_H_
#define _UART_H_

#define PARITY_NONE	(0)
#define PARITY_ODD	(1)
#define PARITY_EVEN	(2)
#define PARITY_MARK	(3)
#define PARITY_SPACE	(4)
#define PARITY_BIT	PARITY_NONE

void uart_init(unsigned long baudrate);

#endif

