#ifndef FUNK_H
#define FUNK_H

typedef struct number
{
    int mas[20];
    int max_min[2];
    int size;
}num_t;

void print_num(num_t *data, int num_1, int num_2);
void min_max(num_t *data, int num_1, int num_2);
void func_end(void);
void handler(int val);

#endif