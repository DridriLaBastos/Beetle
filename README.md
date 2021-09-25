# BeetleOS
Hobby OS for x86 plateform in c++ (and a little bit of nasm)

# Build

To build it you have to have on your path a gcc version 7+ (currently developed on gcc 7.5.0), ld, ar and nasm
that can create i686-elf executables.
When you have everything, go to the top directory, and run make, everything should 
compile

When the whole thing is built you can use make iso to create an iso image.
Grub is required at this time

# Run
You can run the iso directly with VirtualBox, or with bochs by typing make run.

## Variables

BOCHS_PREFIX: I have two versions of bochs, one with a debuger and one without.
You can edit this variable to point to a version of bochs that is built with a debuger
and type make drun. It will launch the bochs version found at $(BOCHS_PREFIX)/bochs

PREFIX: for gcc, ar and ld, the executable launched is $(PREFIX)< the tool >. I compiled 
a new version of gcc and binutils on my computer with the prefix i686-elf-, so I set this variable to "i686-elf-"
