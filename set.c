#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dlinked-list.h"

/* set impl as doubly linked list */

struct set
{
    struct list *list;
};

struct set *set_create()
{
    struct set *set = calloc(1, sizeof(struct set));
    set->list = list_create();
    return set;
}

int set_size(struct set *set)
{
    return list_size(set->list);
}

bool set_contains(struct set *set, int data)
{
    return list_contains(set->list, data);
}

void set_insert(struct set *set, int data)
{
    if (!set_contains(set, data))
        list_prepend(set->list, data);
}

void set_remove(struct set *set, int data)
{
    list_remove(set->list, data);
}

struct set *set_union(struct set *set1, struct set *set2)
{
    struct set *s = set_create();
    int size1 = list_size(set1->list);
    int size2 = list_size(set2->list);
    int arr1[size1];
    int arr2[size2];
    list_to_array(set1->list, arr1);
    list_to_array(set2->list, arr2);
    for (int i = 0; i < size1; i++)
        set_insert(s, arr1[i]);
    for (int i = 0; i < size2; i++)
        set_insert(s, arr2[i]);
    return s;
}

void set_to_array(struct set *set, int *arr)
{
    list_to_array(set->list, arr);
}

void set_clear(struct set *set)
{
    list_clear(set->list);
}

void set_free(struct set *set)
{
    list_free(set->list);
    free(set);
}

int main(int argc, char **argv)
{
    struct set *set = set_create();
    set_insert(set, 4);
    set_insert(set, 4);
    set_insert(set, 5);
    assert(set_size(set) == 2);

    set_insert(set, 115);
    set_remove(set, 115);
    set_remove(set, 116);
    assert(set_size(set) == 2);

    set_clear(set);
    assert(set_size(set) == 0);

    set_insert(set, 44);
    set_insert(set, 45);
    set_insert(set, 44);
    set_insert(set, 46);
    int size = set_size(set);
    int arr[size];
    set_to_array(set, arr);
    assert(size == 3);
    for (int i = 0; i < size; i++)
        assert(arr[i] == 44 || arr[i] == 45 || arr[i] == 46);

    struct set *s1 = set_create();
    struct set *s2 = set_create();
    set_insert(s1, 12);
    set_insert(s1, 44);
    set_insert(s1, 45);
    set_insert(s1, 89);
    set_insert(s2, 20);
    set_insert(s2, 12);
    set_insert(s2, 45);
    set_insert(s2, 89);
    struct set *s3 = set_union(s1, s2);
    size = set_size(s3);
    int union_arr[size];
    set_to_array(s3, union_arr);
    assert(set_size(s3) == 5);
    assert(set_contains(s3, 12));
    assert(set_contains(s3, 44));
    assert(set_contains(s3, 45));
    assert(set_contains(s3, 20));
    assert(set_contains(s3, 89));

    set_free(set);
    return 0;
}
