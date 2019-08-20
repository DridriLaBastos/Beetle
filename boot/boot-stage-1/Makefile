BOOT_OBJ = $(wildcard boot_$(TARGET)_$(PLATFORM)/*.o)
TARGET_LIB = $(SRC_DIR)/arch/$(TARGET)/lib$(TARGET).a

ASSRC	= $(wildcard *.s) $(wildcard boot_$(TARGET)_$(PLATFORM)/*.s)
CXXSRC	= $(wildcard boot_$(TARGET)_$(PLATFORM)/*.cpp)
ASOBJ	= $(ASSRC:.s=.o)
LDFLAGS += -L$(SRC_DIR)/arch/$(TARGET)
CXXOBJ	= $(CXXSRC:.cpp=.o)
OBJ		= $(ASOBJ) $(CXXOBJ) $(BOOT_OBJ) $(TARGET_LIB)

EXEC	= boot-stage-1

$(EXEC): $(OBJ) $(TARGET_LIB)
	$(LD) $(LDFLAGS) --script=linker.ld $(OBJ) -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)