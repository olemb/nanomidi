all: example nanomidi.o

example: nanomidi.o
	gcc -Wall -o example example.c nanomidi.o

nanomidi.o: nanomidi.c nanomidi.h
	gcc -Wall -c nanomidi.c

clean:
	rm *.o example
