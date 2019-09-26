#include "my_shell.h"

void f_echo(char **echo, int num_tokens)
{
    for(int i = 2; strcmp(echo[i], "") && i <= num_tokens; i++)
        fprintf(print_dest, "%s ", echo[i]);
    fprintf(print_dest, "\n");

}
