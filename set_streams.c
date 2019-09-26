#include "my_shell.h"

int set_streams(char **cmd, int *num_tok)
{
    //destination
    FILE *temp;
    if(get_dest(cmd, *num_tok) > 0)
    {
        int exist = 1; //0 if not, 1 otherwise
        if(access(cmd[get_dest(cmd, *num_tok)+1], F_OK) == -1) 
            exist = 0;
        temp = fopen(cmd[get_dest(cmd, *num_tok)+1], "w");
        if(!exist)
            chmod(cmd[get_dest(cmd, *num_tok)+1], 0644);
        *num_tok = get_dest(cmd, *num_tok)-1;
    }
    else if(get_dest_append(cmd, *num_tok) > 0)
    {
        int exist = 1; //0 if not, 1 otherwise
        if(access(cmd[get_dest_append(cmd, *num_tok)+1], F_OK) == -1) 
            exist = 0;
        temp = fopen(cmd[get_dest_append(cmd, *num_tok)+1], "a");
        if(!exist)
            chmod(cmd[get_dest_append(cmd, *num_tok)+1], 0644);
        *num_tok = get_dest_append(cmd, *num_tok)-1;
    }
    else
        temp = stdout;
    print_dest = temp;

    //source
    // if(get_src(cmd, *num_tok) > 0)
    // {
    //     if(access(cmd[get_dest(cmd, *num_tok)+1], F_OK) == -1) 
    //     {
    //         printf("Error: File '%s' does not exist!\n", cmd[get_dest(cmd, *num_tok)+1]);
    //         return -1;
    //     }
    //     temp = fopen(cmd[get_dest(cmd, *num_tok)+1], "r");
    //     *num_tok = get_dest(cmd, *num_tok)-1;
    // }
    // else
    //     temp = stdin;
    // print_dest = temp;   
}