#include "my_shell.h"

void f_setenv(char **env)
{
    printf("%s\n", env[3]);
    if(strcmp(env[4], "") || !strcmp(env[3], ""))
    {
        printf("Error: Too few/many arguments for setenv. Usage: \"setenv var [value]\"\n");
        return;
    }
    if(strcmp(env[3], ""))
    {
        setenv(env[2], env[3], 1);
    }
    else
    {
        setenv(env[2], "", 1);
    }
    return;
}

void f_unsetenv(char **env)
{
    if(!strcmp(env[2], ""))
    {
        printf("Error: Too few arguments for setenv. Usage: \"unsetenv var [value]\"\n");
        return;
    }
    unsetenv(env[1]);
    
}