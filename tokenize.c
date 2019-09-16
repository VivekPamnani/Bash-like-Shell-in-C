#include "my_shell.h"

//takes "empty args array", "delimiter", "command"
int get_arg(char **arg, char *delim, char *in)
{
    char **buff_ptr = malloc(100);
    // arg[0] = in;
    arg[0] = in;
    // printf("%s\n", arg[0]);
    buff_ptr = &arg[0];
    int num_arg = 0;
    for(int i = 0; strcmp(arg[i], "\0"); i++)
    {
        num_arg++;
        char *temp = arg[i];
        if(i > 0)
        {
            for(int j = 0; temp[0]==' '; j++)                                 //removing leading whitespaces
            {
                temp++;
            }
        }
        arg[i] = temp;
        // printf("%d %s\n", i, arg[i]);
        arg[i+1] = *buff_ptr;
        strtok_r(arg[i+1], delim, buff_ptr);
        // printf("%d %s\n", i, *buff_ptr);
    }
    return num_arg - 1;
}

//tokenizes 'inp'. for i!=0, inp[i] is ith command
int tokenize(char **inp, char *delim, char ***args, int *token_parts)
{
    char **buff_ptr = malloc(100);                                         //input buffer pointer (used as saveptr in strtok)
    buff_ptr = &inp[0];
    int tokens = 0;
    for(int i = 0; strcmp(inp[i], "\0"); i++)
    {
        tokens++;
        args[i][0] = malloc(4096);
        args[i][0] = inp[i];
        if(i > 0) token_parts[i] = get_arg(args[i], " ", inp[i]);
        inp[i+1] = *buff_ptr;
        strtok_r(inp[i+1], delim, buff_ptr);
        // printf("\n");
    }
    return tokens - 1;
}
