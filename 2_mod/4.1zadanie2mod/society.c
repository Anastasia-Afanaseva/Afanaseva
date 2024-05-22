#include <stdio.h>
#include <string.h>
#include "society.h"

void add_society(society_t *society)
{
    printf("\tВведите ссылку на телеграм:\n");
    fgets(society->telegram, 128, stdin);

    printf("\tВведите ссылку ВКонтакте:\n");
    fgets(society->vk, 128, stdin);

    printf("\tВведите ссылку WhatsApp:\n");
    fgets(society->whatsapp, 128, stdin);

    printf("\tВведите ссылку на facebook:\n");
    fgets(society->facebook, 128, stdin);
    return;
}
void show_society(society_t *society)
{
    if ((strlen(society->telegram) != 0) && (society->telegram[0] != '\n'))
    {
        int size = strlen(society->telegram) - 1;
        if (society->telegram[size] == '\n')
            society->telegram[size] = 0;
        printf("\t%s", society->telegram);
    }

    if ((strlen(society->vk) != 0) && (society->vk[0] != '\n'))
    {
        int size = strlen(society->vk) - 1;
        if (society->vk[size] == '\n')
            society->vk[size] = 0;
        printf("\t%s", society->vk);
    }

    if ((strlen(society->whatsapp) != 0) && (society->whatsapp[0] != '\n'))
    {
        int size = strlen(society->whatsapp) - 1;
        if (society->whatsapp[size] == '\n')
            society->whatsapp[size] = 0;
        printf("\t%s", society->whatsapp);
    }
            
    if ((strlen(society->facebook) != 0) && (society->facebook[0] != '\n'))
    {
        int size = strlen(society->facebook) - 1;
        if (society->facebook[size] == '\n')
            society->facebook[size] = 0;
        printf("\t%s", society->facebook);
        }
}