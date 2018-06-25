#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* singly linked list */

struct list 
{
    int data;
    struct list *next;
};

bool list_empty(struct list *list)
{
    return list->next->next == NULL;
}

int list_size(struct list *list)
{
    if (list->next->next == NULL) 
        return 0;
    return 1 + list_size(list->next);
}

struct list *list_create(void)
{
    struct list *first = calloc(1, sizeof(struct list));
    struct list *last = calloc(1, sizeof(struct list));
    first->next = last;
    return first;
}

struct list *list_prepend(struct list *list, int data)
{
    struct list *new = calloc(1, sizeof(struct list));
    new->data = data;
    new->next = list->next;
    list->next = new;
    return list;
}

struct list *list_append(struct list *list, int data)
{
    if (list->next->next != NULL)
        return list_append(list->next, data);
    struct list *new = calloc(1, sizeof(struct list));
    new->data = data;
    new->next = list->next;
    list->next = new;
    return list;
}

struct list *list_remove(struct list *list, int data)
{
    if (list->next->next == NULL)
        return NULL;
    if (list->next->data == data) {
        struct list *rm = list->next;
        list->next = list->next->next;
        free(rm);
        return rm;
    }
    return list_remove(list->next, data);
}

void list_traverse(struct list *list, void (*callback)(struct list *data))
{
    if (list->next && list->next->next) 
    {
        callback(list->next);
        list_traverse(list->next, callback);
    }
}

struct list *list_search(struct list *list, int data)
{
    if (!(list->next && list->next->next))
        return NULL;
    if (list->next->data == data)
        return list->next;
    return list_search(list->next, data);
}


void list_print(struct list *list)
{
    printf("%d\n", list->data);
}

void list_free(struct list *list)
{
    if (list)
    {
        list_free(list->next);
        free(list);
    }
}

int *list_array(struct list *list, int *arr)
{
    if (list->next && list->next->next)
    {
        *arr++ = list->next->data;
        return list_array(list->next, arr);
    }
    return arr;

}

int main(int argc, char **argv)
{
    struct list *list = list_create();
    assert(list_empty(list) == true);
    assert(list_size(list) == 0);

    list_prepend(list, 3);
    list_prepend(list, 2);
    list_prepend(list, 1);
    assert(list_empty(list) == false);
    assert(list_size(list) == 3);

    list_append(list, 4); 
    list_append(list, 5); 
    assert(list_size(list) == 5);

    list_remove(list, 5);
    list_remove(list, 2);
    list_remove(list, 11);
    assert(list_size(list) == 3);

    list_remove(list, 1);
    list_remove(list, 2);
    list_remove(list, 3);
    list_remove(list, 4);
    assert(list_empty(list) == true);
    assert(list_size(list) == 0);

    list_append(list, 11);
    list_append(list, 32);
    list_append(list, 123);

    int arr[list_size(list)];
    list_array(list, arr);
    assert(list_size(list) == sizeof(arr) / sizeof(*arr));
    assert(arr[0] == 11);
    assert(arr[1] == 32);
    assert(arr[2] == 123);

    struct list *s1 = list_search(list, 32);
    struct list *s2 = list_search(list, 23);
    assert(s1 != NULL);
    assert(s1->data == 32);
    assert(s2 == NULL);
    
    list_traverse(list, list_print);
    list_free(list);
    return 0;
}
