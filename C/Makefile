CC=gcc
H=shell.h

%.o: %.c $(H)
		$(CC) -c -o $@ $<
all:
	$(CC) -c command.c main.c
	$(CC) -o shell command.o main.o
command.o : command.c
	$(CC) -c command.c
main.o : main.c
	$(CC) -c main.c
clean:
	rm -vf *.o
	rm shell