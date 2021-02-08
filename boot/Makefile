all:
	@echo
	@echo --- COMPILING FIRST STAGE BOOTLOADER ---
	@echo
	$(MAKE) -C boot-stage-1

.PHONY: clean mrproper

clean:
	$(MAKE) -C boot-stage-1 clean

mrproper:
	$(MAKE) -C boot-stage-1 mrproper