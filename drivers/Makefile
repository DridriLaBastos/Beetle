DRIVER_DIRS = $(shell ls -d */)

.PHONY: $(DRIVER_DIRS) clean mrproper

$(DRIVER_DIRS):
	$(MAKE) -C $@

clean mrproper:
	@for dir in $(DRIVER_DIRS); do $(MAKE) -C $$dir $@; done 