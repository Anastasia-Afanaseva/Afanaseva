#include "bitmap.h"
#include "plugin.h"
#include "stress_test.h"
#include "unit_test.h"

#define BYTE_IN_MB 1024 * 1024

void print_bitmap(bitmap_t* bitmap)
{
    for(int i = 0; i < bitmap->size; i++)
    {
        printf("%hhu", bitmap_get_bit(bitmap, i));
    }

    printf("\n");
}

void compare_return(bitmap_t* bitmap1, bitmap_t* bitmap2)
{
    int ret = bitmap_compare(bitmap1, bitmap2);

    switch(ret)
    {
        case -2:
        {
            printf("Битмапа 2 больше по количеству байтов\n");
            break;
        }

        case 2:
        {
            printf("Битмапа 1 больше по количеству байтов\n");
            break;
        }

        case 0:
        {
            printf("Битмапы равны\n");
            break;
        }

        case 1:
        {
            printf("Битмапы равны по количеству байтов, но битмапа 1 больше по значению\n");
            break;
        }

        case -1:
        {
            printf("Битмапы равны по количеству байтов, но битмапа 2 больше по значению\n");
            break;
        }

        default:
        {
            break;
        }
    }
}

int init_one_bitmap(bitmap_t** bitmap)
{
    char str_bit[1024] = { 0 };
    printf("Введите битмапу: ");
    scanf("%s", str_bit);

    if((*bitmap = bitmap_init(str_bit)) == NULL)
    {
        return -1;
    }

    log_debug("Enter");
    return 0;
}

void bit_operations(bitmap_t** bitmap, bitmap_t** bitmap1, bitmap_t** bitmap2)
{
    uint8_t opt;
    printf("\t\nВыберите битовую операцию:\n"
            "\t1 - OR\n"
            "\t2 - AND\n"
            "\t3 - NOT\n"
            "\t4 - XOR\n");

    scanf("%hhu", &opt);

    switch(opt)
    {
        case 1:
        {
            if((init_one_bitmap(bitmap1) == -1) || (init_one_bitmap(bitmap2) == -1))
            {
                printf("Произошла ошибка\n");
                break;
            }

            printf("%-17s", "OR:");
            *bitmap = bitmap_or(*bitmap1, *bitmap2);
            print_bitmap(*bitmap);
            bitmap_remove(*bitmap1);
            bitmap_remove(*bitmap2);
            bitmap_remove(*bitmap);
            break;
        }

        case 2:
        {
            if((init_one_bitmap(bitmap1) == -1) || (init_one_bitmap(bitmap2) == -1))
            {
                printf("Произошла ошибка\n");
                break;
            }

            printf("%-17s", "AND:");
            *bitmap = bitmap_and(*bitmap1, *bitmap2);
            print_bitmap(*bitmap);
            bitmap_remove(*bitmap1);
            bitmap_remove(*bitmap2);
            bitmap_remove(*bitmap);
            break;
        }

        case 3:
        {
            if(init_one_bitmap(bitmap1) == -1)
            {
                printf("Произошла ошибка\n");
                break;
            }

            printf("%-17s", "NOT:");
            bitmap_not(*bitmap1);
            print_bitmap(*bitmap1);
            bitmap_remove(*bitmap1);
            break;
        }

        case 4:
        {
            if((init_one_bitmap(bitmap1) == -1) || (init_one_bitmap(bitmap2) == -1))
            {
                printf("Произошла ошибка\n");
                break;
            }

            printf("%-17s", "XOR:");
            *bitmap = bitmap_xor(*bitmap1, *bitmap2);
            print_bitmap(*bitmap);
            bitmap_remove(*bitmap1);
            bitmap_remove(*bitmap2);
            bitmap_remove(*bitmap);
            break;
        }

        default:
        {
            printf("\tВведена некорректная функция\n");
            break;
        }
    }
}


