#!/bin/bash

echo "Grabbing firmware"
mkdir -p boot
to_get=("fixup.dat" "bootcode.bin" "start.elf")
for get in ${to_get[@]}; do
  echo "== GETTING $get"
  wget https://github.com/raspberrypi/firmware/raw/master/boot/$get -O boot/$get
done
echo "Done"