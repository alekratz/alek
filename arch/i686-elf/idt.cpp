#include "descriptor_tables.h"
#include "interrupts.h"
#include <mem.h>

struct idt_entry
{
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

#define N_IDT_ENTRIES 256

static idt_entry  idt_entries[N_IDT_ENTRIES];
static idt_ptr    idt_entries_ptr;

/**
 * Writes the IDT. This is defined in idt_flush.s.
 * @param ptr pointer to a idt_ptr struct
 */
extern "C" void idt_flush(const idt_ptr* ptr);

void init_idt()
{
  idt_entries_ptr.limit = (sizeof(idt_entry) * N_IDT_ENTRIES) - 1;
  idt_entries_ptr.base = reinterpret_cast<u32>(&idt_entries);

  memset(&idt_entries, 0, sizeof(idt_entry) * N_IDT_ENTRIES);

  // Set up the actual idt using our functions, and flush it to disk
  idt_set_gate(0, AS_U32(isr0), 0x08, 0x8E);
  idt_set_gate(1, AS_U32(isr1), 0x08, 0x8E);
  idt_set_gate(2, AS_U32(isr2), 0x08, 0x8E);
  idt_set_gate(3, AS_U32(isr3), 0x08, 0x8E);
  idt_set_gate(4, AS_U32(isr4), 0x08, 0x8E);
  idt_set_gate(5, AS_U32(isr5), 0x08, 0x8E);
  idt_set_gate(6, AS_U32(isr6), 0x08, 0x8E);
  idt_set_gate(7, AS_U32(isr7), 0x08, 0x8E);
  idt_set_gate(8, AS_U32(isr8), 0x08, 0x8E);
  idt_set_gate(9, AS_U32(isr9), 0x08, 0x8E);
  idt_set_gate(10, AS_U32(isr10), 0x08, 0x8E);
  idt_set_gate(11, AS_U32(isr11), 0x08, 0x8E);
  idt_set_gate(12, AS_U32(isr12), 0x08, 0x8E);
  idt_set_gate(13, AS_U32(isr13), 0x08, 0x8E);
  idt_set_gate(14, AS_U32(isr14), 0x08, 0x8E);
  idt_set_gate(15, AS_U32(isr15), 0x08, 0x8E);
  idt_set_gate(16, AS_U32(isr16), 0x08, 0x8E);
  idt_set_gate(17, AS_U32(isr17), 0x08, 0x8E);
  idt_set_gate(18, AS_U32(isr18), 0x08, 0x8E);
  idt_set_gate(19, AS_U32(isr19), 0x08, 0x8E);
  idt_set_gate(20, AS_U32(isr20), 0x08, 0x8E);
  idt_set_gate(21, AS_U32(isr21), 0x08, 0x8E);
  idt_set_gate(22, AS_U32(isr22), 0x08, 0x8E);
  idt_set_gate(23, AS_U32(isr23), 0x08, 0x8E);
  idt_set_gate(24, AS_U32(isr24), 0x08, 0x8E);
  idt_set_gate(25, AS_U32(isr25), 0x08, 0x8E);
  idt_set_gate(26, AS_U32(isr26), 0x08, 0x8E);
  idt_set_gate(27, AS_U32(isr27), 0x08, 0x8E);
  idt_set_gate(28, AS_U32(isr28), 0x08, 0x8E);
  idt_set_gate(29, AS_U32(isr29), 0x08, 0x8E);
  idt_set_gate(30, AS_U32(isr30), 0x08, 0x8E);
  idt_set_gate(31, AS_U32(isr31), 0x08, 0x8E);

  idt_flush(&idt_entries_ptr);
}

void idt_set_gate(u8 num, u32 base, u16 sel, u8 flags)
{
  idt_entries[num].base_lo = base & 0xFFFF;
  idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

  idt_entries[num].sel = sel;
  idt_entries[num].always0 = 0;
  idt_entries[num].flags = flags;
}
