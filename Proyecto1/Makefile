CC = gcc
CFLAGS = -pthread -Wall 
OBJ = main.o priority_queue.o car.o list.o carManager.o bridge.o

#compile the program
#get all the .c and .h files (dependencies) and generate the objects files
%.o: ./src/%.c ./include/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

#then generate executable file
./bin/exec: $(OBJ)	
	gcc $(CFLAGS) -o $@ $^
	rm -f *.o

#for running the program
run:
	./bin/exec

#for removing files created
clean:
	rm -f ./bin/exec $(OBJ)