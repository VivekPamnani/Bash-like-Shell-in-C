#include "my_shell.h"

char *f_prompt(char *inp_buffer, char *home, int accept_input)
{
    char *prompt = malloc(4096);
    char *username = getenv("USER");
    char curr_dir[4096];
    getcwd(curr_dir, sizeof(curr_dir));
    struct utsname sysinfo;
    uname(&sysinfo);
    char *loc = NULL;
    int offset = strlen(home);
    loc = strstr(curr_dir, home);
    if(loc == NULL)
        sprintf(prompt, "<%s@%s:%s>", username, sysinfo.nodename, curr_dir);
    else
        sprintf(prompt, "<%s@%s:~%s>", username, sysinfo.nodename, loc+offset);
    if(accept_input)
    {
        // fgets(inp_buffer, 4096, stdin);
        inp_buffer = readline(prompt);
        add_history(inp_buffer);
        // fflush(stdout);
    }
    return inp_buffer;
}