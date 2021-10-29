export PROJECT_DIR = $(shell pwd)#sources directories
export BEETLE = $(PROJECT_DIR)/beetle

ifeq ($(shell uname -s), Darwin)
	export PREFIX = i686-elf-
endif

export AS		= nasm
export AR		= $(PREFIX)ar
export LD		= $(PREFIX)ld
export CXX		= $(PREFIX)gcc -march=i386
export NM		= $(PREFIX)nm
export OBJDUMP	= $(PREFIX)objdump
#export CC		= $(PREFIX)gcc -m32 -std=c11
#export LDFLAGS	= -nostdlib --strip-all -melf_i386
export CPPFLAGS	= -I$(BEETLE)/include -I$(PROJECT_DIR)
export ASFLAGS	= -f elf32 -I$(PROJECT_DIR)/beetle/arch/$(TARGET)
export CFLAGS	= -flto -nostdlib -O3 -ffreestanding -Wall -Wextra -fno-asynchronous-unwind-tables -fno-unwind-tables
export CXXFLAGS	= $(CFLAGS) -std=c++11 -nostdinc++ -fno-rtti -fstrict-enums -fno-threadsafe-statics

export TARGET	= i386

export MAJOR_VERSION	= 0
export MINOR_VERSION	= 1
export FIX_VERSION		= 2 #2 implementing interrupts

DIR = beetle
DEBUG = 
BOCHS_PREFIX = 

ifeq ($(DEBUG), 1)
	BOCHS_PREFIX = $$DEV/bochs-debug/bin/
endif

BOCHS = $(BOCHS_PREFIX)bochs

.PHONY: all $(DIR) clean mrproper distclean rebuild

all: $(DIR)

$(DIR):
	$(MAKE) -C $@

iso: beetle.iso
beetle.iso: beetle/beetle.elf
#beetle.iso: boot/boot-stage-1/boot-stage-1.out build-grubconfig.sh
	@mkdir -p iso/boot/grub
	@sh build-grubconfig.sh
	@cp -f $< iso/boot/
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
