#include "my_shell.h"

void f_echo(char **echo, int num_tokens)
{
    print_dest = fopen(echo[get_dest(echo, num_tokens)+1], "w");
    // print_dest = fopen(file_name, "w");
    printf("s:%d d:%d\n", get_src(echo,num_tokens), get_dest(echo, num_tokens));
    // printf("num: |%d |%d |%s\n", print_dest, errno, echo[get_dest(echo, num_tokens)+1]);

    if(print_dest != 0)
    {
        if(errno == 2)
        {
            printf("File '%s' does not exist.\n", echo[get_dest(echo, num_tokens)+1]);
        }
        else
        {
            for(int i = 2; strcmp(echo[i], "") && i < get_dest(echo, num_tokens); i++)
            {
                fprintf(print_dest==EOF?1:print_dest, "%s ", echo[i]);
            }
            fprintf(print_dest==EOF?1:print_dest, "\n");
            fclose(print_dest);
        }
        
    }
    else
    {
        for(int i = 2; strcmp(echo[i], ""); i++)
        {
            printf("%s ", echo[i]);
        }
        printf("\n");
    }
}
