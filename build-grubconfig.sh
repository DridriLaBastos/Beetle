#!/bin/sh
#This script is called from the main makefile where the value *VERSION are defined
#The first world of the string loaded with the module will be its name because I don't know
#in witch order GRUB will load the modules in memory (I suppose they wiill bein the same order as
#in the script but I find nothing in the doc), plus it is easier to know which module is wich,
#and I can change the order of them, or ask GRUB for other modules without woring to much in the kernel code
#TODO: Is really usefull to pass the name of the module ?
echo menuentry \"Beetle$MAJOR_VERSION.$MINOR_VERSION.$FIX_VERSION\" { > iso/boot/grub/grub.cfg
echo "		multiboot /boot/boot-stage-1.out" >> iso/boot/grub/grub.cfg
#echo "		module /drivers/test" >> iso/boot/grub/grub.cfg
echo } >> iso/boot/grub/grub.cfg