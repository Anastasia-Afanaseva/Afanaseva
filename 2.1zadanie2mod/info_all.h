#ifndef INFO_ALL_H_H
#define INFO_ALL_H_H
#include "person.h"
#include "work.h"
#include "cont.h"
#include "society.h"

typedef struct info_all 
{
    person_t person;
    work_t work;
    cont_t cont;
    society_t society;
} info_all_t;

int check_place(info_all_t *info);
int add_person(info_all_t *info);
void add_work(info_all_t *info);
void add_cont(info_all_t *info);
void add_society(info_all_t *info);
void add(void);
void id_name_fam(info_all_t *info);
void del(info_all_t *info);
void change(info_all_t *info);
void show(info_all_t *info);

#endif