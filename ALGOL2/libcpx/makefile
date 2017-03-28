# Compilateur
CC=gcc -c -g -Wall

# Edition de liens
LD=gcc -o


all: test


test: test.o cplxio.o cplxop.o
	$(LD) test test.o cplxio.o cplxop.o

test.o: test.c cplx.h cplxop.h cplxio.h
	$(CC) test.c

cplxop.o: cplxop.c cplxio.h cplx.h
	$(CC) cplxop.c

cplxio.o: cplxio.c cplx.h
	$(CC) cplxio.c

clean:
	rm -f test *.o

