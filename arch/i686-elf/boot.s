# Constants used for creating a multiboot header
.set ALIGN,   1 << 0              # align loaded modules on page boundaries
.set MEMINFO, 1 << 1              # provide memory map
.set FLAGS,   ALIGN | MEMINFO     # multiboot 'flag' field
.set MAGIC,   0x1BADB002          # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)   # checksum of above

# Multiboot header
.section multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Set up the stack
.section bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KB
stack_top:

# text section
.section .text
.global start
.type start, @function
start:
  # Set %esp
  movl $stack_top, %esp
  # Jump into the kernel
  call kmain
  cli
  hlt
.Lhang:
  jmp .Lhang