#include <stdio.h>
#include <string.h>
#include "person.h"

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

int compare_person(person_t *person, person_t *person_1)
{
    if (((strncmp(person->firstname, person_1->firstname, 20)) == 0) &&
    ((strncmp(person->lastname, person_1->lastname, 20)) == 0))
        return -1;
    if (((strncmp(person->firstname, person_1->firstname, 20)) < 0) ||
        (((strncmp(person->firstname, person_1->firstname, 20)) == 0) &&
        (((strncmp(person->lastname, person_1->lastname, 20)) < 0))))
        return 1;
    return 0;
}

void show_person(person_t *person)
{
    printf("%s", person->firstname);
    printf(" %s", person->lastname);
}

