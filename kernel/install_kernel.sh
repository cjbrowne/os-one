#!/bin/bash

echo -ne "\e[32mSetting up loopback device...\e[0m"
sudo losetup /dev/loop0 floppy.img
echo -e "\e[32mDone\e[0m"

