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

#define N_IDT_ENTRIES 256

/**
 * Specifically initializes the Global Descriptor Table for use.
 */
static void init_gdt();
/**
 * Sets up one GDT entry
 * @param s32 which GDT entry to set up
 * @param u32 the base of this GDT entry
 * @param u32 the limit of this GDT entry
 * @param u8  the access level of this GDT entry
 * @param u8  the granularity of this GDT entry
 */
static void gdt_set_gate(s32, u32, u32, u8, u8);

static void init_idt();
static void idt_set_gate(u8, u32, u16, u8);

/**
 * Writes the GDT. This is defined in gdt_flush.s.
 * @param ptr pointer to a gdt_ptr struct
 */
extern "C" void gdt_flush(const gdt_ptr* ptr);
/**
 * Writes the IDT. This is defined in idt_flush.s.
 * @param ptr pointer to a idt_ptr struct
 */
extern "C" void idt_flush(const idt_ptr* ptr);

static gdt_entry  gdt_entries[5];
static gdt_ptr    gdt_entries_ptr;
static idt_entry  idt_entries[N_IDT_ENTRIES];
static idt_ptr    idt_entries_ptr;

void init_descriptor_tables()
{
  // allow the kernel to init both tables at once
  init_gdt();
  init_idt();
}

static void init_gdt()
{
  gdt_entries_ptr.limit = (sizeof(gdt_entry) * 5) - 1;
  gdt_entries_ptr.base = reinterpret_cast<u32>(&gdt_entries);

  gdt_set_gate(0, 0, 0, 0, 0); // null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // data segment
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // user mode code segment
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // user mode data segment

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

static void init_idt()
{
  idt_entries_ptr.limit = sizeof(idt_entry) * N_IDT_ENTRIES - 1;
  idt_entries_ptr.base = reinterpret_cast<u32>(&idt_entries);

  memset(&idt_entries, 0, sizeof(idt_entries) * N_IDT_ENTRIES);

}

static void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
  idt_entries[num].base_lo = base & 0xFFFF;
  idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags;
}