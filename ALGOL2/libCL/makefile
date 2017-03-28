# compilateur
all: list

list: listep_op.o testliste.o
	gcc -o list listep_op.o testliste.o

listep_op.o: listep_op.c listep_op.h listep.h
	gcc -o listep_op.o -c listep_op.c -g -Wall 

testliste.o: testliste.c listep.h
	gcc -o testliste.o -c testliste.c -g -Wall 

clean:
	rm -rf *.o


