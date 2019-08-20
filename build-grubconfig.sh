#!/bin/sh
echo menuentry \"Beetle$MAJOR_VERSION.$MINOR_VERSION.$FIX_VERSION\" { > iso/boot/grub/grub.cfg
echo "		multiboot /boot/boot-stage-1" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/\${grub_cpu}-\${grub_platform}/elf.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/\${grub_cpu}-\${grub_platform}/fat.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/\${grub_cpu}-\${grub_platform}/ext2.mod" >> iso/boot/grub/grub.cfg
echo "		module \${prefix}/\${grub_cpu}-\${grub_platform}/disk.mod" >> iso/boot/grub/grub.cfg
echo } >> iso/boot/grub/grub.cfg