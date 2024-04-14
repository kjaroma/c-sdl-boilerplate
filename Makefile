CC = gcc
CFLAGS = -Wall `sdl2-config --cflags --static-libs`

all: 
	make run

run: build
	./main.exe

build: main.c
	pwd
	$(CC) main.c -o main.exe $(CFLAGS)

clean:
	rm -f *.exe *.o
