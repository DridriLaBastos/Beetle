CXXSRC = $(wildcard *.cpp)
ASSRC  = $(wildcard *.s)
CXXOBJ = $(CXXSRC:.cpp=.o)
ASOBJ  = $(ASSRC:.s=.o)

OBJ = $(CXXOBJ) $(ASOBJ)
PRODUCT = i386.a

$(PRODUCT): $(OBJ)
	$(AR) rcs $@ $^
	@cp $@ ../
	

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -fno-exceptions $^ -o $@

%.o: %.s
	$(AS) -f elf32 $^

.PHONY: clean

clean:
	rm $(OBJ)
	rm $(PRODUCT)