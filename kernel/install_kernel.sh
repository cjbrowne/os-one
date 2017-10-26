#!/bin/bash

echo -ne "\e[32mResetting floppy.img to base image...\e[0m"
cp base_floppy.img floppy.img
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mSetting up loopback device...\e[0m"
sudo losetup /dev/loop0 floppy.img
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mCreating mount directory...\e[0m"
sudo mkdir -p /mnt/osone-boot-floppy/
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mMounting loopback device...\e[0m"
sudo mount /dev/loop0 /mnt/osone-boot-floppy/
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mCopying kernel...\e[0m"
sudo cp src/osone /mnt/osone-boot-floppy/
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mUnmounting directory...\e[0m"
sudo umount /mnt/osone-boot-floppy/ 
echo -e "\e[32mDone\e[0m"

echo -ne "\e[32mDetaching loopback device...\e[0m"
sudo losetup -d /dev/loop0 
echo -e "\e[32mDone\e[0m"
