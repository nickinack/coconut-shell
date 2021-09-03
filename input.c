#include "input.h"
#include "cd.h"
#include "headers.h"

int get_input()
{
    char *buffer;
    size_t bufsize = 1;
    size_t command;
    buffer = (char *)malloc(bufsize * sizeof(char));
    int ptr = getline(&buffer, &bufsize, stdin);
    buffer[ptr-1] = '\0';
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer \n");
        PROGRAM_EXIT = -1;
        return -2;
    }
    if(strcmp(buffer, "exit") == 0){
        printf("Exiting the shell .... \n");
        PROGRAM_EXIT = -1;
        return -1;
    }
    process_input(buffer);
    return 0;
}

int tokenise(char *buffer, char **args){
    char space[2] = " ";
    char temp_buf[SZE];
    strcpy(temp_buf, buffer);
    char* token = strtok(temp_buf, space);
    int k = 0; 
    while(token != NULL){
        args[k++] = token;
        token = strtok(NULL, space);
    }
    return k;
}

void process_input(char *buffer){   
    // tokenise, arguments
    char *args[100];
    int parts = tokenise(buffer, args);
    char *command = args[0];
    if(strcmp(command, "cd") == 0){
        process_cd(parts, args);
    }
    else if(strcmp(command, "ls") == 0){
        printf("LS \n");
    }
    else{
        printf("command not found: %s \n", command);
    }
}  