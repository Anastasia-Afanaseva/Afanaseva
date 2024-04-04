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

#endif