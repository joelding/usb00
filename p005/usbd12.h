/** PDIUSBD12 chip
 */
#ifndef _USBD12_H_
#define _USBD12_H_

#include "common.h"

#define USBD12_DATA P0
#define USBD12_A0 P3_5
#define USBD12_WR P3_6
#define USBD12_RD P3_7
#define USBD12_INT P3_2

#define CMD 1
#define DATA 0

/* 11.2 initialization commands */
#define SET_ADDR_EN (0xD0)
#define SET_EP_EN (0xD8)
#define SET_MODE (0xF3)
#define SET_DMA (0xFB)

/* 11.3 data flow commands */
#define READ_INT_REG (0xF4)
/* TODO
 * #define SELECT_EP ()
 * 0x0 to 0x5
 */
/* TODO
 * #define READ_EP_STATUS ()
 * 0x80 to 0x85
 */
/* TODO
 * #define READ_LAST_TRANSACT_STATUS_REG ()
 * 0x40 to 0x45
 */
#define READ_BUFFER (0xF0)
#define WRITE_BUFFER (0xF0)
#define CLEAR_BUFFER (0xF2)
#define VALIDATE_BUFFER (0xFA)
/* TODO
 * #define SET_ENDPOINT_STATUS ()
 * 0x40 to 0x45
 */
#define ACKNOWLEDGE_SETUP (0xF1)

/* 11.4 general commands */
#define SEND_RESUME (0xF6)
#define READ_CURR_FRAME_NUMBER (0xF5)
#define READ_ID (0xFD)

u8 usbd12_read_byte(void);
void usbd12_write_cmd(u8 cmd);
u16 usbd12_read_id(void);

#endif /* _USBUSBD12_H_ */

