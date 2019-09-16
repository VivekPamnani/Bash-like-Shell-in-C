#include "my_shell.h"

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
