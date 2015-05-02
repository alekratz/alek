MEMORY
{
  ram : ORIGIN = 0x8000, LENGTH = 0x5000
}

SECTIONS
{
  .text : {
    build/debug/boot.o;
    build/debug/kmain.o;
  } > ram
}