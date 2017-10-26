#!/bin/bash

echo -ne "\e[32mRemoving Floppy Image...\e[0m"
rm -f base_floppy.img
echo -e "\e[32mDone\e[0m"
echo -ne "\e[32mCreating new blank image...\e[0m"
dd if=/dev/zero of=base_floppy.img bs=1k count=1440 status=none
echo -e "\e[32mDone\e[0m"
echo -ne "\e[32mSetting up loop device /dev/loop0...\e[0m"
sudo losetup /dev/loop0 base_floppy.img
echo -e "\e[32mDone\e[0m"
echo -ne "\e[32mMaking fat32 filesystem on new device...\e[0m"
sudo mkfs.vfat /dev/loop0p1 >/dev/null
echo -e "\e[32mDone\e[0m"
echo -ne "\e[32mDetaching /dev/loop0 device...\e[0m"
sudo losetup -d /dev/loop0
echo -e "\e[32mDone\e[0m"
