#ALEK - Alek's Little Endian Kernel
(formerly AAA! Kernel)
Independent study Fall 2015

For more comprehensive building instructions, check out [the wiki1](https://github.com/alekratz/aaa/wiki)!

#Building for x86
You must have an i686-elf compiler at your disposal.

After you have your toolchain built, the following steps will build the kernel:
```
make TARGET=x86
```

That wasn't so hard! :)

#Building for Raspberry Pi
You must have an arm-none-eabi compiler at your disposal - this is bare metal, after all.

After you have your toolchain built, the following steps will build the kernel and generate an image ready for the SD card:
```
make TARGET=rpi
./fetchfirmware.sh
./genimage.sh
```

`make TARGET=rpi` will (of course) make an ARM image of the kernel which then can be loaded by the raspberry pi.

`./fetchfirmware.sh` will fetch all of the necessary firmware for loading up the GPU in the RPI. This is also vital, because this kernel doesn't contain code for initializing the CPU, which the firmware does do.

`./genimage.sh` will generate a bootable disk image for the raspberry pi. Stick your SDcard writer, `dd` the kernel onto the raspberry pi, and you're good to go.

#Install
Right now, the kernel doesn't do anything. However, that will soon change. It only runs on the Raspberry Pi directly, so no virtualization is available for the time being. Because it's difficult and annoying and a hassle to constantly be switching out SD cards, a few clever people have made bootloaders which load the OS over serial. I use [raspbootin](https://github.com/mrvn/raspbootin) for booting over serial, however, plenty of others exist.

However, **there is no *actual* way to install to the SD card. That will hopefully come in the future.** For now, just keep either serial booting in, or copying directly to the SD card.

#Rationale
When reading through other peoples' code for bare-metal Raspberry Pi programs/kernels, a lot of the time I find myself asking, *"why did you do this?!"*. It's not necessarily due to annoyance, but more due to lack of documentation and in-code reasoning. There are a few things in AAA! Kernel that seem counterintuitive, but I have put a lot of thought into.

##Why a kernel?
AAA! Kernel is mostly a way to learn what kernel-level code does. I took an operating systems class in Spring of 2015, and I learned a lot! However, I wanted to learn more; I wanted to know what the kernel was actually *doing* at that low of a level. So here we are.

##Why enable stdlib? (Or rather, why not disable it?)
One reason, consensed into a few symbols and letters: `__aeabi_uidiv`. `__aeabi_uidiv` is the method that the linker attempts to use to implement division because it's not already on the chip; if I don't use the stdlib, I don't get integer division. Basically saying, the ARM processor does not natively support integer division. While I could attempt to implement it myself, many other smarter folks over at GNU have done that for me. I'm probably not going to be using the standard libraries quite yet, however, I may start using it if I see it provides things that I deem to be useful (e.g., `std::underlying_type`).

#License
GPL v3

#Sources
[Building the GNU ARM Toolchain for Bare Metal](http://kunen.org/uC/gnu_tool.html) - For building the ARM toolchain
[raspbootin](https://github.com/mrvn/raspbootin) - For booting over serial
[OSDev Wiki - Raspberry Pi Bare Bones](http://wiki.osdev.org/ARM_RaspberryPi_Tutorial_C) - Useful for the UART stuff. Basic source code for the UART interface.
[dwelch67's baremetal Raspberry Pi programs](https://github.com/dwelch67/raspberrypi) - A healthy collection of bare-metal programs written for the Raspberry Pi, exploring different topics.