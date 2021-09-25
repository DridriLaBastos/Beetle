CXXSRC = $(wildcard *.cpp)
CXXARCHSRC = $(wildcard arch/$(TARGET)/*.cpp)

ASSRC = $(wildcard *.s)
ASARCHSRC  = $(wildcard arch/$(TARGET)/*.s)

CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)

CXXARCHOBJ = $(CXXARCHSRC:.cpp=.o)
ASARCHOBJ  = $(ASARCHSRC:.s=.o)

BEETLEOBJ = $(CXXOBJ) $(ASOBJ)

ARCHSRC = $(CXXARCHSRC) $(ASARCHSRC)
ARCHOBJ = $(CXXARCHOBJ) $(ASARCHOBJ)

OBJ = $(BEETLEOBJ) $(ARCHOBJ)

PRODUCT = beetle.elf

.PHONY: clean mrproper all arch

$(PRODUCT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Wl,--script=linker.ld -o $@ $^
	$(PREFIX)nm --demangle --numeric-sort $@ > ../tmps
	$(PREFIX)objdump -d -M intel $@ > ../tmpd

$(ARCHOBJ): $(ARCHSRC)
	$(MAKE) -C arch/$(TARGET)

#kmain.o: $(CXXSRC) arch/i386/i386.cpp

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)