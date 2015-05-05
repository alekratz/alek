AAA! Kernel - Alek's Awesome Arm Kernel
=
Independent study Fall 2015

Building
=
You must have an arm-none-eabi compiler at your disposal - this is bare metal, after all. I'm not going to go over the details for *how* to go about building a cross-compiler toolchain, but there is a link at the bottom of this file for a good source on how to do that.

After you have your toolchain chosen, the following steps will build the kernel:
```
make
./fetchfirmware.sh
./genimage.sh
```

`make` will (of course) make an ARM image of the kernel which then can be loaded by the raspberry pi.

`./fetchfirmware.sh` will fetch all of the necessary firmware for loading up the GPU in the RPI. This is also vital, because this kernel doesn't contain code for initializing the CPU, which the firmware does do.

`./genimage.sh` will generate a bootable disk image for the raspberry pi. Stick your SDcard writer, `dd` the kernel onto the raspberry pi, and you're good to go.

Install
=
Right now, the kernel doesn't do anything. However, that will soon change. It only runs on the Raspberry Pi directly, so no virtualization is available for the time being. Because it's difficult and annoying and a hassle to constantly be switching out SD cards, a few clever people have made bootloaders which load the OS over serial. I use [raspbootin](https://github.com/mrvn/raspbootin) for booting over serial, however, plenty of others exist.

However, **there is no *actual* way to install to the SD card. That will hopefully come in the future.** For now, just keep either serial booting in, or copying directly to the SD card.

License
=
GPL v3

Sources
=
[Building the GNU ARM Toolchain for Bare Metal](http://kunen.org/uC/gnu_tool.html) - For building the ARM toolchain
[raspbootin](https://github.com/mrvn/raspbootin) - For booting over serial