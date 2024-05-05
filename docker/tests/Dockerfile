FROM ubuntu:latest
LABEL authors="redneath"

RUN apt-get update &&\
    apt-get install build-essential -y

RUN gcc -Wall -shared -o bin/libefce.so -fPIC src/efce.c

# Build & run the tests
RUN gcc -Wall -g tests/tests.c -o bin/tests -L./bin/ -lefce \
    bin/tests
