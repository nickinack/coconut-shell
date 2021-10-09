# 🥥-shell

## Introduction
🥥-shell is a linux-shell that supports semi-colon seperated list of commands, piping, redirection and provides signal handling. It can also support background processes and foreground processes.
The code has been written in a modular fashion and is easily extensible. More features will be added to this project in the upcoming days.
The shell supports trivial linux commands like `ls`, `cd`, `pwd`, `history`, `repeat`, `echo`, `<cmd> &`, `cat a.txt > b.txt`, `ls > sort | wc -l > a.txt` and user defined commands like `pinfo`, `fg`, `bg`, `jobs`, `sig` and also 
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
| jobs | shows a list of background jobs (stopped or running). | `<cmd> <cmd_args>` | `jobs -s ; jobs -r ; jobs`
| redirection | the shell supports redirections. you can use redirections like `>`, `<` or `>>`. | `<cmd> <redir_op> <file>` | `sort < ls`
| piping | the output of one command can be directed into the input of the successive command after the pipe operator. | `<cmd1> <pipe> <cmd2> <pipe> <command3> ..` | `ls | sort | cat`
| fg | bring any background process to the foreground. | `fg <job_no>` | `fg 0`
| bg | change the status of any background process to running. | `bg <job_no>` | `bg 0`
| sig | send any signal to a given background process. | `sig <job_no> <signal_id>` | `sig 0 9` 
| signal handling | Ctrl-C press terminates any running foreground process. Ctrl-Z pushes any foreground process to background and changes it status from running to stopped. Ctrl-D exits from the shell when no process is running. | `<Ctrl + <alphabet C/Z/D>>` | `^C` 
| replay | replay the command given intervals and total period | `replay -interval <interval> -period <period> -command <cmd>` | `replay -command echo hello -interval 3 -period 6` 
| misc. | any command not handled above will be handled by the `execvp()` process and be treated as a foreground process. | `<cmd> <cmd_args>` | `vim abc.txt`

## Files 
Each of the file listed below includes its corresponding `.c` and `.h` files.
 - `main`: runs the while loop till an exit command is given or a fatal error occurs. Inside the loop, we get the input and display the prompt.
 - `input`: gets the input, tokenizes multiple commands based on `;` and each of the commands are tokenized further based on `<spac>` and we then get the commands and the list of arguments and direct the flow to the respective command execution files.
 - `ls`: execution of the ls command. Flag booleans are collected, list of directories are stored and we use hte `readdir()` system call along with `stat` for displaying list of directories and files along with file permissions (subjected to which flag is provided).
 - `cd`: cd into a directory using the `chdir()` system call.
 - `pwd`: get the current working directory using the `getpwd()` system call.
 - `echo`: print the tokenized arguments.
 - `pinfo`: access the `/proc/[pid]/` directory and read the files `stat` (for reading the current status and memory usage) and `exec` (readlink) in order to provide info about the process.
 - `background`: run the given command in background, store the command and associated pid in a linked list so that when the process terminates, we go to the signal handler, use the `waitpid()` system call with the `WNOHANG` parameter in order to get the pid, use `WIFEXITED` in order to check exit status and print the termination message. If the return value of `execvp` for a background process is -1, we kill the background process using the `kill(pid, SIGCHLD)` system call for the `WIFEXITED` to give an abnormal termination return value.
 - `foreground`: run the process in foreground and halt the terminal input by using `waitpid()` system call with the `WUNTRACED` parameter. Once process is done, waitpid captures the termination signal and program flow of the parent process continues.
 - `history`: use a character array to store history and use file operations to store the past 20 commands in a file named `history.txt`. <b>Do not use</b> make clean if you want to retain history between two shell runs.
 - `repeat`: recursively repeat the given command until we surpass the last repeat. 
 - `utils`: functions to add `~` to an absolute path for user inputs, remove `~` in order to make the directories accessible by system calls and signal handlers for process terminations.
- `jobs`: functions to access functions in `headers` and format them; jobs are lexicographically sorted while being added into the linked list iteself.
- `dup_fd`: file to handle file descriptors of `STDIN_FILENO` and `STDOUT_FILENO`; redirection operator is handled while parsing command and functions in this file are accessed to change and restore file descriptors during each parse command step.
- `fg`: contains functions to handle the `fg` command. Give terminal access to a process, wait for the process to end and depending on the exit status, take the next action.
- `bg`: contains functions to handle the `bg` command. Send `SIGCONT` signal to the process.
- `sig`: contains functions to handle the `sig` command. Use `kill` to send signals to given process after retrieving the PID of the process from the given job ID.
- `pipe`: contains functions to handle the `pipe` command. Jobs from main input function are routed to pipe. The checker seperates the pipes and sends it to the `parse_cmd`. If 2 or more pipes exist, we juggle between `STDIN_FILENO` and `STDOUT_FILENO` descriptors. Each command between a pipe is treated as a process.
- `replay`: contains functions to handle the replay command. sleep before every command partse in the while loop.
 
 ## Assumptions
 For the ease of coding, the following assumptions have been made:
 - The sizes of strings given as input to the shell do not exceed 100,000 and the size of each command does not exceed 10,000. 
 - The structure of the files in `/proc/[pid]` does not vary across systems.
 - we kill background process on `execvp` failure.
 - The shell is limited to linux systems.
 - A job number assigned to a process is unique and will not be reassigned even after the process' death.
 - The shell assumes following precedence: `logical > pipe > redirection > background`. 
 
 ## Author
 🥥-shell has been designed by <a href="https://nickinack.github.io/">karthik viswanathan</a>.
