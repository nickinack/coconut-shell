# 🥥-shell

## Introduction
🥥-shell is a linux-shell that supports semi-colon seperated list of commands. It can also seperate background processes and foreground processes.
The code has been written in a modular fashion and is easily extensible. More features will be added to this project in the upcoming days. For now,
the shell supports trivial linux commands like `ls`, `cd`, `pwd`, `history`, `repeat`, `echo`, `<cmd> &` and user defined commands like `pinfo` and also 
provides information about finished background process. Information and assumptions for each of the above features have been mentioned below. 

## Running the 🥥-shell
In order to run the 🥥-shell, clone the repository and cd into the repository as follows:
```bash
git clone https://github.com/nickinack/cshell.git
cd cshell
```
Before running the shell, we first clear the existing output files and the history using the clean command:
```bash
make clean
```
Once done, we run the make command to create an executable and run the executable:
```bash
make
./a
```
Once done, the shell output would look something like this:
```bash
(base) nickinack@Karthiks-MBP-2 ass2 % ./a
<nickinack@Karthiks-MBP-2:~> pwd
/Users/nickinack/Desktop/OSN/ass2 
<nickinack@Karthiks-MBP-2:~> <enter commands mentioned below>
```


## Features
| 🥥-shell element | Feature(s) | Usage | Example |
| :---: | :---: | :---: | :---: |
| echo | echo is used to tokenize your argument by eliminating spaces and outputting the resulting argument. | `echo <arg>` | `echo 'avc'. "daksf"`
| pwd | print the current working directory | `pwd` | `pwd`
| cd | cd into the specified directory. | `cd <arg1>` | `cd ~` and `cd` for working root, `cd <path>` for any path, `cd -` for previous working directory, `cd ..` for parent directory and so on`
| ls | for each operand that names a file of a type other than directory, ls displays its name as well as any requested, associated information. | `ls <flag_list 1> <dir_list_1> <flag_list 2> <dir_list_2>...<flag_list_n> <dir_list_n>` | `ls -al <dir_list>` for hidden directories and their read write permissions, `ls -a <dir_list>` for hidden directories, `ls -l <dir_list>` for permissions and long format list, `ls <dir_list>` for all directory formats except `-` specified above.
| pinfo | given a process id, output info about the the given process. | `pinfo <process_id>` | `pinfo 1324`
| history | provide history of commands entered (max: 20) in the order of oldest to newest. | `history <num>` | `history 10`
| repeats | repeats the given command for n times. multiple repeats in the same commands will be handled by recursion. | `repeat <times> <cmd>` | `repeat 4 repeat 2 echo 1`
| background | runs a process in background and provides termination status of the process one done. | `<cmd> <cmd_args> &` | `gedit abc.txt &`
| foreground | runs a process in foreground and halts the terminal inputs till the process terminates. | `<cmd> <cmd_args>` | `sleep 4`
| misc. | any command not handled above will be handled by the `execvp()` process and be treated as a foreground process. | `<cmd> <cmd_args>` | `vim abc.txt`

## Files 
