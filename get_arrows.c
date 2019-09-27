#include "my_shell.h"

int get_src(char **in, int lim)
{
    for(int i = 0; i < lim; i++)
    {
        if(!strcmp(in[i], "<"))
        {
            return i;
        }
    }
    return -1;
}

int get_dest(char **in, int lim)
{
    for(int i = 0; i < lim; i++)
    {
        if(!strcmp(in[i], ">"))
        {
            return i;
        }
    }
    return -1;
}

int get_dest_append(char **in, int lim)
{
    for(int i = 0; i < lim; i++)
    {
        if(!strcmp(in[i], ">>"))
        {
            return i;
        }
    }
    return -1;
}

int get_pipe(char **cmd, int lim, int begin)
{
    for(int i = begin; i < lim; i++)
    {
        if(!strcmp(cmd[i], "|"))
        {
            return i;
        }
    }
    return lim;
}