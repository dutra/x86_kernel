#include <idt.h>
#include <types.h>
#include <lib.h>
#include <asm.h>

static void idt_set_gate(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags);

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

void init_idt()
{

  // Remap the irq table.
  outb(0x20, 0x11);
  outb(0xA0, 0x11);
  outb(0x21, 0x20);
  outb(0xA1, 0x28);
  outb(0x21, 0x04);
  outb(0xA1, 0x02);
  outb(0x21, 0x01);
  outb(0xA1, 0x01);
  outb(0x21, 0x0);
  outb(0xA1, 0x0);

  idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
  idt_ptr.base  = (uint32_t)&idt_entries;

  memset(&idt_entries, 0, sizeof(idt_entry_t)*256);

  // set gates
  idt_set_gate(0, (uint32_t)isr0 , 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)isr1 , 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)isr2 , 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)isr3 , 0x08, 0x8E);

  idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
  idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
  idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
  idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
  idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
  idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
  idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
  idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
  idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
  idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
  idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
  idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
  idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
  idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
  idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
  idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
  
  idt_flush((uint32_t) &idt_ptr);
}

static void idt_set_gate(uint8_t num, uint32_t offset, uint16_t selector, uint8_t flags) {
  idt_entries[num].offset_low = offset & 0xFFFF;
  idt_entries[num].offset_high = (offset >> 16) & 0xFFFF;

  idt_entries[num].selector = selector;
  idt_entries[num].zero = 0;

  idt_entries[num].flags = flags;
}