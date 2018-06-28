#include "linked-list.h"

/* doubly linked list */

struct list *list_create(void)
{
    struct list *first = calloc(1, sizeof(struct list));
    struct list *last = calloc(1, sizeof(struct list));
    first->next = last;
    last->prev = first;
    return first;
}

int list_size(struct list *list)
{
    int size = 0;
    struct list *cursor = list;
    while ((cursor = cursor->next)->data)
        size++;
    return size;
}

struct list *list_prepend(struct list *list, void *data, int datasize)
{
    struct list *new = calloc(1, sizeof(struct list));
    new->data = data;
    new->datasize = datasize;
    new->prev = list;
    new->next = list->next;
    list->next->prev = new;
    list->next = new;
    return list;
}

struct list *list_append(struct list *list, void *data, int datasize)
{
    struct list *cursor = list;
    struct list *new = calloc(1, sizeof(struct list));
    while ((cursor = cursor->next)->data);
    new->data = data;
    new->datasize = datasize;
    new->prev = cursor->prev;
    new->next = cursor;
    cursor->prev->next = new;
    cursor->prev = new;
    return list;
}

bool list_contains(struct list *list, void *data)
{
    struct list *cursor = list;
    while ((cursor = cursor->next)->data)
        if (!memcmp(data, cursor->data, cursor->datasize))
            return true;
    return false;
}

void list_remove(struct list *list, void *data)
{
    struct list *cursor = list;
    while ((cursor = cursor->next)->data)
    {
        if (!memcmp(data, cursor->data, cursor->datasize))
        {
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            return free(cursor);
        }
    }
}

void list_clear(struct list *list)
{
    struct list *cursor = list;
    while ((cursor = cursor->next)->data)
        free(cursor);
    list->next = cursor;
    cursor->prev = list;
}

void list_traverse(struct list *list, 
        void (*callback)(struct list *cursor), bool reverse)
{
    struct list *cursor = list;
    if (reverse)
    {
        while ((cursor = cursor->next)->data);
        while ((cursor = cursor->prev)->data)
            callback(cursor);
    } else 
    {
        while ((cursor = cursor->next)->data)
            callback(cursor);
    }
}

void list_free(struct list *list)
{
    if (list)
    {
        list_free(list->next);
        free(list);
    }
}

void list_test(void)
{
    struct list *list = list_create();
    int num1 = 90, num2 = 21, num3 = 198, num4 = 22;
    int num5 = 90; 
    list_append(list, &num1, sizeof(int));
    list_append(list, &num2, sizeof(int));
    list_append(list, &num3, sizeof(int));
    assert(list_size(list) == 3);
    assert(list_contains(list, &num5));
    assert(list_contains(list, &num2));
    assert(list_contains(list, &num3));

    list_remove(list, &num4);
    list_remove(list, &num2);
    assert(list_size(list) == 2);

    list_clear(list);
    assert(list_size(list) == 0);

    char *strings[] = { "hello", "goodbye", "world!" };
    list_prepend(list, strings[0], strlen(strings[0]));
    list_prepend(list, strings[1], strlen(strings[1]));
    list_prepend(list, strings[2], strlen(strings[2]));
    assert(list_size(list) == 3);
    assert(!list_contains(list, "hi"));
    assert(list_contains(list, "hello"));
    assert(list_contains(list, "goodbye"));
    assert(list_contains(list, "world!"));

    list_free(list);
}
