#include "descriptor_tables.h"
#include "interrupts.h"
#include "cpu_io.h"

#include <types.h>

static void irq_remap();

static void irq_remap()
{
  // Send initialization code
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  // Set up the offsets
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  // Tell master PIC that there is a slave PIC at IRQ2
  outb(0x21, 0x04);
  // Tell slave PIC its cascade identity
  outb(0xA1, 0x02);
  // 8086 mode
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  // Clear PIC masks
  outb(0x21,  0x0);
  outb(0xA1,  0x0);
}

void init_irq()
{
  irq_remap();
  idt_set_gate(32, AS_U32(irq0),  0x08, 0x8E);
  idt_set_gate(33, AS_U32(irq1),  0x08, 0x8E);
  idt_set_gate(34, AS_U32(irq2),  0x08, 0x8E);
  idt_set_gate(35, AS_U32(irq3),  0x08, 0x8E);
  idt_set_gate(36, AS_U32(irq4),  0x08, 0x8E);
  idt_set_gate(37, AS_U32(irq5),  0x08, 0x8E);
  idt_set_gate(38, AS_U32(irq6),  0x08, 0x8E);
  idt_set_gate(39, AS_U32(irq7),  0x08, 0x8E);
  idt_set_gate(40, AS_U32(irq8),  0x08, 0x8E);
  idt_set_gate(41, AS_U32(irq9),  0x08, 0x8E);
  idt_set_gate(42, AS_U32(irq10), 0x08, 0x8E);
  idt_set_gate(43, AS_U32(irq11), 0x08, 0x8E);
  idt_set_gate(44, AS_U32(irq12), 0x08, 0x8E);
  idt_set_gate(45, AS_U32(irq13), 0x08, 0x8E);
  idt_set_gate(46, AS_U32(irq14), 0x08, 0x8E);
  idt_set_gate(47, AS_U32(irq15), 0x08, 0x8E);
}