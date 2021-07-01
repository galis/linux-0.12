#!/bin/zsh
#1.请根据你电脑的情况修改下面变量
LINUX_CODE_PATH=/Volumes/mac-code/linux-0.12
BOCHS_EXE_PATH=/Volumes/mac-data/bochs-2.6.11/build-mac-gdb/bin/bochsdbg
BOCHS_CONFIG_PATH=${LINUX_CODE_PATH}/tools/bochsconfig_linux12.txt

echo "start!!"
cp ${LINUX_CODE_PATH}/tools/root-0.12.img /tmp/root-0.12.img
make clean && make -j8
nohup ${BOCHS_EXE_PATH} -f ${BOCHS_CONFIG_PATH} -q &
sleep 3
echo "end"

