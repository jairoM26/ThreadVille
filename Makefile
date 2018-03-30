#directories
BDIR = ./bin/
IDIR = ./include/
LDIR = ./lib/
SDIR = ./src/

#flags
CC = gcc
IFLAGS = -I$(IDIR)
LFLAGS = -lm -pthread
CFLAGS = -c -fPIC
OFLAGS = -o

_SRC = main.c
SRC = $(patsubst %, $(SDIR)%, $(_SRC))

EXEC = $(BDIR)exec

all:
	$(CC) $(IFLAGS) $(LFLAGS) $(OFLAGS)  $(EXEC) $(SRC)


run:
	./$(EXEC)

clean:
	rm -f $(EXEC)
