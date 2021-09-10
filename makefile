all: initialize

initialize: headers.o utils.o execute_cmd.o pinfo.o bg.o fg.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o 
	gcc -o a headers.o utils.o execute_cmd.o pinfo.o bg.o fg.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o

headers.o: headers.c
	gcc -c headers.c
	
utils.o: utils.c
	gcc -c utils.c

execute_cmd.o: execute_cmd.c
	gcc -c execute_cmd.c

pinfo.o: pinfo.c
	gcc -c pinfo.c

bg.o: bg.c
	gcc -c bg.c

fg.o: fg.c
	gcc -c fg.c

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


