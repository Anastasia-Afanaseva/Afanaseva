#ifndef BTREE_H_
#define BTREE_H_
#include "info_all.h"

typedef struct btree
{
    info_all_t info_all;
    struct btree *left;
    struct btree *right;
}btree_t;

void add_struct(void);
void del(void);
void change(void);
void show(void);
void insert_btree(info_all_t *item, btree_t **root);
void Print_Btree_person(btree_t *root);
int Delete(char *fname, char *lname, btree_t **node);
int edit(char *fname, char *lname, btree_t **node);
void Print_Btree(btree_t *q);

#endif