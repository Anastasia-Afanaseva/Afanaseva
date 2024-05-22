#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void func(void)
{
    printf("\nУспешное завершение работы программы");
}
int main()
{
    atexit(func);
    int i = 0, j = 0, m = 1, rv;
    char str[20] = {};
    char arg[20] = {};
    char c[1] = {""};
    char string[10][10] = {0};
    char *arg_str[10] = {NULL};
    arg_str[0] = &c[0];
    pid_t pid;
    
    switch(pid = fork())
    {
        case -1:
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            printf("\nВведите название программы\n");
            fgets(str, 20, stdin);
            str[strlen(str) - 1] = 0;

            printf("\nВведите аргументы программы\n");
            fgets(arg, 20, stdin);
            arg[strlen(arg) - 1] = ' ';

            for (int i = 0; i < strlen(arg); i++)
            {
                if ((arg[i] != ' '))
                {
                    string[m][j] = arg[i];
                    j++;
                }
                else
                {
                    arg_str[m] = string[m];
                    m++;
                    j = 0;
                }
            }

            arg_str[m] = NULL;

            if (execv(str, arg_str) != -1)
            {
                exit(EXIT_SUCCESS);
            }

            if (execvp(str, arg_str) != -1)
            {
                exit(EXIT_SUCCESS);
            }

            printf("\nНет введенной программы в каталоге");
            exit(EXIT_FAILURE);
        }
        default:
        {
            wait(&rv);
        }
    }
}
