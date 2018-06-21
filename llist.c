#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct list {
    int id;
    struct list *next;
};

struct list *list_create(int id)
{
    struct list *new = malloc(sizeof(struct list));
    new->id = id;
    new->next = NULL;
    return new;
}

void list_append(struct list *list, struct list *new)
{ 
    if (list->next == NULL) 
        list->next = new;
    else 
        list_append(list->next, new);
}

void list_free(struct list *list)
{
    if (list)
    {
        list_free(list->next);
        free(list);
    }
        
}

void list_print(struct list *list)
{
    if (list) 
    {
        printf("%d\n", list->id);
        list_print(list->next);
    }
}

int main(int argc, char **argv)
{
    struct list *list;
    struct list *list_elem;
    for (int i = 0; i < 10; i++)
    {
        list_elem = list_create(i);
        if (!list)
            list = list_elem;
        else
            list_append(list, list_elem);
    }
    list_print(list);
    list_free(list);
    return 0;
}
