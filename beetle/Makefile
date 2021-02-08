CXXSRC = $(wildcard src/*.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

DEPFLAGS	= -MM -MF
DEPOBJ	= $(CXXSRC:.cpp=.d)
OBJ		= $(CXXOBJ) $(ASOBJ)

PRODUCT = libbeetle.a

.PHONY: clean mrproper all

all:
	@echo
	@echo --- COMPILING BEETLE ARCHITECTURE INDEPENDANNT CODE ---
	@echo
	@make $(PRODUCT)

$(PRODUCT): $(DEPOBJ) $(CXXOBJ)
	@echo
	@echo --- CREATING LIBBEETLE.A ---
	@echo
	$(AR) -vrus $@ $(CXXOBJ)

%.d: %.cpp
	$(CXX) $(DEPFLAGS) $@ $^

clean:
	rm $(CXXOBJ)

mrproper:
	rm $(PRODUCT)

include $(wildcard $(DEPOBJ))