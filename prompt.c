#include "my_shell.h"

int f_prompt(char *inp_buffer, char *home, int accept_input)
{
    char *username = getenv("USER");
    char curr_dir[4096];
    getcwd(curr_dir, sizeof(curr_dir));
    struct utsname sysinfo;
    uname(&sysinfo);
    char *loc = NULL;
    int offset = strlen(home);
    loc = strstr(curr_dir, home);
    if(loc == NULL)
        printf("<%s@%s:%s>", username, sysinfo.nodename, curr_dir);
    else
        printf("<%s@%s:~%s>", username, sysinfo.nodename, loc+offset);
    if(accept_input)
        fgets(inp_buffer, 4096, stdin);
    return 1;
}