CXXSRC = $(wildcard *.cpp)
CXXARCHSRC = $(wildcard arch/$(TARGET)/*.cpp)

CXXOBJ = $(CXXSRC:.cpp=.o)
CXXARCHOBJ = $(CXXARCHSRC:.cpp=.o)

ASSRC = $(wildcard *.s) arch/i386/preinit.s
ASOBJ = $(ASSRC:.s=.o)

OBJ = $(CXXOBJ) $(CXXARCHOBJ) $(ASOBJ)

PRODUCT = beetle.elf

.PHONY: clean mrproper all arch

$(PRODUCT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Wl,--script=linker.ld -o $@ $^

$(CXXARCHOBJ): $(CXXARCHSRC)
	$(MAKE) -C arch/$(TARGET)

#kmain.o: $(CXXSRC) arch/i386/i386.cpp

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)