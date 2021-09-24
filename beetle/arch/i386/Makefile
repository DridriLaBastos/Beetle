CXXSRC = $(wildcard *.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

INTERRUPT_FLAGS = -mgeneral-regs-only -mno-red-zone

all: $(CXXOBJ)

interrupts.o: interrupts.cpp include/interrupts.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INTERRUPT_FLAGS) -c -o $@ $<