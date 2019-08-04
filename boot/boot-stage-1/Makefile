ASSRC  = $(wildcard *.s)
ASOBJ  = $(ASSRC:.s=.o)
OBJ    = $(ASOBJ)
EXEC   = boot-stage-1

$(EXEC): $(OBJ) $(BEETLE)/libsystem.a
	$(LD) $(LDFLAGS) --script=linker.ld $^ -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)