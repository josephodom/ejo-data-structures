CC?=gcc

.PHONY=run-tests
run-tests:
	${CC} -c test/test.c -o test/test.o -I`pwd`/include
	${CC} -c test/test_queue.c -o test/test_queue.o -I`pwd`/include
	${CC} -c test/test_stack.c -o test/test_stack.o -I`pwd`/include
	${CC} \
		test/test.o \
		test/test_queue.o \
		test/test_stack.o \
		-o main
	./main
