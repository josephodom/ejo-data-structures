CC?=gcc

.PHONY=test
test:
	${CC} -c src/test.c -o src/test.o -I`pwd`/include
	${CC} src/test.o -o bin/test
	./bin/test
