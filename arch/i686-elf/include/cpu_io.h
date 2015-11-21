#ifndef ALEK_OUTB_H
#define ALEK_OUTB_H

#include <types.h>

extern "C" void outb(u32 port, u32 value);
extern "C" u8 inb(u32 port);

#endif