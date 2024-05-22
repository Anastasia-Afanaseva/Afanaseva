#ifndef PERSON_H
#define PERSON_H

typedef struct person
{
    char firstname[20];
    char lastname[20];
} person_t;

int add_person(person_t *person);
int compare_person(person_t *person, person_t *person_1);
void show_person(person_t *person);

#endif