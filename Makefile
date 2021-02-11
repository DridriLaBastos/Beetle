export SRC_DIR = $(shell pwd)#sources directories
export BEETLE = $(SRC_DIR)/beetle

ifeq ($(shell uname -s), Darwin)
	export PREFIX = i686-elf-
endif

export AS		= nasm
export AR		= $(PREFIX)ar
export LD		= $(PREFIX)ld
export CXX		= $(PREFIX)g++ -m32 -std=c++11
export LDFLAGS	= -nostdlib --strip-all -melf_i386
export CPPFLAGS	= -nostdinc++ -I$(SRC_DIR)
export ASFLAGS	= -f elf
export CFLAGS	= -O3 -ffreestanding -mtune=generic -march=i386 -Wall -Wextra
export CXXFLAGS	= $(CFLAGS) -fno-rtti -fstrict-enums -fno-threadsafe-statics

export TARGET	= i386
export PLATFORM	= pc

export MAJOR_VERSION	= 0
export MINOR_VERSION	= 1
export FIX_VERSION		= 2 #2 implementing the apics functionnality of the 0.1* version

DIR = arch boot
DEBUG = 
BOCHS_PREFIX = 

ifeq ($(DEBUG), 1)
	BOCHS_PREFIX = $$DEV/bochs-debug/bin/
endif

BOCHS = $(BOCHS_PREFIX)bochs

.PHONY: all $(DIR) clean mrproper distclean rebuild iso

all: $(DIR)

$(DIR):
	$(MAKE) -C $@

boot: beetle
beetle: arch

iso: beetle.iso
beetle.iso: boot/boot-stage-1/boot-stage-1.out build-grubconfig.sh
	@mkdir -p iso/boot/grub
	@sh build-grubconfig.sh
	@cp -f $^ iso/boot/
	@grub-mkrescue -o beetle.iso iso

run:
	$(BOCHS) -q

drun:
	@$(MAKE) run DEBUG=1

clean:
	@for i in $(DIR); do $(MAKE) -C $$i clean; done

iclean:
	rm -Rfd iso
	rm beetle.iso

mrproper:
	@for i in $(DIR); do $(MAKE) -C $$i mrproper; done

distclean: clean iclean mrproper
rebuild: distclean all iso
