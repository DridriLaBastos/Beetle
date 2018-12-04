PRODUCT = libsys.a
TARGET_OBJ = $(SRC_DIR)/arch/$(TARGET)/$(TARGET).o
CXXSRC = system/system_$(TARGET).cpp
CXXOBJ = $(CXXSRC:.cpp=.o)
PRODUCT=libsystem.a

$(PRODUCT): $(CXXOBJ) $(TARGET_OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp include/system.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

.PHONY: clean mrproper

clean:
	rm $(CXXOBJ)

mrproper:
	rm $(PRODUCT)