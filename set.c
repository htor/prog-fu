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

struct set *set_create(void)
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
    struct set *unionset = set_create();
    struct list_node *cursor = set1->list->first;
    while ((cursor = cursor->next) != set1->list->last)
        set_insert(unionset, cursor->data);
    cursor = set2->list->first;
    while ((cursor = cursor->next) != set2->list->last)
        set_insert(unionset, cursor->data);
    return unionset;
}

struct set *set_intersect(struct set *set1, struct set *set2)
{
    struct set *interset = set_create();
    struct list_node *cursor = set1->list->first;
    while ((cursor = cursor->next) != set1->list->last)
        if (set_contains(set2, cursor->data))
            set_insert(interset, cursor->data);
    cursor = set2->list->first;
    while ((cursor = cursor->next) != set2->list->last)
        if (set_contains(interset, cursor->data))
            set_insert(interset, cursor->data);
    return interset;
}

struct set *set_diff(struct set *set1, struct set *set2)
{
    struct set *diffset = set_create();
    struct list_node *cursor = set1->list->first;
    while ((cursor = cursor->next) != set1->list->last)
        if (!set_contains(set2, cursor->data))
            set_insert(diffset, cursor->data);
    return diffset;
}

bool set_subset(struct set *set1, struct set *set2)
{
    struct list_node *cursor = set1->list->first;
    while ((cursor = cursor->next) != set1->list->last)
        if (set_contains(set2, cursor->data))
            continue;
        else
            return false;
    return true;
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
    assert(set_size(set) == 3);
    assert(set_contains(set, 44));
    assert(set_contains(set, 45));
    assert(set_contains(set, 46));

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
    set_insert(s2, 90);

    struct set *s3 = set_union(s1, s2);
    assert(set_size(s3) == 6);
    assert(set_contains(s3, 12));
    assert(set_contains(s3, 44));
    assert(set_contains(s3, 45));
    assert(set_contains(s3, 20));
    assert(set_contains(s3, 89));
    assert(set_contains(s3, 90));

    struct set *s4 = set_intersect(s1, s2);
    assert(set_size(s4) == 3);
    assert(set_contains(s4, 12));
    assert(set_contains(s4, 45));
    assert(set_contains(s4, 89));

    struct set *s5 = set_diff(s1, s2);
    struct set *s6 = set_diff(s2, s1);
    assert(set_size(s5) == 1);
    assert(set_contains(s5, 44));
    assert(set_size(s6) == 2);
    assert(set_contains(s6, 20));
    assert(set_contains(s6, 90));

    struct set *s7 = set_create();
    struct set *s8 = set_create();
    assert(set_subset(s7, s8));
    set_insert(s7, 11);
    set_insert(s7, 12);
    set_insert(s8, 11);
    set_insert(s8, 12);
    set_insert(s8, 13);
    assert(set_subset(s7, s8));
    assert(set_subset(s8, s7) == false);

    set_free(set);
    return 0;
}
