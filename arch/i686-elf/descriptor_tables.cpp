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
#include "interrupts.h"
#include <mem.h>

#define N_IDT_ENTRIES 256

/**
 * Specifically initializes the Global Descriptor Table for use.
 */
/* static */ void init_gdt();
/**
 * Sets up one GDT entry
 * @param s32 which GDT entry to set up
 * @param u32 the base of this GDT entry
 * @param u32 the limit of this GDT entry
 * @param u8  the access level of this GDT entry
 * @param u8  the granularity of this GDT entry
 */
/* static */ void gdt_set_gate(s32, u32, u32, u8, u8);

/* static */ void init_idt();
/* static */ void idt_set_gate(u8, u32, u16, u8);

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

/* static */ gdt_entry  gdt_entries[5];
/* static */ gdt_ptr    gdt_entries_ptr;
/* static */ idt_entry  idt_entries[N_IDT_ENTRIES];
/* static */ idt_ptr    idt_entries_ptr;

void init_descriptor_tables()
{
  // allow the kernel to init both tables at once
  init_gdt();
  init_idt();
}

/* static */ void init_gdt()
{
  gdt_entries_ptr.limit = (sizeof(gdt_entry) * 5) - 1;
  gdt_entries_ptr.base = reinterpret_cast<u32>(&gdt_entries);

  gdt_set_gate(0, 0, 0, 0, 0); // null segment
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);   // kernel code segment
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);   // kernel data segment
  //gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);   // user mode code segment
  //gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);   // user mode data segment

  gdt_flush(&gdt_entries_ptr);
}

/* static */ void gdt_set_gate(s32 num, u32 base, u32 limit, u8 access, u8 gran)
{
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_mid = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low = (limit & 0xFFFF);
  gdt_entries[num].granularity = (limit >> 16) & 0x0F;

  gdt_entries[num].granularity |= gran & 0xF0;
  gdt_entries[num].access = access;
}

/* static */ void init_idt()
{
  idt_entries_ptr.limit = sizeof(idt_entry) * N_IDT_ENTRIES - 1;
  idt_entries_ptr.base = reinterpret_cast<u32>(&idt_entries);

  memset(&idt_entries, 0, sizeof(idt_entry) * N_IDT_ENTRIES);

  // Set up the actual idt using our functions, and flush it to disk
  idt_set_gate(0, reinterpret_cast<u32>(isr0), 0x08, 0x8E);
  idt_set_gate(1, reinterpret_cast<u32>(isr1), 0x08, 0x8E);
  idt_set_gate(2, reinterpret_cast<u32>(isr2), 0x08, 0x8E);
  idt_set_gate(3, reinterpret_cast<u32>(isr3), 0x08, 0x8E);
  idt_set_gate(4, reinterpret_cast<u32>(isr4), 0x08, 0x8E);
  idt_set_gate(5, reinterpret_cast<u32>(isr5), 0x08, 0x8E);
  idt_set_gate(6, reinterpret_cast<u32>(isr6), 0x08, 0x8E);
  idt_set_gate(7, reinterpret_cast<u32>(isr7), 0x08, 0x8E);
  idt_set_gate(8, reinterpret_cast<u32>(isr8), 0x08, 0x8E);
  idt_set_gate(9, reinterpret_cast<u32>(isr9), 0x08, 0x8E);
  idt_set_gate(10, reinterpret_cast<u32>(isr10), 0x08, 0x8E);
  idt_set_gate(11, reinterpret_cast<u32>(isr11), 0x08, 0x8E);
  idt_set_gate(12, reinterpret_cast<u32>(isr12), 0x08, 0x8E);
  idt_set_gate(13, reinterpret_cast<u32>(isr13), 0x08, 0x8E);
  idt_set_gate(14, reinterpret_cast<u32>(isr14), 0x08, 0x8E);
  idt_set_gate(15, reinterpret_cast<u32>(isr15), 0x08, 0x8E);
  idt_set_gate(16, reinterpret_cast<u32>(isr16), 0x08, 0x8E);
  idt_set_gate(17, reinterpret_cast<u32>(isr17), 0x08, 0x8E);
  idt_set_gate(18, reinterpret_cast<u32>(isr18), 0x08, 0x8E);
  idt_set_gate(19, reinterpret_cast<u32>(isr19), 0x08, 0x8E);
  idt_set_gate(20, reinterpret_cast<u32>(isr20), 0x08, 0x8E);
  idt_set_gate(21, reinterpret_cast<u32>(isr21), 0x08, 0x8E);
  idt_set_gate(22, reinterpret_cast<u32>(isr22), 0x08, 0x8E);
  idt_set_gate(23, reinterpret_cast<u32>(isr23), 0x08, 0x8E);
  idt_set_gate(24, reinterpret_cast<u32>(isr24), 0x08, 0x8E);
  idt_set_gate(25, reinterpret_cast<u32>(isr25), 0x08, 0x8E);
  idt_set_gate(26, reinterpret_cast<u32>(isr26), 0x08, 0x8E);
  idt_set_gate(27, reinterpret_cast<u32>(isr27), 0x08, 0x8E);
  idt_set_gate(28, reinterpret_cast<u32>(isr28), 0x08, 0x8E);
  idt_set_gate(29, reinterpret_cast<u32>(isr29), 0x08, 0x8E);
  idt_set_gate(30, reinterpret_cast<u32>(isr30), 0x08, 0x8E);
  idt_set_gate(31, reinterpret_cast<u32>(isr31), 0x08, 0x8E);

  idt_flush(&idt_entries_ptr);
}

/* static */ void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
  idt_entries[num].base_lo = base & 0xFFFF;
  idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags;
}
