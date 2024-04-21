#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void func (void)
{
    printf("\nУспешное завершение работы программы\n");
}

int main(int argc, char *argv[])
{
    atexit(func);
    pid_t pid;
    int rv;

    switch(pid = fork()) 
    {
        case -1:
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            printf("argc = %d\n", argc);

            for (int i = 0; i < argc; i++)
            {
                printf("%d argv = %s\n", i, argv[i]);
            }

            exit(EXIT_SUCCESS);
        }
        default:
        {
            printf("argc = %d\n", argc);

            for (int i = 0; i < argc; i++)
            {
                printf("%d argv = %s\n", i, argv[i]);
            }

            wait(&rv);
        }
    }
}