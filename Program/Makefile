CC = gcc
CFLAGS = -Wall
DEPS = list.h car.h common.h
OBJ = main.o list.o car.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
