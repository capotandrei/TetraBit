run: main
	./main

build: main

tema1: main.c
	gcc -Wall -g main.c moving_parts_foo.c map_foo.c new_stuff.c -o main -lm

clean:
	rm *.o main
