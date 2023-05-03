CC=gcc
CFLAGS=-Wall
DEPS= lib/ls.h lib/mkdir.h lib/print.h lib/pwd.h lib/struct.h lib/touch.h lib/test_struct.h lib/chemin.h lib/cp.h lib/cd.h lib/rm.h lib/mv.h lib/parseur.h
OBJ = ls.o mkdir.o print.o pwd.o struct.o touch.o chemin.o test_struct.o cp.o cd.o rm.o mv.o parseur.o
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