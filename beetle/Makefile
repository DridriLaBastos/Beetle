CXXSRC = $(wildcard *.cpp)
ASSRC = $(wildcard *.s)

CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)

PRODUCT = beetle.elf

.PHONY: clean mrproper all $(TARGET)

$(PRODUCT): $(CXXOBJ) $(TARGET)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -Larch/$(TARGET) -Wl,--script=linker.ld -o $@ $(CXXOBJ) -l$(TARGET)
	$(NM) --demangle --numeric-sort $@ > ../tmps
	$(OBJDUMP) -d -M intel $@ > ../tmpd

$(TARGET):
	$(MAKE) -C arch/$(TARGET)

#kmain.o: $(CXXSRC) arch/i386/i386.cpp

clean:
	rm $(CXXOBJ) $(ASOBJ)
	$(MAKE) -C arch/$(TARGET) $@

mrproper:
	rm $(PRODUCT)
	$(MAKE) -C arch/$(TARGET) $@