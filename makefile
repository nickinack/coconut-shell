all: initialize

initialize: cd.o main.o prompt.o input.o 
	gcc -o a cd.o main.o prompt.o input.o

cd.o: cd.c
	gcc -c cd.c

main.o: main.c
	gcc -c main.c

prompt.o: prompt.c
	gcc -c prompt.c

input.o: input.c
	gcc -c input.c


