#
# if you want the ram-disk device, define this to be the
# size in blocks.
#

#>>>>>>>>>>>>>>>>下面配置修改你电脑自己的
export KERNEL_INCLUDE = /Volumes/mac-code/linux-0.12/include
export GCC_PREFIX = /usr/local/opt/x86_64-elf-gcc/bin/x86_64-elf-
export BINUTILS_PREFIX = /usr/local/opt/x86_64-elf-binutils/bin/x86_64-elf-
#<<<<<<<<<<<<<<<<

export AS	= $(BINUTILS_PREFIX)as --32 -g
export AR	= $(BINUTILS_PREFIX)ar
export LD	= $(BINUTILS_PREFIX)ld -m elf_i386 -Ttext 0
export LDFLAGS	= -M
export CC	=$(GCC_PREFIX)gcc -m32 -nostdinc -I$(KERNEL_INCLUDE)  -c
export CFLAGS	= -Wall -fomit-frame-pointer -O0 -fno-builtin -nostdlib -g -finline-functions -mcld
export CPP	=$(CC) -E
export OBJCOPY	= $(BINUTILS_PREFIX)objcopy
export OBJDUMP	= $(BINUTILS_PREFIX)objdump

#
# ROOT_DEV specifies the default root-device when making the image.
# This can be either FLOPPY, /dev/xxxx or empty, in which case the
# default of /dev/hd6 is used by 'build'.
#
RAMDISK = #-DRAMDISK=512
ROOT_DEV=FLOPPY
SWAP_DEV=NONE

ARCHIVES=kernel/kernel.o mm/mm.o fs/fs.o
DRIVERS =kernel/blk_drv/blk_drv.a kernel/chr_drv/chr_drv.a
MATH	=kernel/math/math.a
LIBS	=lib/lib.a

.c.s:
	$(CC) $(CFLAGS)  -S -o $*.s $<
.s.o:
	$(AS) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) -c -o $*.o $<

all:	Image

Image: boot/bootsect boot/setup tools/system tools/build
	dd if=boot/bootsect >Image
	dd if=/dev/zero bs=512 count=4 >>Image
	dd if=boot/setup of=Image seek=512 bs=1 conv=notrunc
	dd if=tools/system >> Image
	sync

disk: Image
	dd bs=8192 if=Image of=/dev/PS0

#tools/build: tools/build.c
#	$(CC) -w -O -fno-stack-protector -m32 -fstrength-reduce  \
#	-o tools/build tools/build.c

boot/head.o: boot/head.s
	$(CC) $(CFLAGS) boot/head.s -o boot/head.o
#	$(LD) -o boot/head.ld boot/head.o
#	$(OBJCOPY) -I elf32-i386 -O binary boot/head.ld boot/head

tools/system:	boot/head.o init/main.o $(ARCHIVES) $(DRIVERS) $(MATH) $(LIBS)
	$(LD) boot/head.o init/main.o \
	$(ARCHIVES) \
	$(DRIVERS) \
	$(MATH) \
	$(LIBS) \
	-t -v -o tools/system.ld
	$(OBJCOPY) -I elf32-i386 -O binary  tools/system.ld tools/system
	$(OBJCOPY) --only-keep-debug tools/system.ld tools/system.symbol
	$(OBJDUMP) -t tools/system.ld > tools/system.map

kernel/math/math.a:
	(cd kernel/math; make)

kernel/blk_drv/blk_drv.a:
	(cd kernel/blk_drv; make)

kernel/chr_drv/chr_drv.a:
	(cd kernel/chr_drv; make)

kernel/kernel.o:
	(cd kernel; make)

mm/mm.o:
	(cd mm; make)

fs/fs.o:
	(cd fs; make)

lib/lib.a:
	(cd lib; make)


boot/setup:	boot/setup.S include/linux/config.h
	$(CPP) -traditional boot/setup.S -o boot/setup.s
	$(AS) -o boot/setup.o boot/setup.s
	$(LD) -s -o boot/setup.ld boot/setup.o
	$(OBJCOPY) -I elf32-i386 -O binary boot/setup.ld boot/setup

boot/bootsect:	boot/bootsect.S include/linux/config.h
	$(CPP) -traditional boot/bootsect.S -o boot/bootsect.s
	$(CC) -o boot/bootsect.o boot/bootsect.s
	$(LD) -s -o boot/bootsect.ld boot/bootsect.o
	$(OBJCOPY) -I elf32-i386 -O binary boot/bootsect.ld boot/bootsect

clean:
	rm -f Image System.map tmp_make core boot/bootsect boot/setup \
		boot/bootsect.s boot/setup.s \
		boot/bootsect.ld bootsect/setup.ld
	rm -f init/*.o tools/system tools/system.ld tools/system.symbol tools/build boot/*.o
	(cd mm;make clean)
	(cd fs;make clean)
	(cd kernel;make clean)
	(cd lib;make clean)

backup: clean
	(cd .. ; tar cf - linux | compress - > backup.Z)
	sync

dep:
	sed '/\#\#\# Dependencies/q' < Makefile > tmp_make
	(for i in init/*.c;do echo "init/";$(CPP) -M $$i;done) >> tmp_make
	cp tmp_make Makefile
	(cd fs; make dep)
	(cd kernel; make dep)
	(cd mm; make dep)

### Dependencies:
init/main.o: init/main.c include/unistd.h include/sys/stat.h \
  include/sys/types.h include/sys/time.h include/time.h \
  include/sys/times.h include/sys/utsname.h include/sys/param.h \
  include/sys/resource.h include/utime.h include/linux/tty.h \
  include/termios.h include/linux/sched.h include/linux/head.h \
  include/linux/fs.h include/linux/mm.h include/linux/kernel.h \
  include/signal.h include/asm/system.h include/asm/io.h \
  include/stddef.h include/stdarg.h include/fcntl.h include/string.h
