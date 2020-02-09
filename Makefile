run: tema1
	./tema1

build: tema1

tema1: tema1.c
	gcc -Wall -g tema1.c moving_parts_foo.c map_foo.c new_stuff.c -o tema1 -lm

clean:
	rm *.o tema1
