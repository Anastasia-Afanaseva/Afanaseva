#ifndef PERSON_H
#define PERSON_H

typedef struct person
{
    char firstname[20];
    char lastname[20];
} person_t;

int check_person(person_t *person);
int add_person(person_t *person);
void show_person(person_t *person);

#endif