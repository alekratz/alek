#!/bin/bash
#
# Copyright (C) 2015 Alek Ratzloff
# 
# This file is part of Alek's Little Endian Kernel.
# 
# Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Alek's Little Endian Kernel is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
#
# This file will generate the raspberry pi boot image

print_help() {
	echo "usage: $0 [options]"
	echo "options:"
	echo "-v ........................ verbose output"
	echo "-? -h ..................... print this help message"
}

vecho() {
	if [[ $verbose == 1 ]]; then echo $*; fi
}

if [[ $# -gt 0 ]]; then	
	while getopts "hv" OPT; do
		case $OPT in
			\?)
				echo "unknown option '$OPT'."
				print_help 
				;;
			h)
				print_help
				;;
			v)
				verbose=1
				;;
		esac
	done
fi

BOOTDIR=boot
IMG="rpi-image.img"
vecho "Creating $IMG"
dd bs=1M count=64 if=/dev/zero of=$IMG 2> /dev/null
fdisk $IMG -L=never << EOF
n
p
1


t
b
w
EOF

read -r -p "This script requires root access. Sudo will be used. Continue? [Y/n] " response
if [[ $response =~ [nN][oO]|[nN] ]]; then
	echo "Aborting: permission denied"
	exit 1
fi

vecho "Mounting image"
MOUNTDIR="mount"
mkdir $MOUNTDIR

# for some reason we have to forward EOF to sudo. why
echo -e "\0" | HOME=$PWD sudo -E -A -H bash<< EOF
	device=\$(losetup --show -P -f $IMG) || exit 1
	devicepart=\${device}p1
	mkfs.vfat \$devicepart
	if [[ -n "$verbose" ]]; then echo "Mounting \$devicepart under $MOUNTDIR"; fi
	mount \$devicepart $MOUNTDIR
	if [[ -n "$verbose" ]]; then echo "Copying files"; fi
	cp $BOOTDIR/* $MOUNTDIR
	sync
	umount $MOUNTDIR
	rmdir $MOUNTDIR
	losetup -d \$device
EOF

if [[ $? == 1 ]]; then
	echo "ERROR: Failed to open device."
	rmdir $MOUNTDIR
	exit 1
fi

echo "Initialized partition successfully. No error reported."