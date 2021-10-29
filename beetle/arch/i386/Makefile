CXXSRC = $(wildcard *.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

ASSRC = $(wildcard *.s)
ASOBJ = $(ASSRC:.s=.o)

INTERRUPT_FLAGS = -mgeneral-regs-only -mno-red-zone

PRODUCT=libi386.a

.PHONY: clean mrproper

$(PRODUCT): $(CXXOBJ) $(ASOBJ)
	$(AR) -ruv $@ $^

interrupts.o: interrupts.cpp include/interrupts.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INTERRUPT_FLAGS) -c -o $@ $<

clean:
	rm $(CXXOBJ) $(ASOBJ) $(PRODUCT)

mrproper: clean
