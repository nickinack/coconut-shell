#include <stdio.h>  /* printf */
#include <getopt.h> /* getopt */
#include <string.h>

int main(int argc, char *argv[])
{
    char *s = "Hello how !";
    strcpy(argv, s);
    int opt;
    while ((opt = getopt(argc, argv, ":a:b:X")) != -1)
    {
        switch (opt) 
        {
        case 'a':
        printf("Option a has arg: %s\n", optarg);
        break;
        case 'b':
        printf("Option b has arg: %s\n", optarg);
        break;
        case 'X':
        printf("Option X was provided\n");
        break;
        case '?':
        printf("Unknown option: %c\n", optopt);
        break;
        case ':':
        printf("Missing arg for %c\n", optopt);
        break;
        }
    }

    /* Get all of the non-option arguments */
    if (optind < argc) 
    {
    printf("Non-option args: ");
    while (optind < argc)
        printf("%s ", argv[optind++]);
    printf("\n");
    }

    return 0;
}