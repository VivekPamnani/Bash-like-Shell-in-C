#include "my_shell.h"

int main()
{
    print_dest = stdout;
    scan_src = stdin;

    int words[100] = {0};
    
    //printf("%s", home_dir);
    char *home_dir = malloc(4096);
    char *LOL = malloc(4096);
    char *username = getenv("USER");
    char curr_dir[4096];
    getcwd(home_dir, 4096);
    getcwd(curr_dir, 4096);
    home_dir = f_pinfo(-1, 0);
    for(int k = strlen(home_dir); k > 0; k--)
    {
        if(home_dir[k] == '/')
        {
            home_dir[k] = '\0';
            break;
        }
    }
    //inp will store ';' separated commands
    char **inp = malloc(100);                                               //reminder: change length
    //inp_cmd will store the corresponding commands to inp
    char **inp_cmd = malloc(100);                                           //reminder: change length
    //args will store the corresponding arguments to inp
    char ***args = malloc(100 * sizeof(char**));
    // *args = malloc(100);
    //used as saveptr for strtok_r
    int token_parts[100] = {0};
    char **buff_ptr = malloc(100);
    //LOL is input buffer for stdin, change the name.
    char **contents = malloc(1000);
    char **path_contents = malloc(1000);
    int alloted = 0;
    for(int i = 0; i < 100; i++) //change this is contents size changed
    {
        contents[i] = malloc(4096);
        path_contents[i] = malloc(4096);
        alloted = 1;
    }
   for(int i = 0; i < 100; i++)                                             //allocating memory
    {
        args[i] = malloc(100 * sizeof(char *));
        inp[i] = malloc(4096);
        for(int j = 0; j < 100; j++)
        {
            args[i][j] = malloc(4096 * sizeof(char));
        }
    }
    home = home_dir;
    inp_buffer = LOL;
    while(1)
    { 
        getcwd(curr_dir, sizeof(curr_dir));
        // printf("c_dir %s\nh_dir %s\n", curr_dir, home_dir);
        LOL = f_prompt(LOL, home_dir, 1);
        inp[0] = LOL;
        strtok_r(inp[0], "\n", buff_ptr);
        inp[1] = inp[0];
        int tokens = tokenize(inp, ";", args, token_parts);
        // printf("Tokens: %d\n", tokens);
        for(int i = 1; i <= tokens; i++)
        {
            set_streams(args[i], &token_parts[i]);

            if (!strcmp(args[i][1], "\n"))
            {
                continue;
            }
            
            else if(!strcmp(args[i][1], "cd"))
            {
                f_cd(args[i], home_dir);
            }
            else if(!strcmp(args[i][1], "echo"))
            {
                f_echo(args[i], token_parts[i]);
            }
            else if(!strcmp(args[i][1], "pwd"))
            {
                f_pwd();
            }
            else if(!strcmp(args[i][1], "ls"))
            {
                f_ls(args[i], contents, path_contents);
            }
            else if(!strcmp(args[i][1], "pinfo"))
            {
                if(token_parts[i] == 2)
                    f_pinfo(atoi(args[i][2]), 1);
                else
                    f_pinfo(-1, 1);
            }
            else if(!strcmp(args[i][1], "setenv"))
            {
                f_setenv(args[i]);
            }
            else if(!strcmp(args[i][1], "unsetenv"))
            {
                f_unsetenv(args[i]);
            }
            else if(!strcmp(args[i][1], "exit"))
            {
                return 0;
            }
            else
            {
                int j = strlen(args[i][0]);
                if(args[i][0][j-1] == '&')
                {
                    args[i][0][j-1] = '\0';
                    f_bground(args[i]);
                }
                else
                {
                    f_fground(args[i], token_parts[i]);
                }
            }
        }
        if(print_dest != stdout)
            fclose(print_dest);
    }
}