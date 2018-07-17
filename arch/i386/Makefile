CXXSRC = $(wildcard *.cpp)
CXXHEADERS = $(wildcard *.hpp)
ASSRC  = $(wildcard *.s)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)

OBJ = $(CXXOBJ) $(ASOBJ)
PRODUCT = i386.a

$(PRODUCT): $(OBJ) $(CXXHEADERS)
	$(AR) rcs $@ $(OBJ)
	ln -vf $$(pwd)/$@ $$(pwd)/../$@
	
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -fno-exceptions $^ -o $@

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)