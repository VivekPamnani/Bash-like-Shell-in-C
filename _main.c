#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/stat.h>

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

void f_cd(char **cd, char *home)
{
    if(cd[2][0] == '~')
    {
        chdir(home);
        chdir(&cd[2][2]);
    }
    else
    {
        chdir(cd[2]);
    }
}

void f_echo(char **echo)
{
    for(int i = 2; strcmp(echo[i], ""); i++)
    {
        printf("%s ", echo[i]);
    }
    printf("\n");
}

void f_pwd()
{
    char dir[4096];
    getcwd(dir, sizeof(dir));
    printf("%s\n", dir);
}

void f_ls(char **ls, char **contents, char **path_contents)
{
    // char **contents = malloc(1000);
    // char **path_contents = malloc(1000);
    struct dirent *dir;
    struct passwd *user_id;
    struct group *grp_id;
    DIR *folder;
    char mtime[4096];
    struct stat files[100];
    int hidden = 0; int long_list = 0;
    int param = 0; //whether -l/a/la/al is specified
    int num_contents = 0; //number of contents
    if(ls[2][0] == '-')
    {
        param++;
        for(int i = 1; (i < 3) & (ls[2][i] != '\0'); i++)
        {
            if(ls[2][i] == 'a') hidden = 1;
            if(ls[2][i] == 'l') long_list = 1;
        }
    }
    if(ls[3][0] == '-')
    {
        param++;
        for(int i = 1; (i < 3) & (ls[3][i] != '\0'); i++)
        {
            if(ls[3][i] == 'a') hidden = 1;
            if(ls[3][i] == 'l') long_list = 1;
        }
    }

    int arg_no = 2 + param; //index from which directories begin
    if(!strcmp(ls[arg_no], ""))
    {
        ls[arg_no][0] = '.';
        ls[arg_no][1] = '\0';
    }
    for (int i = arg_no; strcmp(ls[i], ""); i++)
    {
        folder = opendir(ls[i]);
        if(folder == NULL) 
        {
             printf("Error: The directory '%s' doesn not exist.\n", ls[i]);
             continue;
        }
        for(int j = 0; (dir = readdir(folder)) != NULL; j++, num_contents++)
        {
            contents[j] = dir->d_name;
            strcpy(path_contents[j], ls[i]); strcat(path_contents[j], "/");
            strcat(path_contents[j], contents[j]);
        }
        int skip = 0;
        long long int block_size = 0;
        /**
        for (int j = 0; j < num_contents; j++)
        {
            // if(!S_ISDIR(files[i].st_mode))
                block_size += files[i].st_blksize;
        }
        printf("total %lld\n", block_size);
        */
        for (int j = 0; j < num_contents; j++)
        {
            stat(path_contents[j], &files[i]);
            if(hidden == 0)
            {
                if(contents[j][0] == '.')
                {
                    // printf("%s\n", contents[j]);
                    // skip = 1;
                    continue;
                }
            }
            //printf("%s\n", path_contents[j]); //prints perfectly
            if(long_list)
            {
                //Important: Non-existent directory error handled above, so no need here.
                printf( (S_ISDIR(files[i].st_mode)) ? "d" : "-");
                printf( (files[i].st_mode & S_IRUSR) ? "r" : "-");
                printf( (files[i].st_mode & S_IWUSR) ? "w" : "-");
                printf( (files[i].st_mode & S_IXUSR) ? "x" : "-");
                printf( (files[i].st_mode & S_IRGRP) ? "r" : "-");
                printf( (files[i].st_mode & S_IWGRP) ? "w" : "-");
                printf( (files[i].st_mode & S_IXGRP) ? "x" : "-");
                printf( (files[i].st_mode & S_IROTH) ? "r" : "-");
                printf( (files[i].st_mode & S_IWOTH) ? "w" : "-");
                printf( (files[i].st_mode & S_IXOTH) ? "x" : "-");
                printf("\t%ld", files[i].st_nlink);

                user_id = getpwuid(files[i].st_uid);
                printf("\t%s", user_id->pw_name);
                
                grp_id = getgrgid(files[i].st_gid);
                printf("\t%s", grp_id->gr_name);
                printf("\t%ld", files[i].st_size);
                time_t raw_time = files[i].st_mtime;
                struct tm local_time;
                localtime_r(&raw_time, &local_time);
                strftime(mtime, sizeof(mtime), "%b %d", &local_time);
                printf("\t%s", mtime);
                strftime(mtime, sizeof(mtime), "%H:%M", &local_time);
                printf("\t%s", mtime);
                printf("\t%s\n", contents[j]);
            }
            else
            {
                printf("%s\n", contents[j]);
            }
        }
        
    }
}

