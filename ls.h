#include <getopt.h>
#include <dirent.h>
#include <time.h>
#include <grp.h>
#include <uuid/uuid.h>
#include <sys/stat.h>

blkcnt_t cnt_blocks(char *dir);
void ls_dir(char *dir, int flag_a, int flag_l);
void ls_implementation(int parts, char **args);