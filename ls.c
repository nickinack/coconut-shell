#include "headers.h"
#include "ls.h"
#include "utils.h"

void ls_implementation(int parts, char **args)
{
    char *dirs_to_ls[100];
    char *file_to_ls[100];
    for (int i = 0; i < 100; i++)
    {
        dirs_to_ls[i] = (char *)malloc(100);
        file_to_ls[i] = (char *)malloc(100);
    }
    int dirs_num = 0;
    int file_num = 0;
    int flag_a = 0;
    int flag_l = 0;
    if (parts == 0)
    {
        strcpy(dirs_to_ls[0], ".");
        dirs_num = 1;
    }
    for (int i = 0; i < parts; i++)
    {
        if (strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0)
        {
            flag_a = 1;
            flag_l = 1;
        }
        else if (strcmp(args[i], "-a") == 0)
        {
            flag_a = 1;
        }
        else if (strcmp(args[i], "-l") == 0)
        {
            flag_l = 1;
        }
        else 
        {
            if(strcmp(args[i], "~") == 0)
            {
                args[i] = home_dir;
            }
            if(access(args[i], F_OK ) == 0 && strcmp(args[i], "..") && strcmp(args[i], ".")) 
            {
                strcpy(file_to_ls[file_num], args[i]);
                file_num++;
            }
            else 
            {
                struct stat dir;
                if (stat(args[i], &dir) == 0 && S_ISDIR(dir.st_mode))
                {
                    strcpy(dirs_to_ls[dirs_num], args[i]);
                    dirs_num++;
                }
                else
                {
                    printf("ls: cannot access '%s': no such file or directory\n", args[i]);
                }
            }
        }
    }
    if (dirs_num == 0 && (flag_a || flag_l) && file_num == 0)
    {
        strcpy(dirs_to_ls[dirs_num], ".");
        dirs_num++;
    }
    for (int i = 0; i < file_num; i++)
    {
        if (flag_l != 1)
        {
            printf("%s \n\n", file_to_ls[i]);
        }
        if (flag_l == 1)
        {
            ls_file(file_to_ls[i]);
            printf("\n");
        }
    }
    for (int i = 0; i < dirs_num; i++)
    {
        if (dirs_num > 1 || file_num >= 1)
        {
            printf("%s: \n", tilda_add(dirs_to_ls[i]));
        }
        if (flag_l == 1)
        {
            blkcnt_t blocks = cnt_blocks(dirs_to_ls[i]);
            printf("total %d\n", (int)blocks);
        }
        ls_dir(dirs_to_ls[i], flag_a, flag_l);
        if (dirs_num > 1)
        {
            printf("\n\n");
        }
    }
    return;
}

void ls_dir(char *dir, int flag_a, int flag_l)
{
    DIR *folder;
    struct dirent *entry;
    folder = opendir(dir);
    if (folder == NULL){
        printf("unable to read directory \n");
        return;
    }
    if (flag_l == 1)
    {
        struct stat fileStat;
        struct passwd *usr;
        struct group *grp;
        while ( (entry=readdir(folder)) )
        {
            if (entry->d_name[0] == '.' && flag_a == 0)
            {
                continue;
            }
            char *system = (char *)malloc(MINI_SZE);
            char *date = (char *)malloc(MINI_SZE);
            char *buf = (char *)malloc(MINI_SZE);
            strcpy(buf, tilda_change(dir));
            strcpy(system, buf);
            strcat(system, "/");
            strcat(system, entry->d_name);
            if (stat(system, &fileStat) < 0)
            {
                printf("not able to access files in the directory \n");
                return;
            }
            usr = getpwuid(fileStat.st_uid);
            grp = getgrgid(fileStat.st_gid);
            if (!usr->pw_name || !grp->gr_name)
            {
                printf("unable to retrieve user/group \n");
                return;
            }
            printf( (S_ISDIR(fileStat.st_mode))  ? "d" : "-");
            printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t%d", fileStat.st_nlink);
            printf("\t%s", usr->pw_name);
            printf("\t%s", grp->gr_name);
            printf("\t%lld", (long long int)fileStat.st_size);
            strftime(date, 50, "%b  %d  %I: %M", gmtime(&(fileStat.st_ctime)));
            printf("\t%s", date);
            printf("\t%s", entry->d_name);
            free(system);
            free(date);
            free(buf);
            printf("\n");
        }
    }
    while ( (entry=readdir(folder)) )
    {   
        if(entry->d_name[0] == '.' && flag_a == 0)
            continue;
        printf("%s \n", entry->d_name);
    }
    free(entry);
    free(folder);
    return;
}

void ls_file(char *system)
{
    struct stat fileStat;
    struct passwd *usr;
    struct group *grp;
    char *date = (char *)malloc(MINI_SZE);
    if (stat(system, &fileStat) < 0)
    {
        printf("not able to access files in the directory \n");
        return;
    }
    usr = getpwuid(fileStat.st_uid);
    grp = getgrgid(fileStat.st_gid);
    if (!usr->pw_name || !grp->gr_name)
    {
        printf("unable to retrieve user/group \n");
        return;
    }
    printf( (S_ISDIR(fileStat.st_mode))  ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\t%d", fileStat.st_nlink);
    printf("\t%s", usr->pw_name);
    printf("\t%s", grp->gr_name);
    printf("\t%lld", (long long int)fileStat.st_size);
    strftime(date, 50, "%b  %d  %I: %M", gmtime(&(fileStat.st_ctime)));
    printf("\t%s", date);
    printf("\t%s", system);
    free(system);
    free(date);
    printf("\n");
}

blkcnt_t cnt_blocks(char *dir)
{
    blkcnt_t total_blocks = 0;
    DIR *folder;
    folder = opendir(dir);
    if (folder == NULL){
        printf("unable to read directory \n");
        return 0;
    }
    struct stat fileStat;
    struct dirent *entry;
    while ( (entry=readdir(folder)) )
    { 
        char *system = (char *)malloc(MINI_SZE);
        char *buf = (char *)malloc(MINI_SZE);
        strcpy(buf, tilda_change(dir));
        strcpy(system, buf);
        strcat(system, "/");
        strcat(system, entry->d_name);
        if (stat(system, &fileStat) < 0)
        {
            printf("not able to access files in the directory \n");
            return total_blocks;
        }
        total_blocks += fileStat.st_blocks;
        free(system);
        free(buf);
    }
    free(entry);
    free(folder);
    return total_blocks;
}
