#ifndef FUNK_H
#define FUNK_H


union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

void change_parent(int num, char *str);
void func(void);

#endif