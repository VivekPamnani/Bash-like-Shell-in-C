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
        waitpid(-1, &status, WNOHANG);
        for(int k = 0; k < children_index; k++)
        {
            if(WIFEXITED(status) == 1)
            {
                printf("'%s' with pid %d exited with exit code %d.\n", name, getpid(), WEXITSTATUS(status));
                // kill(getpid(), SIGKILL);
                children[children_index] = -2;
            }
        }
        fflush(stdout);
        return;
    }
}
char *f_bground(char **bground)
{
    int k;
    for(k = 0; strcmp(bground[k], "&"); k++);
    pid_t pid = fork();
    int exe = 0;
    if(!pid)
    {
        bground[k] = NULL;
        // printf("child pid: %d\n", getpid());
        exe = execvp(bground[1], &bground[1]);
        if(exe < 0)
        {
            printf("Error: '%s' is an invalid command.\n", bground[1]);
            return bground[1];
        }
    }
    else
    {
        // printf("parent process id: %d", pid);
        strcpy(name, bground[1]);
        children[children_index] = getpid();
        strcpy(children_name[children_index], name);
        children_index++;
        return bground[1];
    }
}
