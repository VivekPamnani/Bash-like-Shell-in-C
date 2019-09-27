#include "my_shell.h"

int set_streams(char **cmd, int *num_tok)
{
    //destination
    FILE *temp;
    int temp_dest = 1;
    if(get_dest(cmd, *num_tok) > 0)
    {
        int exist = 1; //0 if not, 1 otherwise
        if(access(cmd[get_dest(cmd, *num_tok)+1], F_OK) == -1) 
            exist = 0;
        temp = fopen(cmd[get_dest(cmd, *num_tok)+1], "w");
        temp_dest = open(cmd[get_dest(cmd, *num_tok)+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
        temp_dest = open(cmd[get_dest_append(cmd, *num_tok)+1], O_APPEND | O_CREAT | O_TRUNC, 0644);
        if(!exist)
            chmod(cmd[get_dest_append(cmd, *num_tok)+1], 0644);
        *num_tok = get_dest_append(cmd, *num_tok)-1;
    }
    else
    {
        temp = stdout;
        temp_dest = dup(1);
    }
    print_dest = temp;
    dup2(temp_dest, 1);
    close(temp_dest);

    //source
    int temp_src = 0; //stdin
    if(get_src(cmd, *num_tok) > 0)
    {
        if(access(cmd[get_src(cmd, *num_tok)+1], F_OK) == -1) 
        {
            printf("Error: File '%s' does not exist!\n", cmd[get_src(cmd, *num_tok)+1]);
            temp = stdin;
            temp_src = 0;
            return -1;
        }
        temp = fopen(cmd[get_src(cmd, *num_tok)+1], "r");
        temp_src = open(cmd[get_src(cmd, *num_tok)+1], O_RDONLY);
        *num_tok = get_src(cmd, *num_tok)-1;
    }
    else
    {
        temp = stdin;
        temp_src = dup(0);
    }
    scan_src = temp;   
    dup2(temp_src, 0);
    close(temp_src);
}