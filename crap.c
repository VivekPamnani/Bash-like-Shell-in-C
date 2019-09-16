#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
int main()
{
    char *input = malloc(100);
    char prompt[100] = "Enter pls";
    while(1)
    {
        input = readline(prompt);
        add_history(input);
        printf("%s\n", input);
    }
}
