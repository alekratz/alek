.global init
.extern kmain

init:
  mov sp,#0x80000
  bl kmain
  b hang$
hang$:
  b hang$
