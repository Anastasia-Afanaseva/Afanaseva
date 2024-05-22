#include <stdio.h>
#include <stdlib.h>
#include "funk.h"

struct Item* head = NULL;
struct Item* head_end = NULL;

int main() 
{
    for (int i = 0; i < 10; i++)
    {
        head = Insert(1 + rand()%255);
    }
    head = Insert(100);
    
    printList(head); 
    head_end = extraction(-200);
    head_end = extraction(200);
    head_end = extraction(-200);
    head_end = extraction(100);
    head_end = extraction(-200);
    head_end = extraction(0);
    printList(head_end); 
    printList(head);
    
    return 0;
}