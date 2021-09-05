all: initialize

initialize: utils.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o 
	gcc -o a utils.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o

cd.o: cd.c
	gcc -c cd.c -std=c99

ls.o: ls.c
	gcc -c ls.c -std=c99

echo.o: echo.c
	gcc -c echo.c -std=c99

pwd.o: pwd.c
	gcc -c pwd.c -std=c99

main.o: main.c
	gcc -c main.c -std=c99

prompt.o: prompt.c
	gcc -c prompt.c -std=c99

input.o: input.c
	gcc -c input.c -std=c99


