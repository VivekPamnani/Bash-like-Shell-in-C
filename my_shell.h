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

int get_arg(char **arg, char *delim, char *in);
int tokenize(char **inp, char *delim, char ***args, int *token_parts);

void f_cd(char **cd, char *home);
void f_echo(char **echo);
void f_pwd();

void f_ls(char **ls, char **contents, char **path_contents);

char *f_pinfo(int r_pid, int show);

void f_fground(char **fground, int parts);
void f_bghandler(int sig);
char *f_bground(char **bground);
