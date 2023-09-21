#!/bin/bash
source /opt/st/stm32mp1/4.0.4-openstlinux-5.15-yocto-kirkstone-mp1-v22.11.23/environment-setup-cortexa7t2hf-neon-vfpv4-ostl-linux-gnueabi
make uImage dtbs LOADADDR=0XC2000040 -j23
./install.sh
