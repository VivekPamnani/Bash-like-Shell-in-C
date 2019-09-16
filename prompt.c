#include "my_shell.h"

void f_prompt(char *inp_buffer, char *home_dir)
{
    char curr_dir[4096];
    getcwd(curr_dir, sizeof(curr_dir));
    struct utsname sysinfo;
    uname(&sysinfo);
    char *loc = NULL;
    int offset = strlen(home_dir);
    loc = strstr(curr_dir, home_dir);
    if(loc == NULL)
        printf("<%s@%s:%s>", username, sysinfo.nodename, curr_dir);
    else
        printf("<%s@%s:~%s>", username, sysinfo.nodename, loc+offset);
    return fgets(inp_buffer, 4096, stdin);
}