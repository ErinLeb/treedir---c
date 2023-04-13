CC=gcc
CFLAGS=-Wall
DEPS= lib/ls.h lib/mkdir.h lib/print.h lib/pwd.h lib/struct.h lib/touch.h
EXEC=main

all : $(EXEC)

%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

main : main.o ls.o mkdir.o print.o pwd.o struct.o touch.o
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf $(EXEC) *.o
