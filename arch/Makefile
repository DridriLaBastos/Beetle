all:
	$(MAKE) -C $(TARGET)

.PHONY: clean mrproper

clean:
	$(MAKE) -C $(TARGET) clean

mrproper:
	@rm $(TARGET).a
	$(MAKE) -C $(TARGET) mrproper