char *f_pinfo(int r_pid, int show)
{
    char stat_file[4096];
    char path_file[4096];
    char buffer[4096];
    FILE* status;
    struct stat file;
    char temp[4096];
    char stat[3];
    char size[4096];
    char *path = malloc(4096*sizeof(char*));
    int sz = 0;
    pid_t s_pid = getpid();
    pid_t pid = (r_pid > 0) ? r_pid : s_pid;
    if(show)    printf("pid -- %d\n", pid);
    sprintf(stat_file, "/proc/%d/status", pid);
    status = fopen(stat_file, "r");
    for(int i = 0; fgets(buffer, sizeof(buffer), status); i++)
    {
        // printf("buff %d %s\n", i, buffer);
        strcpy(temp, buffer);
        temp[5] = '\0';
        if(!strcmp(temp, "State"))
        {
            stat[0] = buffer[6];
            stat[1] = buffer[7];
            stat[2] = '\0';
        }
        strcpy(temp, buffer);
        temp[6] = '\0';
        if(!strcmp(temp, "VmSize"))
        {
            for(int k = 8; buffer[k] != ' '; k++)
            {
                size[k-8] = buffer[k];
            }
            sz = atoi(size);
        }
    }
    fclose(status);
    if(show)    printf("Process Status -- %s\n", stat);
    if(show)    printf("memory -- %d\n", sz);
    sprintf(path_file, "/proc/%d/exe", pid);
    readlink(path_file, path, 4096);
    if(show)    printf("Executable Path -- %s\n", path);
    return path;
}

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

int main()
{
    //printf("%s", home_dir);
    char *username = getenv("USER");
    char curr_dir[4096];
    char *home_dir = malloc(4096); getcwd(home_dir, 4096);
    home_dir = f_pinfo(-1, 0);
    for(int k = strlen(home_dir); k > 0; k--)
    {
        if(home_dir[k] == '/')
        {
            home_dir[k] = '\0';
            break;
        }
    }
    //printf("%s\n", home_dir);
    struct utsname sysinfo;
    uname(&sysinfo);
    //inp will store ';' separated commands
    char **inp = malloc(100);                                               //reminder: change length
    //inp_cmd will store the corresponding commands to inp
    char **inp_cmd = malloc(100);                                           //reminder: change length
    //args will store the corresponding arguments to inp
    char ***args = malloc(sizeof(char**));
    *args = malloc(100);
    //used as saveptr for strtok_r
    int token_parts[100] = {0};
    char **buff_ptr = malloc(100);
    //LOL is input buffer for stdin, change the name.
    char *LOL = malloc(4096);
    char **contents = malloc(1000);
    char **path_contents = malloc(1000);
    int alloted  = 0;
    for(int i = 0; i < 1000; i++) //change this is contents size changed
    {
        contents[i] = malloc(4096);
        path_contents[i] = malloc(4096);
        alloted = 1;
    }
   for(int i = 0; i < 100; i++)                                             //allocating memory
    {
        (*args)[i] = malloc(100);
        inp[i] = malloc(4096);
    }
    while(1)
    {
        signal(SIGCHLD, f_bghandler);
        getcwd(curr_dir, sizeof(curr_dir));
        // printf("c_dir %s\nh_dir %s\n", curr_dir, home_dir);
        char *loc = NULL;
        int offset = strlen(home_dir);
        loc = strstr(curr_dir, home_dir);
        if(loc == NULL)
            printf("<%s@%s:%s>", username, sysinfo.nodename, curr_dir);
        else
            printf("<%s@%s:~%s>", username, sysinfo.nodename, loc+offset);
        fgets(LOL, 4096, stdin);
        inp[0] = LOL;
        strtok_r(inp[0], "\n", buff_ptr);
        inp[1] = inp[0];
        int tokens = tokenize(inp, ";", args, token_parts);
        // printf("Tokens: %d\n", tokens);
        for(int i = 1; i <= tokens; i++)
        {
            // printf("%d\n", token_parts[i]);
            if (!strcmp(args[i][1], "\n"))
            {
                continue;
            }
            
            else if(!strcmp(args[i][1], "cd"))
            {
                f_cd(args[i], home_dir);
            }
            // else if(!strcmp(args[i][1], "echo"))
            // {
            //     f_echo(args[i]);
            // }
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
            else if(!strcmp(args[i][1], "exit"))
            {
                return 0;
            }
            else
            {
                int j = strlen(args[i][0]);
                if(args[i][0][j-1] == '&')
                {
                    f_bground(args[i]);
                }
                else
                {
                    f_fground(args[i], token_parts[i]);
                }
                
            }
        }
    }
}