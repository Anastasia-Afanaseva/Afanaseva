#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_1.h"
#include "func_2.h"
#include "func_3.h"

int main()
{
    int opt, opt_1, opt_2;
    char string[20] = {};
    char letter[10] = {};
    char number[10] = {};
    char file[30] = {};
    char str[10] = {};
    while (1)
    {
        printf("\n\tВыберите необходимую функцию:"
        "\n\t1 - Вывод битового представления маски прав доступа"
        "\n\t2 - Вывод буквенного, цифрового и битового представлдения прав доступа введенного файла"
        "\n\t3 - Изменение прав доступа к файлу"
        "\n\t4 - Выход\n");
        scanf("\t%d", &opt);
        switch(opt)
        {
            case 1:
            {
                printf("\n\tВведите маску прав доступа:");
                getchar();
                fgets(string, 20, stdin);
                if (check_number_or_letters(string) == 0) 
                {
                    printf("\n\tВведено неверное значение маски прав доступа\n");
                    break;
                }
                else  if (check_number_or_letters(string) == 1)
                {
                    transform_number(string, letter);
                }
                else
                    transform_letters(string, letter);
                break;
            }
            case 2:
            {
                printf("\n\tВведите название файла:");
                getchar();
                fgets(file, 30, stdin);
                stat_func(file, number);
                break;
            }  
            case 3:
            {
                printf("\n\tВведите номер маски, которую хотите изменить:");
                printf("\n\t1 - %s", letter);
                printf("\n\t2 - %s\n", number);
                scanf("\t%d", &opt_2);
                if (((strlen(letter) ==  0) && (opt_2 == 1)) || ((strlen(number) ==  0) && (opt_2 == 2)))
                {
                    printf("\n\tВыбран номер пустой маски, сначала выполните пункт %d", opt_2);
                    break;
                }
                printf("\n\tВведите команды модификации атрибутов для изменения прав доступа:");
                getchar();
                fgets(str, 10, stdin);
                if (check_change(str) == 0)
                {
                    printf("\n\tНекорректно введена команда модификации атрибутов");
                    break;
                }
                if (opt_2 == 1)
                {
                    edit(str, letter);
                    printf("\n\t%s", str);
                    printf("\n\tБитовое представление прав доступа: %s", letter);
                    printf("\n\tЦифровое представление прав доступа: %d", binary_to_number(letter));
                    binary_to_letters(letter);
                    break;
                }
                if (opt_2 == 2)
                {
                    edit(str, number);
                    printf("\n\t%s", str);
                    printf("\n\tБитовое представление прав доступа: %s", number);
                    printf("\n\tЦифровое представление прав доступа: %d", binary_to_number(number));
                    binary_to_letters(number);
                    break;
                }
                printf("\n\tВведено некорректное значение номера маски");
                break;
            }
            case 4:
            {
                exit(0);
            }
            default:
            {
                printf("\n\tВведена некорректная функция");
                break;
            }
        }
    }
}
