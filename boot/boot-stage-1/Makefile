TARGET_LIB = $(SRC_DIR)/arch/$(TARGET)/lib$(TARGET).a $(SRC_DIR)/beetle/libbeetle.a

ASSRC	= $(wildcard *.s) $(wildcard boot_$(TARGET)_$(PLATFORM)/*.s)
CXXSRC	= $(wildcard boot_$(TARGET)_$(PLATFORM)/*.cpp)
ASOBJ	= $(ASSRC:.s=.o)
CXXOBJ	= $(CXXSRC:.cpp=.o)
LDFLAGS += -L$(SRC_DIR)/arch/$(TARGET) -L$(SRC_DIR)/beetle

OBJ		= $(ASOBJ) $(CXXOBJ)

EXEC	= boot-stage-1

$(EXEC): $(OBJ) $(TARGET_LIB)
	$(LD) $(LDFLAGS) --script=linker.ld $(OBJ) -l$(TARGET) -lbeetle -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)