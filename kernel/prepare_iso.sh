#!/bin/bash

cp src/osone isofiles/
grub-mkrescue -o osone.iso isofiles

