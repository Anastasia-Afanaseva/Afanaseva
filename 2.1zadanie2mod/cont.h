#ifndef CONT_H
#define CONT_H

typedef struct cont
{
    char phone[5][30];
    char mail[5][30];
} cont_t;

void add_cont(cont_t *cont);
void show_cont(cont_t *cont);

#endif