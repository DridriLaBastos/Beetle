#!/bin/sh
echo menuentry \"Beetle$MAJOR_VERSION.$MINOR_VERSION.$FIX_VERSION\" { > iso/boot/grub/grub.cfg
echo "		multiboot /boot/boot-stage-1" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/$GRUB_TARGET/elf.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/$GRUB_TARGET/fat.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/$GRUB_TARGET/ext2.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/$GRUB_TARGET/disk.mod" >> iso/boot/grub/grub.cfg
echo } >> iso/boot/grub/grub.cfg