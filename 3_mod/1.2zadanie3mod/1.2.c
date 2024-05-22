#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void func(void)
{
    printf("\nУспешное завершение работы программы\n");
}

int main(int argc, char *argv[])
{
    atexit(func);
    int num, rv;
    pid_t pid;

    if (argc == 1)
    {
        printf("\nНет аргументов для вычисления площади");
        exit(EXIT_FAILURE);
    }

    switch(pid = fork()) 
    {
        case -1:
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if (argc > 2)
            {
                for (int i = 1; i < argc; i++)
                {
                    num = atoi(argv[i]);
                    if ((i % 2 == 0) && (num > 0))
                    {
                        printf("Сторона квадрата = %d\n", num);
                        printf("Площадь квадрата = %d\n", num * num);
                    }
                }
            }

            exit(EXIT_SUCCESS);
        }
        default:
        {
            for (int i = 1; i < argc; i++)
            {
                num = atoi(argv[i]);
                if ((i % 2 == 1) && (num > 0))
                {
                    printf("Сторона квадрата = %d\n", num);
                    printf("Площадь квадрата = %d\n", num * num);
                }
            }
            
            wait(&rv);
        }
    }
}