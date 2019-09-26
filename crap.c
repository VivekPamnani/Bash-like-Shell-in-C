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

int main() 
{
    while(1)
    {
        int cp = open("kass.txt", O_RDWR | O_CREAT | O_TRUNC);
        dup2(cp, 1);
        printf("Hello\n");
        close(cp);
        printf("World\n");
        getchar();
    }
} 
