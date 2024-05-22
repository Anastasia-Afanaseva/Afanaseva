#ifndef FUNK_H_
#define FUNK_H_

struct Item 
{
    int value;
    struct Item* next;
};

struct Item* Insert(int num);
struct Item* deleteFromStart(struct Item* head);
struct Item* deleteValue(int value, struct Item* head);
struct Item* extraction(int prior);
struct Item* deleteList(struct Item* head);
void printList(struct Item* h);

#endif