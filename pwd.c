#include "my_shell.h"

void f_pwd()
{
    char dir[4096];
    getcwd(dir, sizeof(dir));
    printf("%s\n", dir);
}
