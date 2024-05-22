#include <stdio.h>
#include <string.h>
#include "work.h"

void add_work(work_t *work)
{
    printf("\tВведите место работы:\n");
    fgets(work->place, 30, stdin);
    if ((strlen(work->place) != 0) && (work->place[0] != '\n'))
    {
        printf("\tВведите должность:\n");
        fgets(work->title, 30, stdin);
    }
    return;
}
void show_work(work_t *work)
{
    if ((strlen(work->place) != 0) && (work->place[0] != '\n'))
    {
            int size = strlen(work->place) - 1;
            if (work->place[size] == '\n')
                work->place[size] = 0;
            printf("\t%s", work->place);
    }

    if ((strlen(work->title) != 0) && (work->title[0] != '\n'))
    {
            int size = strlen(work->title) - 1;
            if (work->title[size] == '\n')
                work->title[size] = 0;
            printf("\t%s", work->title);
    }
}