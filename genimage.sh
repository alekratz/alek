#!/bin/bash
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