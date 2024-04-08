#ifndef SOCIETY_H
#define SOCIETY_H

typedef struct society
{
    char telegram[128];
    char vk[128];
    char whatsapp[128];
    char facebook[128];
} society_t;

void add_society(society_t *society);
void show_society(society_t *society);

#endif