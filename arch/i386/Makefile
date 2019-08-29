CXXSRC	= $(wildcard *.cpp)
ASSRC	= $(wildcard *.s)
CXXOBJ	= $(CXXSRC:.cpp=.o)
ASOBJ	= $(ASSRC:.s=.o)
DEPFLAGS	= -MM -MF
DEPOBJ	= $(CXXSRC:.cpp=.d)
OBJ		= $(CXXOBJ) $(ASOBJ)
PRODUCT	= lib$(TARGET).a

$(PRODUCT) : $(DEPOBJ) $(OBJ)
	$(AR) -vrus $@ $(OBJ)

%.d: %.cpp
	$(CXX) $(DEPFLAGS) $@ $^

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(PRODUCT)

include $(wildcard $(DEPOBJ))