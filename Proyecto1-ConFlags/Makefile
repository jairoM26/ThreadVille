CC = gcc
CFLAGS = -pthread 
OBJ = main.o priority_queue.o car.o  carManager.o bridge.o mythread.o arduino-serial-lib.o

#compile the program
#get all the .c and .h files (dependencies) and generate the objects files
%.o: ./src/%.c ./include/%.h
	$(CC) $(CFLAGS) -c -o $@ $< -lm

#then generate executable file
./bin/exec: $(OBJ)	
	gcc $(CFLAGS) -o $@ $^ -lm
	rm -f *.o

#for running the program
run:
	./bin/exec

#for removing files created
clean:
	rm -f ./bin/exec $(OBJ)