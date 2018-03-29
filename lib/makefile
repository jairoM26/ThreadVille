#directories
BDIR = ../bin/
IDIR = ../include/
LDIR = ./
SDIR = ../src

_DYNAMIC_LIBRARY = libScheduler.so
DYNAMIC_LIBRARY = $(patsubst %, $(LDIR)%, $(_DYNAMIC_LIBRARY))

#flags
CC = gcc
IFLAGS = -I$(IDIR)
LFLAGS = -lm
CFLAGS = -c -fPIC
OFLAGS = -o
LINKFLAGS = -shared -fPIC

#setting files name and directories
_OBJ = scheduler.o
OBJ = $(patsubst %, $(LDIR)%, $(_OBJ))
SRC = $(LDIR)scheduler.c

#crating dynamic library
$(DYNAMIC_LIBRARY): $(OBJ) 
	@echo creating $@ with $<
	ld $(OFLAGS) $(DYNAMIC_LIBRARY) $(OBJ) $(LINKFLAGS)
	@echo $@ created
	
#creating operaciones.o in lib directory
$(OBJ):$(SRC)
	@echo compiling $<
	$(CC) $(IFLAGS) $(CFLAGS) $(OFLAGS) $@ $<
	@echo $@ created


clean:
	rm -f $(DYNAMIC_APP) $(STATIC_LIBRARY)
