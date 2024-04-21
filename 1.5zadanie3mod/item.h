#ifndef ITEM_H
#define ITEM_H
#include "info_all.h"

typedef struct Item 
{
    info_all_t info_all;
    struct Item* next;
    struct Item* prev;
} item_t;

struct Item* reading_(struct Item* head, int fd);
struct Item* writing(struct Item* head, int fd);
struct Item* add_head(struct Item* head, struct Item* tmp);
struct Item* add(struct Item* head);
struct Item* del(struct Item* head);
struct Item* change(struct Item* head);
void show(struct Item* head);

#endif