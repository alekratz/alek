.global init
.extern kmain

init:
  mov sp,#0x8000
  bl kmain
  b hang$
hang$:
  b hang$
