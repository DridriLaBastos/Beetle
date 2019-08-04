LIB_SYSTEM = $(BEETLE)/libsystem.a

ASSRC	= $(wildcard *.s)
ASOBJ	= $(ASSRC:.s=.o)
OBJ		= $(ASOBJ)
EXEC	= boot-stage-1

$(EXEC): $(OBJ) $(LIB_SYSTEM)
	$(LD) $(LDFLAGS) --script=linker.ld $^ -o $@

.PHONY: clean mrproper

clean:
	rm $(OBJ)

mrproper:
	rm $(EXEC)