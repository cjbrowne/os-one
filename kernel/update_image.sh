#!/bin/bash

if [ -f floppy.img ]; then
	echo "floppy.img already exists, skipping creation..."
else
	./create-floppy-image.sh
fi

sudo losetup /dev/loop0 floppy.img
sudo mkdir -p /mnt/osone-boot-floppy/
sudo mount /dev/loop0 /mnt/osone-boot-floppy/
sudo grub-install /dev/loop0
sudo cp menu.lst /mnt/osone-boot-floppy/
sudo cp osone /mnt/osone-boot-floppy/
sudo umount /dev/loop0
sudo losetup -d /dev/loop0

