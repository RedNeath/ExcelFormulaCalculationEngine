wd != pwd

all:build-linux

build-linux:
	mkdir -p bin
	gcc -Wall -shared \
 		-o bin/libefce.so \
 		-fPIC \
 		src/efce.c \
 		src/context.c \
 		src/parser.c \
 		src/processing/pre_processor.c \
 		src/functions/functions_facade.c \
 		src/functions/mathematics_and_trigonometry/*.c

tests-linux:
	mkdir -p bin
	gcc -Wall -c -fPIC src/*.c && \
		ar rcs lib/libefce.a *.o && \
		rm *.o && \
		gcc -Wall -L$(wd)/lib -o bin/tests test/tests.c -lmunit -lefce
	./bin/tests
	rm lib/libefce.a
	rm bin/tests

clean:
	rm -Rf bin
	rm lib/libefce.a
