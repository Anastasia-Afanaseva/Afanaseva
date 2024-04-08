#ifndef WORK_H
#define WORK_H

typedef struct work
{
    char place[30];
    char title[30];
} work_t;

void add_work(work_t *work);
void show_work(work_t *work);

#endif