CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = q1.o q2a.o q2b.o q2c.o q3a.o q3b.o q3c.o
OBJ1 = q4.o q5.o q6.o

%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS)

all: $(OBJ)
	gcc -pthread q4.c -o q4.o
	gcc -pthread q5.c -o q5.o
	gcc -pthread q6.c -o q6.o

clean:
	rm -f $(OBJ)
	rm -f $(OBJ1)
