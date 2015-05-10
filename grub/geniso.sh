#!/bin/bash

BOOT=boot/
GRUB=$BOOT/grub
ISO=alek.iso

rm -f $ISO
cp ../kernel.elf $BOOT
grub-mkrescue -d /usr/lib/grub/i386-pc -o $ISO .

