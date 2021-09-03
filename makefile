all: initialize

initialize: cd.o echo.o pwd.o main.o prompt.o input.o 
	gcc -o a cd.o echo.o pwd.o main.o prompt.o input.o

cd.o: cd.c
	gcc -c cd.c

echo.o: echo.c
	gcc -c echo.c

pwd.o: pwd.c
	gcc -c pwd.c

main.o: main.c
	gcc -c main.c

prompt.o: prompt.c
	gcc -c prompt.c

input.o: input.c
	gcc -c input.c


