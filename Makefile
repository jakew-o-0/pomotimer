CC = gcc
CFLAGS = -lncurses -lpthread 


all: pomo-timer clean

pomo-timer: main.o title.o timer_control.o
	$(CC) $(CFLAGS) timer_control.o main.o title.o  -o pomotimer


main.o: main.c
	$(CC) -c main.c

title.o: title.c
	$(CC) -c title.c

timer.o: timer_control.c
	$(CC) -c timer_control.c

clean:
	rm -f *.o
