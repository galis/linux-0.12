# linux-0.12

##  1.简介

1.修改了部分c以及汇编代码，可以通过GCC最新版本编译通过(本人电脑macOS Catalina 10.15;gcc version 10.3.0 (GCC))

2.学习资料放在源码目录下的study，可以查阅用

##  2.编译源码

1.修改源码根目录下的Makefile文件，把下面几个路径修改成你电脑的

```bash
export KERNEL_INCLUDE = /Volumes/mac-code/linux-0.12/include
export GCC_PREFIX = /usr/local/opt/x86_64-elf-gcc/bin/x86_64-elf-
export BINUTILS_PREFIX = /usr/local/opt/x86_64-elf-binutils/bin/x86_64-elf-
```

2.执行make clean&&make，可以得到Image，位于源码根目录下

##  3.运行与调试

1.确保你电脑安装了支持gdb的bochs，bochs如何安装请自行查找，网上很多资料.

2.解压tools/root-0.12.img.zip,得到tools/root-0.12.img.(git 不允许超过100M文件上传！！)

3.根据实际情况修改tools/bochsgdb.sh脚本配置


```bash
LINUX_CODE_PATH=/Volumes/mac-code/linux-0.12
BOCHS_EXE_PATH=/Volumes/mac-data/bochs-2.6.11/build-mac-gdb/bin/bochsdbg
BOCHS_CONFIG_PATH=${LINUX_CODE_PATH}/tools/bochsconfig_linux12.txt
```
3.根据实际情况修改tools/bochsconfig_linux11.txt配置

```bash
romimage:file=/Volumes/mac-data/bochs-2.6.11/build-mac/share/bochs/BIOS-bochs-latest
vgaromimage:file=/Volumes/mac-data/bochs-2.6.11/build-mac/share/bochs/VGABIOS-lgpl-latest
floppya:1_44=/Volumes/mac-code/linux-0.12/Image,status=inserted
ata0-master: type=disk, mode=flat, path="/tmp/root-0.12.img", cylinders=410, heads=16, spt=38
```

4.在Clion创建脚本执行配置，填入相关参数，点击OK创建
参数`Script Path`,选择源码根目录下的tools/bochsgdb.sh

参数`Working Directory`,选择源码根目录路径

![Image](https://github.com/galis/linux-0.12/blob/master/tools/clion_shell_script.png)

5.在Clion创建GDB REMOTE DEBUG配置，然后填写相关参数,，点击OK创建

参数`symbol file`,选择源码编译出来的tools/system.symbol

参数`sysroot`,选择源码根目录。

![Image](https://github.com/galis/linux-0.12/blob/master/tools/clion_remtoe_config.png)

6.在main.c打断点，点击debug按钮就可以调试了

![Image](https://github.com/galis/linux-0.12/blob/master/tools/clion_debug.png)

##  4.注意事项与修改记录

1.去除AS86 LD86用gcc代替

2.将bootsect.S setup.S用AT&T语法重写

3.删除seg,修改部分代码。seg 影响下一条语句而已

4.export 变量给下一级makefile使用

5.删除汇编clobber列表

6.扩展汇编才需要%%，不扩展就%

7.合并重定义符号，只使用第一个符号。ld

8.lvalue required as left operand of assignment 没有什么好的办法呢，重写下吧

9.把函数修饰符号_删除。。。自己改吧..BUILD irq很多

10.在Mac上大小写敏感很重要,在MAC编译的时候注意分区是否支持大小写。

11.invalidate_buffers 在floppy.c找不到。加一行extern void invalidate_buffers(int dev);

12.输出和内存变量输入同时存在要注意了。

13.HD controller not ready问题
原来语句：
163 int retries=10000;
165 while (--retries && (inb_p(HD_STATUS)&0xc0)!=0x40);
修改为
163 int retries=100000;
165 while (--retries && (inb_p(HD_STATUS)&0x80));
理由是：驱动器是否就绪与控制器的状态无关，我们只需要检测状态寄存器忙位是否为1即可，不需要管就绪位。
