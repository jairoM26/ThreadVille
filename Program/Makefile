CC = gcc
CFLAGS = -pthread -Wall 
DEPS = list.h car.h common.h queue.h
OBJ = main.o list.o car.o queue.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
