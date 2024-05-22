#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "btree.h"

extern btree_t *root;

int compare_person(info_all_t *item, btree_t **root)
{
    if ((((strncmp(item->person.firstname, (*root)->info_all.person.firstname, 20)) == 0) &&
    (strncmp(item->person.lastname, (*root)->info_all.person.lastname, 20)) == 0))
    {
        return -1;
    }
    else if (((strncmp(item->person.firstname, (*root)->info_all.person.firstname, 20)) < 0) ||
        ((strncmp(item->person.firstname, (*root)->info_all.person.firstname, 20)) == 0) &&
        (((strncmp(item->person.lastname, (*root)->info_all.person.lastname, 20)) < 0)))
        return 1;
    else
        return 0;
}

//добавление пользователя в дерево
void insert_btree(info_all_t *item, btree_t **root) 
{
    if (*root == NULL) 
    {
        (*root) = malloc(sizeof(btree_t));
        if (*root == NULL)
        {
            printf("\nНе выделилась память для новой структуры");
            return;
        }
        (*root)->left = (*root)->right = NULL;
        (*root)->info_all = *item;
        return;
    }
    
    if (compare_person(item, root) == 1)
        insert_btree(item, &(*root)->left);
    else if (compare_person(item, root) == 0)
        insert_btree(item, &(*root)->right);
    else 
    {
        printf("\n\tТакой пользователь уже существует");
        return;
    }
}

void add_struct(void)
{
    info_all_t *item = malloc(sizeof(info_all_t));
    if (item == NULL)
    {
        printf("\nНе выделилась память для новой структуры");
        return;
    }
    if (add_person(&item->person) < 0)
    {
        printf("\tНе введены фамилия или имя\n");
        free(item);
        return;
    }
    add_work(&item->work);
    add_cont(&item->cont);
    add_society(&item->society);
    insert_btree(item, &root);
    return;
}

int compare_else(char *fname, char *lname, btree_t **node)
{
    if ((strncmp((*node)->info_all.person.firstname, fname, 20) == 0) &&
    (strncmp((*node)->info_all.person.lastname, lname, 20) == 0))
        return -1;
    else if (((strncmp((*node)->info_all.person.firstname, fname, 20)) < 0) ||
    ((strncmp((*node)->info_all.person.firstname, fname, 20)) == 0) &&
    (((strncmp((*node)->info_all.person.lastname, lname, 20)) < 0)))
        return 1;
    else 
        return 0;
}
// Удаление вершины с заданным значением key
int Delete(char *fname, char *lname, btree_t **node) 
{
    btree_t *t, *up;
    if(*node == NULL) 
        return 0; // нет такого значения в дереве
    
    if (compare_else(fname, lname, node) == -1)
    {
        // если значение находится в листе, то удаляем лист
        if(((*node)->left == NULL) && ((*node)->right == NULL)) 
        {
            free(*node);
            *node = NULL;
            return 1;
        }
        // если у вершины только правый потомок, то перебрасываем
        // связь на вершину ниже удаляемой в правом поддереве
        if((*node)->left == NULL) 
        {
            t = *node;
            *node =(*node)->right;
            free(t);
            return 1;
        }
        // если у вершины только левый потомок, то перебрасываем
        // связь на вершину ниже удаляемой в левом поддереве
        if((*node)->right == NULL) 
        {
            t = *node;
            *node =(*node)->left;
            free(t);
            return 1;
        }
        // если у вершины два потомка, то заменяем удаляемое значение
        // на значение самого правого элемента в левом поддереве
        up = *node;
        t = (*node)->left; // идем в левое поддерево
        //спускаемся до крайнего правого узла
        while (t->right != NULL) 
        {
            up = t;
            t = t-> right;
        }
        //копируем значение из правого узла вместо удаляемого значения
        (*node)->info_all = t->info_all;
        // если ниже удаляемого больше, чем одна вершина
        if (up != (*node)) 
        {
            // если крайний правый не лист, то «отбрасываем» его из дерева
            if(t->left != NULL) 
                up->right = t->left;
            else 
                up->right = NULL; // удаляем лист
        }
        // если ниже удаляемого одна вершина, удаляем лист
        else 
            (*node)->left = t->left;
        // освобождаем память – удаляем крайнюю
        // правую вершину
        free(t);
        return 1;
    }
        // поиск ключа в левом или правом поддереве
    if ((compare_else(fname, lname, node)) == 1)
        return Delete(fname, lname, &(*node)->right);
    else
        return Delete(fname, lname, &(*node)->left);
}

void del(void)
{
    char fname[20] = {};
    char lname[20] = {};
    
    if (root == NULL) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    printf("\tВыберите пользователя для удаления из списка:\n");
    Print_Btree_person(root);
    printf("\n\tВведите имя\n");
    scanf("\t%s", fname);
    printf("\n\tВведите фамилию\n");
    scanf("\t%s", lname);
    if (Delete(fname, lname, &root) == 0)
    {
        printf("\tНет такого пользователя в списке для удаления\n");
        return;
    }
}

int edit(char *fname, char *lname, btree_t **node)
{
    int opt;
    if(*node == NULL) 
        return 0; // нет такого значения в дереве
    if (compare_else(fname, lname, node) == -1)
    {
        printf("\tВыберите номер позиции для редактирования:\n"
                "\t1 - Место работы/должность\n"
                "\t2 - Номера телефонов/Почтовые адреса\n"
                "\t3 - Ссылки на социальные сети\n");
        scanf("\n%d", &opt);
        
        switch(opt)
        {
            case 1:
            {
                getchar();
                add_work(&(*node)->info_all.work);
                break;
            }
            case 2:
            {
                getchar();
                add_cont(&(*node)->info_all.cont);
                break;
            }
            case 3:
            {
                getchar();
                add_society(&(*node)->info_all.society);
                break;
            }
            default:
            {
                printf("\n\tНекорректно введена позиция для редактирования\n");
            }
        }
        return 1;
    }

    if ((compare_else(fname, lname, node)) == 1)
        return edit(fname, lname, &(*node)->right);
    else
        return edit(fname, lname, &(*node)->left);
}

void change(void)
{
    int opt_2;
    char fname[20] = {};
    char lname[20] = {};
    
    if (root == NULL) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    printf("\tВыберите пользователя для редактироавния из списка:\n");
    Print_Btree_person(root);
    printf("\n\tВведите имя\n");
    scanf("\t%s", fname);
    printf("\n\tВведите фамилию\n");
    scanf("\t%s", lname);
    if (edit(fname, lname, &root) == 0)
    {
        printf("\tНет такого пользователя в списке для удаления\n");
        return;
    }
}

//печать только фио
void Print_Btree_person(btree_t *root)
{
    if (root == NULL)
    {
        return;
    }
    Print_Btree_person(root->left);
    show_person(&root->info_all.person);
    printf("\n");
    Print_Btree_person(root->right);
    return;
}

void Print_Btree(btree_t *q) 
{
    if (q == NULL)
    {
        return;
    }
    Print_Btree(q->left);
    show_person(&q->info_all.person);
    show_work(&q->info_all.work);
    show_cont(&q->info_all.cont);
    show_society(&q->info_all.society);
    printf("\n");
    Print_Btree(q->right);
}

//печать контактов и всех их данных
void show()
{
    printf("\tИнформация обо всех пользователях:\n");
    if (root == NULL)
    {
        printf("\n\tНет ни одного пользователя в списке");
        return;
    }
    Print_Btree(root);
}