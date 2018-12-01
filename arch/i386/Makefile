CXXSRC = $(wildcard *.cpp)
CXXHEADERS = $(wildcard *.hpp)
ASSRC  = $(wildcard *.s)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)
OBJ    = $(CXXOBJ) $(ASOBJ)
PRODUCT = i386.o

$(PRODUCT) : $(OBJ)
	$(LD) $(LDFLAGS) --relocatable $^ -o $(PRODUCT)
	
%.o: %.cpp $(CXXHEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -fno-exceptions $< -o $@

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)