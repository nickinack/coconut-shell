#include<stdio.h>    
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <pwd.h>
#define SZE 10000
#define MINI_SZE 100

char home_dir[10000]; // stores the home directory
char cur_dir[10000];  // stores the current working directory
char prev_dir[10000];
int PROGRAM_EXIT;
