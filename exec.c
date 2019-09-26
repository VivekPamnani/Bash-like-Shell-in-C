#include "my_shell.h"

void f_fground(char **fground, int parts)
{
    pid_t pid = fork();
    int exe = 0;
    if(!pid)
    {
        fground[parts+1] = NULL;
        exe = execvp(fground[1], &fground[1]);
        if(exe < 0)
        {
            printf("Error: '%s' is an invalid command.\n", fground[1]);
            return;
        }
    }
    else
    {
        wait(NULL);
        return;
    }
}

pid_t children[100];
char children_name[100][4096];
int children_index = 0;
char name[4096];

void f_bghandler(int sig)
{
    //sig is the receiver signal
    if(sig == SIGCHLD)
    {
        int status;
        int ch_pid =  waitpid(-1, &status, WNOHANG);
        // printf("waitpid %d %d\n", waitpid(-1, &status, WNOHANG), children_index);
        for(int k = 0; k < children_index; k++)
        {
            // printf("%d\n", children[k]);
            if(ch_pid == children[k])
            {
                if(WIFEXITED(status) == 1)
                {
                    printf("'%s' with pid %d exited with exit code %d.\n", name, ch_pid, WEXITSTATUS(status));
                    // kill(getpid(), SIGKILL);
                    children[k] = -children[k];
                }
            }
        }
        f_prompt(inp_buffer, home, 0);
        // while ((getchar()) != '\n');
        fflush(stdout);
        return;
    }
}
char *f_bground(char **bground)
{
    int k;
    // for(k = 0; strcmp(bground[k], "&"); k++);
    pid_t pid = fork();
    strcpy(name, bground[1]);
    children[children_index] = pid;
    strcpy(children_name[children_index], name);
    // printf("child pid: %d\n", pid);
    // printf(" %d %s|\n", children_index, children_name[children_index]);
    children_index++;
    int exe = 0;
    if(!pid)
    {
        bground[k] = NULL;
        exe = execvp(bground[1], &bground[1]);
        if(exe < 0)
        {
            children_index--;
            printf("Error: '%s' is an invalid command.\n", bground[1]);
            return bground[1];
        }
    }
    else
    {
        // printf("parent process id: %d", pid);
        
    }
    signal(SIGCHLD, f_bghandler);
}
