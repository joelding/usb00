#ifndef _KEY_H_
#define _KEY_H_

#include "common.h"

void key_isr(void) __interrupt (1) __using (2);
u8 key_get_val(void);
void key_init(void);

#endif // _KEY_H_

