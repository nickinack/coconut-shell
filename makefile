all: initialize

initialize: main.o prompt.o input.o
	gcc -o a main.o prompt.o input.o

main.o: main.c
	gcc -c main.c

prompt.o: prompt.c
	gcc -c prompt.c

input.o: input.c
	gcc -c input.c
