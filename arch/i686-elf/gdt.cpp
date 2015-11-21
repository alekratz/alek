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

#include "descriptor_tables.h"
#include <mem.h>

#define N_GDT_ENTRIES 5
/**
 * Sets up one GDT entry
 * @param s32 which GDT entry to set up
 * @param u32 the base of this GDT entry
 * @param u32 the limit of this GDT entry
 * @param u8  the access level of this GDT entry
 * @param u8  the granularity of this GDT entry
 */
static void gdt_set_gate(s32, u32, u32, u8, u8);

struct gdt_entry
{
  u16 limit_low;    // lower 16 bits of the limit
  u16 base_low;     // lower 16 bits of the base
  u8  base_mid;     // the next 8 bits of the base
  u8  access;       // access permissions of this segment
  u8  granularity;  // 0 = bytes, 1 = kilobytes
  u8  base_high;    // last 8 bits of the base
} __attribute__((packed));

struct gdt_ptr
{
  u16 limit;    // upper 16 bits of all selector limits
  u32 base;     // address of the first gdt_entry
} __attribute__((packed));

static_assert(sizeof(gdt_entry) == 8, "gdt_entry is not 8 bytes long");

/**
 * Writes the GDT. This is defined in gdt_flush.s.
 * @param ptr pointer to a gdt_ptr struct
 */
extern "C" void gdt_flush(const gdt_ptr* ptr);

static gdt_entry  gdt_entries[N_GDT_ENTRIES];
static gdt_ptr    gdt_entries_ptr;

void init_gdt()
{
  gdt_entries_ptr.limit = (sizeof(gdt_entry) * N_GDT_ENTRIES) - 1;
  gdt_entries_ptr.base = reinterpret_cast<u32>(&gdt_entries);

  gdt_set_gate(0, 0, 0, 0, 0); // null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // kernel code segment:     0x08
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // kernel data segment:     0x10
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // user mode code segment:  0x18
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // user mode data segment:  0x20

  gdt_flush(&gdt_entries_ptr);
}

static void gdt_set_gate(s32 num, u32 base, u32 limit, u8 access, u8 gran)
{
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_mid = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F;

  gdt_entries[num].granularity |= gran & 0xF0;
  gdt_entries[num].access = access;
}