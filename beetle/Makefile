FINAL_OBJ = $(SRC_DIR)/arch/$(TARGET)/$(TARGET).o
CXXSRC = system/system_$(TARGET)_$(PLATFORM).cpp
CXXOBJ = $(CXXSRC:.cpp=.o)
PRODUCT=libsystem.a

$(PRODUCT): $(CXXOBJ) $(FINAL_OBJ)
	$(AR) rcs $@ $^

%.o: %.cpp include/system.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

.PHONY: clean mrproper

clean:
	rm $(CXXOBJ)

mrproper:
	rm $(PRODUCT)