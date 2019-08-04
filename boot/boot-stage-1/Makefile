BOOT_OBJ = $(wildcard boot_$(TARGET)_$(PLATFORM)*.o)
TARGET_OBJ = $(SRC_DIR)/arch/$(TARGET)/$(TARGET).o

ASSRC	= $(wildcard *.s) $(wildcard boot_$(TARGET)_$(PLATFORM)/*.s)
CXXSRC	= $(wildcard boot_$(TARGET)_$(PLATFORM)/*.cpp)
ASOBJ	= $(ASSRC:.s=.o)
CXXOBJ	= $(CXXSRC:.cpp=.o)
OBJ		= $(ASOBJ) $(CXXOBJ) $(BOOT_OBJ)

EXEC	= boot-stage-1

$(EXEC): $(OBJ) $(TARGET_OBJ)
	$(LD) $(LDFLAGS) --script=linker.ld $^ -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)