#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dlinked-list.h"

/* doubly linked list */

struct list *list_create(void)
{
    struct list *list = calloc(1, sizeof(struct list));
    struct list_node *first = calloc(1, sizeof(struct list_node));
    struct list_node *last = calloc(1, sizeof(struct list_node));
    first->next = last;
    last->prev = first;
    list->first = first;
    list->last = last;
    return list;
}

int list_size(struct list *list)
{
    int size = 0;
    struct list_node *cursor = list->first;
    while ((cursor = cursor->next) != list->last) 
        size++;
    return size;
}

struct list *list_prepend(struct list *list, int data)
{
    struct list_node *new = calloc(1, sizeof(struct list_node));
    new->data = data;
    new->prev = list->first;
    new->next = list->first->next;
    list->first->next->prev = new;
    list->first->next = new;
    return list;
}

struct list *list_append(struct list *list, int data)
{
    struct list_node *new = calloc(1, sizeof(struct list_node));
    new->data = data;
    new->prev = list->last->prev;
    new->next = list->last;
    list->last->prev->next = new;
    list->last->prev = new;
    return list;
}

void list_remove(struct list *list, int data)
{
    struct list_node *cursor = list->first;
    while ((cursor = cursor->next) != list->last)
    {
        if (cursor->data == data)
        {
            cursor->prev->next = cursor->next;
            cursor->next->prev = cursor->prev;
            return free(cursor);
        }
    }
}

bool list_contains(struct list *list, int data)
{
    struct list_node *cursor = list->first;
    while ((cursor = cursor->next) != list->last)
        if (cursor->data == data)
            return true;
    return false;
}

void list_traverse(struct list *list, 
        void (*callback)(struct list_node *cursor), bool reverse)
{
    struct list_node *cursor;
    if (reverse)
    {
        cursor = list->last;
        while ((cursor = cursor->prev) != list->first)
            callback(cursor);
    } else 
    {
        cursor = list->first;
        while ((cursor = cursor->next) != list->last)
            callback(cursor);
    }
}

void list_to_array(struct list *list, int *arr)
{
    struct list_node *cursor = list->first;
    while ((cursor = cursor->next) != list->last)
        *arr++ = cursor->data;
}

void list_node_free(struct list_node *list)
{
    free(list);
}

void list_clear(struct list *list)
{
    list_traverse(list, list_node_free, false);
    list->first->next = list->last;
    list->last->prev = list->first;
}

void list_print(struct list_node *list)
{
    printf("%d\n", list->data);
}

void list_free(struct list *list)
{
    struct list_node *cursor = list->last;
    struct list_node *prev;
    while (cursor)
    {
        prev = cursor->prev;
        free(cursor);
        cursor = prev;
    }
    free(list);
}

int nomain(int argc, char **argv)
{
    struct list *list = list_create();
    list_append(list, 90);
    list_append(list, 21);
    list_append(list, 198);
    assert(list_size(list) == 3);
    assert(list_contains(list, 90));
    assert(list_contains(list, 198));
    assert(list_contains(list, 21));

    list_remove(list, 22);
    list_remove(list, 21);
    assert(list_size(list) == 2);

    list_clear(list);
    assert(list_size(list) == 0);

    list_prepend(list, 33);
    list_prepend(list, 22);
    list_prepend(list, 11);
    int size = list_size(list);
    int arr[size];
    list_to_array(list, arr);
    assert(arr[0] == 11);
    assert(arr[1] == 22);
    assert(arr[2] == 33);
    
    list_traverse(list, list_print, false);
    list_traverse(list, list_print, true);

    list_free(list);
    return 0;
}
