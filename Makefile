# CC - compiler
CC=gcc
# COPT - compiler flags
COPT=-Wall -Wpedantic -g
# BIN - binary
BIN_TEST=test
# .c files located in each folder
DATA_C=$(wildcard data_types/*.c)
STRUCT_C=$(wildcard structure_types/*.c)
# OBJ - compiled source files that should be linked
# Find all .c files and convert to their corresponding .o name
OBJ=$(DATA_C:.c=.o) $(STRUCT_C:.c=.o) Node.o Structure.o util.o

$(BIN_TEST): test.c $(OBJ)
	$(CC) -o $@ test.c *.o $(COPT)

run_test:
	./$(BIN_TEST)

tester: $(BIN_TEST) run_test clean

sample: sample.c
	$(CC) -o sample sample.c $(COPT)
	./sample

all: $(BIN_TEST) sample

# Wildcard rule to make any .o file,
# given a .c and .h file with the same leading filename component
%.o: %.c %.h
	$(CC) -c $< $(COPT)

format:
	clang-format -i *.c *.h

.PHONY: clean
clean:
	rm -rf $(BIN_TEST) $(BIN_TEST).exe *.o *.dSYM sample sample.exe
