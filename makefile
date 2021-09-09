all: initialize

initialize: utils.o pinfo.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o 
	gcc -o a utils.o pinfo.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o

utils.o: utils.c
	gcc -c utils.c

pinfo.o: pinfo.c
	gcc -c pinfo.c

cd.o: cd.c
	gcc -c cd.c 

ls.o: ls.c
	gcc -c ls.c 

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


