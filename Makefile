CC = gcc
CFLAGS = -Wall -pthread

all: philosophers_dinner

philosophers_dinner: philosophers_dinner.o
	$(CC) $(CFLAGS) -o $@ $^

philosophers_dinner.o: philosophers_dinner.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f philosophers_dinner philosophers_dinner.o

run: philosophers_dinner
	./philosophers_dinner

exec: all
	./philosophers_dinner