int main(void)
{
    uint8_t opt, bit;
    size_t index;
    bitmap_t* bitmap2 = NULL;
    bitmap_t* bitmap1 = NULL;
    bitmap_t* bitmap = NULL;

    while(1)
    {
        printf("\n\t\tВыберите функцию:"
           "\n\t1. Сравнение двух битмап"
           "\n\t2. Копирование одного битмапа в другой"
           "\n\t3. Клонирование битмапы"
           "\n\t4. Сброс битмапы"
           "\n\t5. Получение значения битмапы по индексу"
           "\n\t6. Установка значения битмапы по индексу"
           "\n\t7. Склеивание битмап"
           "\n\t8. Битовые операции"
           "\n\t9. Плагины"
           "\n\t10. Тестирования"
           "\n\t11. Выход\n");

        scanf("%hhu", &opt);

        switch(opt)
        {
            case 1:
            {
                if((init_one_bitmap(&bitmap1) == -1) || (init_one_bitmap(&bitmap2) == -1))
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                compare_return(bitmap1, bitmap2);
                bitmap_remove(bitmap1);
                bitmap_remove(bitmap2);
                break;
            }

            case 2:
            {
                if((init_one_bitmap(&bitmap1) == -1) || (init_one_bitmap(&bitmap2) == -1))
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("\nКопирование: ");
                bitmap_copy(bitmap1, bitmap2);
                printf("\nБитмап 1: ");
                print_bitmap(bitmap1);
                printf("Битмап 2: ");
                print_bitmap(bitmap2);
                bitmap_remove(bitmap1);
                bitmap_remove(bitmap2);
                break;
            }

            case 3:
            {
                if(init_one_bitmap(&bitmap1) == -1)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("Клонирование:    ");
                bitmap = bitmap_clone(bitmap1);
                print_bitmap(bitmap);
                bitmap_remove(bitmap1);
                bitmap_remove(bitmap);
                break;
            }

            case 4:
            {
                if(init_one_bitmap(&bitmap1) == -1)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                bitmap_reset(bitmap1);
                printf("Сброс битмапы:   ");
                print_bitmap(bitmap1);
                bitmap_remove(bitmap1);
                break;
            }

            case 5:
            {
                if(init_one_bitmap(&bitmap1) == -1)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("Введите индекс:");
                scanf("%lu", &index);

                if(bitmap_get_bit(bitmap1, index) == 2)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                else
                {
                    printf("Бит = %hhu", bitmap_get_bit(bitmap1, index));
                }

                bitmap_remove(bitmap1);
                break;
            }

            case 6:
            {
                if(init_one_bitmap(&bitmap1) == -1)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("Введите индекс: ");
                scanf("%lu", &index);
                printf("Введите значение бита: ");
                scanf("%hhu", &bit);

                if(bitmap_set_bit(bitmap1, index, bit) != 0)
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                else
                {
                    printf("\nБит установлен:  ");
                    print_bitmap(bitmap1);
                }

                bitmap_remove(bitmap1);
                break;
            }

            case 7:
            {
                if((init_one_bitmap(&bitmap1) == -1) || (init_one_bitmap(&bitmap2) == -1))
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("Склеивание:      ");
                bitmap = bitmap_concat(bitmap1, bitmap2);
                print_bitmap(bitmap);
                bitmap_remove(bitmap1);
                bitmap_remove(bitmap);
                bitmap_remove(bitmap2);
                break;
            }

            case 8:
            {
                bit_operations(&bitmap, &bitmap1, &bitmap2);
                break;
            }

            case 9:
            {
                init_plugin("../../plugin/build/");
                const char **name = connected_plugins();
                printf("\n\tСписок функций плагинов: ");

                for(int i = 0; i < plug_plugins_cnt_get(); i++)
                {
                    printf("\n\t%d.%s", i + 1, name[i]);
                }

                printf("\nВведите номер функции: ");
                scanf("%hhu", &bit);

                if((plug_plugins_cnt_get() <= (bit - 1)) || (bit <= 0))
                {
                    printf("Нет плагина с таким номером\n");
                    break;
                }

                if((init_one_bitmap(&bitmap1) == -1) || (init_one_bitmap(&bitmap2) == -1))
                {
                    printf("Произошла ошибка\n");
                    break;
                }

                printf("\n%s: ", name[bit - 1]);
                bitmap = call_plugin(bitmap1, bitmap2, name[bit - 1]);
                print_bitmap(bitmap);
                deinit_plugin();
                bitmap_remove(bitmap1);
                bitmap_remove(bitmap);
                bitmap_remove(bitmap2);
                break;
            }

            case 10:
            {
                printf("\n\tДоступные функции тестирований:"
                       "\n\t1. Стресс-тесты"
                       "\n\t2. Unit-тесты"
                       "\n\t3. Очистить логи");
                printf("\nВведите номер из списка: ");
                scanf("%hhu", &bit);

                switch(bit)
                {
                    case 1:
                    {
                        printf("\nВведите размер битмапы в Мб: ");
                        scanf("%lu", &index);
                        stress_test_global(NULL, NULL, index * BYTE_IN_MB);
                        break;
                    }

                    case 2:
                    {
                        unit_test_global();
                        break;
                    }

                    case 3:
                    {
                        stress_clear_logs();
                        unit_clear_logs();
                        break;
                    }
                    
                    default:
                    {
                        printf("Нет варианта с таким номером");
                        break;
                    }
                }

                break;
            }

            case 11:
            {
                exit(0);
            }

            default:
            {
                printf("\tВведена некорректная функция\n");
                break;
            }
        }
    }
}
