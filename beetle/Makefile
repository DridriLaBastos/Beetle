CXXSRC = $(wildcard *.cpp)
CXXOBJ = $(CXXSRC:.cpp=.o)

PRODUCT = libbeetle.a

.PHONY: clean mrproper

$(PRODUCT): $(CXXOBJ)
	$(AR) -vrus $@ $^

clean:
	rm $(CXXOBJ)

mrproper:
	rm $(PRODUCT)