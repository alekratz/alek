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

struct gdt_entry
{
  gdt_entry() = default;
  gdt_entry(u16 limit_low, u16 base_low, u8 base_middle, u8 access, u8 granularity, u8 base_high)
    : limit_low(limit_low)
    , base_low(base_low)
    , base_mid(base_middle)
    , access(access)
    , granularity(granularity)
    , base_high(base_high) { }

  u16 limit_low;    // lower 16 bits of the limit
  u16 base_low;     // lower 16 bits of the base
  u8  base_mid;     // the next 8 bits of the base
  u8  access;       // access permissions of this segment
  u8  granularity;  // 0 = bytes, 1 = kilobytes
  u8  base_high;    // last 8 bits of the base
} __attribute__((packed));

struct gdt_ptr
{
  gdt_ptr() = default;
  gdt_ptr(u16 limit, u32 base)
    : limit(limit)
    , base(base) { }

  u16 limit;    // upper 16 bits of all selector limits
  u32 base;     // address of the first gdt_entry
} __attribute__((packed));

// Essential for correct operation of the machine/kernel
static_assert(sizeof(gdt_entry) == 8, "gdt_entry is not 8 bytes long");
// This is less essential
//static_assert(sizeof(gdt_ptr) == 6, "gdt_ptr is not 6 bytes long");

struct idt_entry
{
  idt_entry() = default;
  idt_entry(u16 base_lo, u16 sel, u16 base_hi)
    : base_lo(base_lo)
    , sel(sel)
    , always0(0)
    , base_hi(base_hi) { }

  u16 base_lo;    // lower 16 bits of the address to jump to when this interrupt fires
  u16 sel;        // kernel segment selector
  u8  always0;    // this is always zero. x86 logic
  u8  flags;      // flags (duh)
  u16 base_hi;    // the upper 16 bits of the address to jump to
} __attribute__((packed));

struct idt_ptr
{
  u16 limit;
  u32 base;       // Address of the first element in the array
} __attribute__((packed));

void init_descriptor_tables();

#endif /* ALEK_GDT_H */