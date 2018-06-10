CXXSRC = $(wildcard *.cpp)
ASSRC  = $(wildcard *.s)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)
OBJ    = $(CXXOBJ) $(ASOBJ)
EXEC   = boot-stage-1

CPPFLAGS = -I $(SRC_DIR)

$(EXEC): $(OBJ)
	$(LD) $(LDFLAGS) --script=linker.ld -o $@ $(OBJ) $(SRC_DIR)/arch/$(TARGET).a

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)