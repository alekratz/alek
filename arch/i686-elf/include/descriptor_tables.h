/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALEK_GDT_H
#define ALEK_GDT_H

/*
sources:
http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
http://www.osdever.net/bkerndev/Docs/idt.htm
http://www.osdever.net/bkerndev/Docs/gdt.htm
 */

#include <types.h>

void init_gdt();
void init_idt();
void init_irq();

void idt_set_gate(u8, u32, u16, u8);

#endif /* ALEK_GDT_H */