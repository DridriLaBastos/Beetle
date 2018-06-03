
export PREFIX = i686-elf-
export AS  = nasm
export LD  = $(PREFIX)ld
export CXX = $(PREFIX)g++
export LDFLAGS  = -nostdlib --script=linker.ld
export CPPFLAGS = -nostdinc -nostdinc++
export CFLAGS   = -c -ffreestanding -mtune=generic -m32
export CXXFLAGS = $(CFLAGS) -fno-rtti   

MAJOR_VERSION = 0
MINOR_VERSION = 1
FIX_VERSION   = 0

DIR = boot
DEBUG = 
BOCHS_PREFIX = 

ifeq ($(DEBUG), 1)
	BOCHS_PREFIX = $$DEV/bochs-debug/bin/
endif

BOCHS = $(BOCHS_PREFIX)bochs

all:
	@for i in $(DIR); do $(MAKE) -C $$i; echo; done
	$(LD) $(LDFLAGS) boot/header.o -o boot-stage-1

iso: boot-stage-1
	@mkdir -p iso/boot/grub
	@echo menuentry \"Beetle$(MAJOR_VERSION).$(MINOR_VERSION).$(FIX_VERSION)\" { > iso/boot/grub/grub.cfg
	@echo "    multiboot /boot/boot-stage-1" >> iso/boot/grub/grub.cfg
	@echo } >> iso/boot/grub/grub.cfg
	@cp -f boot-stage-1 iso/boot/
	@grub-mkrescue -o beetle.iso iso

run:
	$(BOCHS) -q

.PHONY: clean mrproper clean-all

clean:
	@for i in $(DIR); do $(MAKE) -C $$i clean; done

clean-all:
	@$(MAKE) clean
	rm -Rfd iso
	rm beetle.iso

mrproper:
	rm boot-stage-1
