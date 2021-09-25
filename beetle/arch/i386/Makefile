CXXSRC = $(wildcard *.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

ASSRC = $(wildcard *.s)
ASOBJ = $(ASSRC:.s=.o)

INTERRUPT_FLAGS = -mgeneral-regs-only -mno-red-zone

all: $(CXXOBJ) $(ASOBJ)

interrupts.o: interrupts.cpp include/interrupts.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INTERRUPT_FLAGS) -c -o $@ $<