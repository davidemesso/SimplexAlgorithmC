OBJ = program.o simplex.o fraction.o
CC=gcc
CFLAGS=-Wall
BIN=./bin/

simplex.exe: $(OBJ) dependencies
	gcc -o simplex.exe $(OBJ)

-include dependencies

.PHONY: clean cleanall
dependencies:
	gcc -MM *.c > dependencies
clean:
	rm -f *.o
cleanall:
	rm -f simplex *.o