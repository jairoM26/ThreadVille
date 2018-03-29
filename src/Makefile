#directories
BDIR = ../bin/
IDIR = ../include/
LDIR = ../lib/
SDIR = ./

#setting exec files
_DYNAMIC_APP = main_d 
DYNAMIC_APP = $(patsubst %, $(BDIR)%, $(_DYNAMIC_APP))

#libraries names
_DYNAMIC_LIBRARY = libScheduler.so
DYNAMIC_LIBRARY = $(patsubst %, $(LDIR)%, $(_DYNAMIC_LIBRARY))

#setting files name and directories
_OBJ = scheduler.o
OBJ = $(patsubst %, $(LDIR)%, $(_OBJ))

SRC = $(LDIR)scheduler.c
APP_SRC = $(SDIR)main.c

#flags
CC = gcc
IFLAGS = -I$(IDIR)
CFLAGS = -c -fPIC
OFLAGS = -o

#creating/compiling dynamic exec
$(DYNAMIC_APP): $(APP_SRC) $(DYNAMIC_LIBRARY)
	@echo creating $@ 
	$(CC) $(IFLAGS) $(LINKFLAGS) $(OFLAGS) $(DYNAMIC_APP) $(APP_SRC) -Bdynamic $(DYNAMIC_LIBRARY) $(LFLAGS) 
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./
	@echo $@ created

$clean:
	rm -f $(APP_SRC) $(SRC)