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

OUTPUT=rpi-image.img
OUTPUTSIZEmb=34
BOOTDIR=boot

# Do some math based on the output size
OUTPUTSIZEb=$(( $OUTPUTSIZEmb * 1024 * 1024 ))
OUTPUTCYLINDERS=$(( $OUTPUTSIZEb / 255 / 63 / 512 ))
OUTPUTBLOCKCOUNT=$(( $OUTPUTSIZEmb * 1024 * 1024 ))
OUTPUTBLOCKCOUNT=$(( $OUTPUTBLOCKCOUNT / 512 ))

vecho "OUTPUTSIZEb: $OUTPUTSIZEb"
vecho "OUTPUTCYLINDERS: $OUTPUTCYLINDERS"
vecho "OUTPUTBLOCKCOUNT: $OUTPUTBLOCKCOUNT"

# Create/format the image for FAT32
vecho "Creating $OUTPUT"
dd bs=512 count=$OUTPUTBLOCKCOUNT if=/dev/zero of=$OUTPUT 2> /dev/null
vecho "Formatting $OUTPUT"
fdisk -L=never -b 512 -H 255 -S 63 -C $OUTPUTCYLINDERS $OUTPUT > /dev/null << EOF
x
c
$OUTPUTCYLINDERS
r
n
p
1


t
c

w
EOF

read -r -p "This script requires root access. Sudo will be used. Continue? [Y/n] " response
if [[ $response =~ [nN][oO]|[nN] ]]; then
	echo "Aborting: permission denied"
	exit 1
fi

vecho "Mounting image"
DEVFILE=".device"
MOUNTDIR="mount"
mkdir $MOUNTDIR

# for some reason we have to forward EOF to sudo. why
echo -e "\0" | HOME=$PWD sudo -E -A -H bash<< EOF
	losetup --show -o $((63*512)) -f $OUTPUT > $DEVFILE || exit 1
	device=\$(cat $DEVFILE)
	rm $DEVFILE
	#echo "opened device \$device"
	mkfs.msdos -F 32 \$device
	mount -o loop,offset=$((63*512)) $OUTPUT $MOUNTDIR
	if [[ -n "$verbose" ]]; then echo "Copying files"; fi
	cp $BOOTDIR/* $MOUNTDIR
	umount $MOUNTDIR
	rmdir $MOUNTDIR
	#echo "closing device \$device"
	losetup -d \$device
EOF

if [[ $? == 1 ]]; then
	echo "ERROR: Failed to open device."
	rm -rf $DEVFILE $MOUNTDIR
	exit 1
fi

echo "Initialized partition successfully. No error reported."