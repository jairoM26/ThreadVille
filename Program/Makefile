CC = gcc
CFLAGS = -pthread -Wall 
DEPS = list.h car.h queue.h common.h linkedGraph.c priority_queue.c

OBJ = main.o list.o queue.c car.o 
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(OBJ)
	gcc $(CFLAGS) -o $@ $^
