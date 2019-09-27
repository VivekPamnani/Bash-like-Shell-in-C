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
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

char *home, *inp_buffer;
FILE *print_dest;
FILE *scan_src;  

char * f_prompt(char *inp_buffer, char *home_dir, int show_input);

int get_arg(char **arg, char *delim, char *in);
int tokenize(char **inp, char *delim, char ***args, int *token_parts);
int get_src(char **in, int lim);
int get_dest(char **in, int lim);
int get_dest_append(char **in, int lim);
int get_pipe(char **cmd, int lim, int begin);
int set_streams(char **cmd, int *num_tok);

void f_cd(char **cd, char *home);
void f_echo(char **echo, int num_tokens);
void f_pwd();
void f_ls(char **ls, char **contents, char **path_contents, int num_tokens);
char *f_pinfo(int r_pid, int show);

void f_fground(char **fground, int parts);
void f_bghandler(int sig);
char *f_bground(char **bground);

void f_setenv(char **env);
void f_unsetenv(char **env);
