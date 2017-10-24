#!/bin/bash

rm floppy.img
dd if=/dev/zero of=floppy.img bs=1k count=1440
sudo losetup /dev/loop0 floppy.img
sudo parted -s /dev/loop0 mklabel msdos
sudo parted -s /dev/loop0 mkpart primary fat32 1s 100%
sudo losetup -d /dev/loop0
