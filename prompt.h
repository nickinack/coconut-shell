char hostname[10000]; // get the current hostname
char username[10000]; // get the current username

#define PROMPT_COLOR "\033[1;32m"
#define DEFAULT_COLOR "\033[0m"

int get_host_user_dir_details();
char *get_prompt();
void prompt();
