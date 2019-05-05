export SRC_DIR    = $(shell pwd)#sources directories
export BEETLE = $(SRC_DIR)/beetle
export PREFIX = i686-elf-
export AS  = nasm
export AR = $(PREFIX)ar
export LD  = $(PREFIX)ld
export CXX = $(PREFIX)g++
export DEPFLAGS = -MM -MF
export LDFLAGS  = -nostdlib -flto --strip-all
export CPPFLAGS =  -nostdinc++ -I$(SRC_DIR)
export CFLAGS   = -c -ffreestanding -mtune=generic -march=i386 -Wall -Wextra
export CXXFLAGS = $(CFLAGS) -fno-rtti -fno-exceptions

export TARGET = i386
export PLATFORM = pc

MAJOR_VERSION = 0
MINOR_VERSION = 1
FIX_VERSION   = 2 # 2 implementing the apics functionnality of the 0.1* version

DIR = arch beetle boot
DEBUG = 
BOCHS_PREFIX = 

ifeq ($(DEBUG), 1)
	BOCHS_PREFIX = $$DEV/bochs-debug/bin/
endif

BOCHS = $(BOCHS_PREFIX)bochs

all:
	@for i in $(DIR); do $(MAKE) -C $$i; echo; done

iso: boot/boot-stage-1/boot-stage-1
	@mkdir -p iso/boot/grub
	@echo menuentry \"Beetle$(MAJOR_VERSION).$(MINOR_VERSION).$(FIX_VERSION)\" { > iso/boot/grub/grub.cfg
	@echo "    multiboot /boot/boot-stage-1" >> iso/boot/grub/grub.cfg
	@echo } >> iso/boot/grub/grub.cfg
	@cp -f $^ iso/boot/
	@grub-mkrescue -o beetle.iso iso

run:
	$(BOCHS) -q

drun:
	@$(MAKE) run DEBUG=1

.PHONY: clean mrproper distclean rebuild

clean:
	@for i in $(DIR); do $(MAKE) -C $$i clean; done

iclean:
	rm -Rfd iso
	rm beetle.iso

mrproper:
	@for i in $(DIR); do $(MAKE) -C $$i mrproper; done

distclean: clean iclean mrproper
rebuild: distclean all iso
