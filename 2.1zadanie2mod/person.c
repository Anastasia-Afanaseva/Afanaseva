#include <stdio.h>
#include <string.h>
#include "person.h"

int check_person(person_t *person)
{
    if (((strlen(person->firstname) == 0) || (strlen(person->lastname) == 0))
        && ((person->firstname[0] != '\n') || (person->lastname[0] != '\n')))
        return 1;
    return 0;
}

int add_person(person_t *person)
{
    printf("\tВведите имя:\n");
    getchar();
    if ((fgets(person->firstname, 20, stdin) == NULL)
       || (person->firstname[0] == '\n'))
    {
        printf("\tНеобходимо ввести имя\n");
        return -1;
    }

    printf("\tВведите фамилию:\n");
    if ((fgets(person->lastname, 20, stdin) == NULL)
    || (person->lastname[0] == '\n'))
    {
        printf("\tНеобходимо ввести фамилию\n");
        return -1;
    }

    int size = strlen(person->firstname) - 1;
    person->firstname[size] = 0;
    size = strlen(person->lastname) - 1;
    person->lastname[size] = 0;
    return 0;
}
void show_person(person_t *person)
{
    printf("\t%s", person->firstname);
    printf(" %s", person->lastname);
}

