CXXSRC = $(wildcard src/*.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

DEPFLAGS	= -MM -MF
DEPOBJ	= $(CXXSRC:.cpp=.d)
OBJ		= $(CXXOBJ) $(ASOBJ)

PRODUCT = libbeetle.a

.PHONY: clean mrproper

$(PRODUCT): $(DEPOBJ) $(CXXOBJ)
	$(AR) -vrus $@ $(CXXOBJ)

%.d: %.cpp
	$(CXX) $(DEPFLAGS) $@ $^

clean:
	rm $(CXXOBJ)

mrproper:
	rm $(PRODUCT)

include $(wildcard $(DEPOBJ))