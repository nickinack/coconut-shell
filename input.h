#ifndef __INPUT_H
#define __INPUT_H

#include <getopt.h>

int tokenise(char *str, char **args);
void process_input(char* buffer);
int get_input();

#endif