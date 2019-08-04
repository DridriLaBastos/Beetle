FINAL_OBJ = $(SRC_DIR)/arch/$(TARGET)/$(TARGET).o
CXXSRC = system/system_$(TARGET)_$(PLATFORM).cpp
ASSRC  = system/system_$(TARGET)_$(PLATFORM)_main.s
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ = $(ASSRC:.s=.o)

ASFLAGS = -f elf

PRODUCT=libsystem.a main.o

$(PRODUCT): $(CXXOBJ) $(ASOBJ)
	$(AR) rcs $@ $^ $(FINAL_OBJ)

.PHONY: clean mrproper

clean:
	rm $(CXXOBJ) $(ASOBJ)

mrproper:
	rm $(PRODUCT)