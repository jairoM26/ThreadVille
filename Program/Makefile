CC = gcc
CFLAGS = -pthread -Wall 
<<<<<<< HEAD
DEPS = list.h car.h queue.h common.h linkedGraph.c priority_queue.c
=======
DEPS = list.h car.h common.h queue.h
OBJ = main.o list.o car.o queue.o
>>>>>>> de61c52e754e4f5db88eba1dfd6da58e327c8940

OBJ = main.o list.o queue.c car.o 
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
