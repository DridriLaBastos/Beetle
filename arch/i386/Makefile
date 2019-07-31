CXXSRC = $(wildcard *.cpp)
ASSRC  = $(wildcard *.s)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)
DEPFLAGS = -MM -MF
DEPOBJ   = $(CXXSRC:.cpp=.d)
OBJ    = $(CXXOBJ) $(ASOBJ)
PRODUCT = i386.o

$(PRODUCT) : $(DEPOBJ) $(OBJ)
	$(LD) $(LDFLAGS) --relocatable $(OBJ) -o $(PRODUCT)

%.d: %.cpp
	$(CXX) $(DEPFLAGS) $@ $^

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)

include $(wildcard $(patsubst %, %.d, $(CXXSRC)))