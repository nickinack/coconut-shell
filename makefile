all: initialize

initialize: headers.o utils.o execute_cmd.o pinfo.o background.o foreground.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o repeat.o history.o dup_fd.o jobs.o sig.o bg.o fg.o
	gcc -o a headers.o utils.o execute_cmd.o pinfo.o background.o foreground.o cd.o ls.o echo.o pwd.o main.o prompt.o input.o repeat.o history.o dup_fd.o jobs.o sig.o bg.o fg.o

headers.o: headers.c
	gcc -c headers.c
	
utils.o: utils.c
	gcc -c utils.c

execute_cmd.o: execute_cmd.c
	gcc -c execute_cmd.c

pinfo.o: pinfo.c
	gcc -c pinfo.c

background.o: background.c
	gcc -c background.c

foreground.o: foreground.c
	gcc -c foreground.c

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

repeat.o: repeat.c
	gcc -c repeat.c

history.o: history.c
	gcc -c history.c

dup_fd.o: dup_fd.c
	gcc -c dup_fd.c

jobs.o: jobs.c
	gcc -c jobs.c

sig.o: sig.c
	gcc -c sig.c

bg.o: bg.c
	gcc -c bg.c

fg.o: fg.c
	gcc -c fg.c
	
clean:
	rm -rf *.o 
	rm -rf a
	rm -rf a.out.dSYM


