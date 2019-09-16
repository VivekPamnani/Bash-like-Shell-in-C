#include "my_shell.h"

void f_echo(char **echo)
{
    for(int i = 2; strcmp(echo[i], ""); i++)
    {
        printf("%s ", echo[i]);
    }
    printf("\n");
}
