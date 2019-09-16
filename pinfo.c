#include "my_shell.h"

char *f_pinfo(int r_pid, int show)
{
    char stat_file[4096];
    char path_file[4096];
    char buffer[4096];
    FILE* status;
    struct stat file;
    char temp[4096];
    char stat[3];
    char size[4096];
    char *path = malloc(4096*sizeof(char*));
    int sz = 0;
    pid_t s_pid = getpid();
    pid_t pid = (r_pid > 0) ? r_pid : s_pid;
    if(show)    printf("pid -- %d\n", pid);
    sprintf(stat_file, "/proc/%d/status", pid);
    status = fopen(stat_file, "r");
    for(int i = 0; fgets(buffer, sizeof(buffer), status); i++)
    {
        // printf("buff %d %s\n", i, buffer);
        strcpy(temp, buffer);
        temp[5] = '\0';
        if(!strcmp(temp, "State"))
        {
            stat[0] = buffer[6];
            stat[1] = buffer[7];
            stat[2] = '\0';
        }
        strcpy(temp, buffer);
        temp[6] = '\0';
        if(!strcmp(temp, "VmSize"))
        {
            for(int k = 8; buffer[k] != ' '; k++)
            {
                size[k-8] = buffer[k];
            }
            sz = atoi(size);
        }
    }
    fclose(status);
    if(show)    printf("Process Status -- %s\n", stat);
    if(show)    printf("memory -- %d\n", sz);
    sprintf(path_file, "/proc/%d/exe", pid);
    readlink(path_file, path, 4096);
    if(show)    printf("Executable Path -- %s\n", path);
    return path;
}
