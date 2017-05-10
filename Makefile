# Makefile

EXES=example_bloviate example_hexdump
OBJS=example_bloviate.o bloviate.o example_hexdump.o hexdump.o
CFLAGS=-Wno-pointer-to-int-cast

all : $(EXES)

clean : 
	$(RM) $(EXES) $(OBJS)

bloviate.o : bloviate.c bloviate.h

example_bloviate.o : example_bloviate.c bloviate.h

example_bloviate : bloviate.o example_bloviate.o

hexdump.o : hexdump.c hexdump.h

example_hexdump.o : example_hexdump.c hexdump.h

example_hexdump : hexdump.o example_hexdump.o
