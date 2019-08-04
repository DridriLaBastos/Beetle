TARGET_OBJ = $(SRC_DIR)/arch/$(TARGET)/$(TARGET).o
CXXSRC = system/system_$(TARGET)_$(PLATFORM).cpp
ASSRC  = system/system_$(TARGET)_$(PLATFORM)_main.s
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ = $(ASSRC:.s=.o)

ASFLAGS = -f elf

PRODUCT=libsystem.a

$(PRODUCT): $(CXXOBJ) $(ASOBJ) $(TARGET_OBJ)
	$(AR) rcs $@ $^

#$(TARGET_OBJ) must be build before executing this makefile
$(TARGET_OBJ):

.PHONY: clean mrproper

clean:
	rm $(CXXOBJ) $(ASOBJ)

mrproper:
	rm $(PRODUCT)