CC = gcc
UNAME := $(shell uname)

CFLAGS = -Wall $(shell sdl2-config --cflags --static-libs)

ifeq ($(UNAME), Linux)
	CFLAGS = -Wall -lSDL2
endif

all: 
	make run

run: build
	./main.exe

build: main.c
	$(CC) main.c -o main.exe $(CFLAGS)

clean:
	rm -f *.exe *.o
