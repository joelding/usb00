/** common.h: shared definitions, inclusions for usb00 board
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include "stc89c5xrc.h"

#define FCLK 22118400UL /* Hz */

/* sdcc provided basic data types
 * _Bool: 1 byte
 * char: 1 byte
 * short, int: 2 bytes
 * long: 4 bytes
 * float: 4 bytes
 */
typedef _Bool bool;
typedef unsigned char u8;
typedef char s8;
//typedef unsigned short u16;
typedef unsigned int u16;
typedef int s16;
typedef unsigned long u32;
typedef long s32;

#endif

