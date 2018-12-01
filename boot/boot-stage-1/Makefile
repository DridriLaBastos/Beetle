CXXSRC = $(wildcard *.cpp)
ASSRC  = $(wildcard *.s)
CPPFLAGS := $(CPPFLAGS)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)
OBJ    = $(CXXOBJ) $(ASOBJ)
EXEC   = boot-stage-1

$(EXEC): $(OBJ) $(BEETLE)/libsystem.a
	$(LD) $(LDFLAGS) --script=linker.ld -o $@ $(OBJ) $(BEETLE)/libsystem.a

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)