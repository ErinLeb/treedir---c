CC=gcc
CFLAGS=-Wall
DEPS= lib/ls.h lib/mkdir.h lib/print.h lib/pwd.h lib/struct.h lib/touch.h lib/test_struct.h lib/chemin.h
OBJ = ls.o mkdir.o print.o pwd.o struct.o touch.o chemin.o test_struct.o chemin.o
EXEC=main

all : $(EXEC)

%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

main : main.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

test : test.o $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf $(EXEC) test *.o
