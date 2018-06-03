OBJ = header.o

$(OBJ): header.s
	$(AS) -f elf32 $^ -o $@

.PHONY: clean

clean:
	rm $(OBJ)