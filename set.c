#include "set.h"

/* set implemented using a linked list */

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

bool set_contains(struct set *set, void *data)
{
    return list_contains(set->list, data);
}

void set_insert(struct set *set, void *data, int datasize)
{
    if (!set_contains(set, data))
        list_prepend(set->list, data, datasize);
}

void set_remove(struct set *set, void *data)
{
    list_remove(set->list, data);
}

struct set *set_union(struct set *set1, struct set *set2)
{
    struct set *unionset = set_create();
    struct list *cursor = set1->list;
    while ((cursor = cursor->next)->data)
        set_insert(unionset, cursor->data, cursor->datasize);
    cursor = set2->list;
    while ((cursor = cursor->next)->data)
        set_insert(unionset, cursor->data, cursor->datasize);
    return unionset;
}

struct set *set_intersect(struct set *set1, struct set *set2)
{
    struct set *interset = set_create();
    struct list *cursor = set1->list;
    while ((cursor = cursor->next)->data)
        if (set_contains(set2, cursor->data))
            set_insert(interset, cursor->data, cursor->datasize);
    cursor = set2->list;
    while ((cursor = cursor->next)->data)
        if (set_contains(set1, cursor->data))
            set_insert(interset, cursor->data, cursor->datasize);
    return interset;
}

struct set *set_diff(struct set *set1, struct set *set2)
{
    struct set *diffset = set_create();
    struct list *cursor = set1->list;
    while ((cursor = cursor->next)->data)
        if (!set_contains(set2, cursor->data))
            set_insert(diffset, cursor->data, cursor->datasize);
    return diffset;
}

bool set_subset(struct set *set1, struct set *set2)
{
    struct list *cursor = set1->list;
    while ((cursor = cursor->next)->data)
        if (set_contains(set2, cursor->data))
            continue;
        else
            return false;
    return true;
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

void set_test(void)
{
    struct set *set = set_create();
    int nums[] = { 4, 5 };
    set_insert(set, &nums[0], sizeof(int));
    set_insert(set, &nums[0], sizeof(int));
    set_insert(set, &nums[1], sizeof(int));
    assert(set_size(set) == 2);

    set_clear(set);
    int morenums[] = { 115, 116 };
    set_insert(set, &morenums[0], sizeof(int));
    set_insert(set, &morenums[1], sizeof(int));
    set_remove(set, &morenums[0]);
    set_remove(set, &morenums[1]);
    assert(set_size(set) == 0);

    set_clear(set);
    assert(set_size(set) == 0);

    int num1 = 11, num2 = 22;
    set_insert(set, "fink", strlen("fink"));
    set_insert(set, "ployd", strlen("ployd"));
    set_insert(set, "ployd", strlen("ployd"));
    set_insert(set, &num1, sizeof(int));
    set_insert(set, &num2, sizeof(int));
    assert(set_size(set) == 4);
    assert(set_contains(set, "fink"));
    assert(set_contains(set, "ployd"));
    assert(set_contains(set, &num1));
    assert(set_contains(set, &num2));

    struct set *s1 = set_create();
    struct set *s2 = set_create();
    int manynums[] = { 12, 44, 45, 89, 20, 12, 45, 89, 90 };
    set_insert(s1, &manynums[0], sizeof(int));
    set_insert(s1, &manynums[1], sizeof(int));
    set_insert(s1, &manynums[2], sizeof(int));
    set_insert(s1, &manynums[3], sizeof(int));
    set_insert(s2, &manynums[4], sizeof(int));
    set_insert(s2, &manynums[5], sizeof(int));
    set_insert(s2, &manynums[6], sizeof(int));
    set_insert(s2, &manynums[7], sizeof(int));
    set_insert(s2, &manynums[8], sizeof(int));

    struct set *s3 = set_union(s1, s2);
    assert(set_size(s3) == 6);
    assert(set_contains(s3, &manynums[0]));
    assert(set_contains(s3, &manynums[1]));
    assert(set_contains(s3, &manynums[2]));
    assert(set_contains(s3, &manynums[4]));
    assert(set_contains(s3, &manynums[3]));
    assert(set_contains(s3, &manynums[8]));

    struct set *s4 = set_intersect(s1, s2);
    int a = 12, b = 45, c = 89;
    assert(set_size(s4) == 3);
    assert(set_contains(s4, &a));
    assert(set_contains(s4, &b));
    assert(set_contains(s4, &c));

    struct set *s5 = set_diff(s1, s2);
    struct set *s6 = set_diff(s2, s1);
    int d = 44, e = 20, f = 90;
    assert(set_size(s5) == 1);
    assert(set_contains(s5, &d));
    assert(set_size(s6) == 2);
    assert(set_contains(s6, &e));
    assert(set_contains(s6, &f));

    struct set *s7 = set_create();
    struct set *s8 = set_create();
    assert(set_subset(s7, s8));
    int g = 11, h = 12, i = 13;
    set_insert(s7, &g, sizeof(int));
    set_insert(s7, &h, sizeof(int));
    set_insert(s8, &g, sizeof(int));
    set_insert(s8, &h, sizeof(int));
    set_insert(s8, &i, sizeof(int));
    assert(set_subset(s7, s8));
    assert(!set_subset(s8, s7));

    set_free(set);
    set_free(s1);
    set_free(s2);
    set_free(s3);
    set_free(s4);
    set_free(s5);
    set_free(s6);
    set_free(s6);
    set_free(s7);
    set_free(s8);
}

