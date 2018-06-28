#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "linked-list.h"

struct set { struct list *list; }; 
struct set *set_create(void);
int set_size(struct set *set);
void set_insert(struct set *set, void *data, int datasize);
void set_remove(struct set *set, void *data);
bool set_contains(struct set *set, void *data);
struct set *set_union(struct set *set1, struct set *set2);
struct set *set_intersect(struct set *set1, struct set *set2);
struct set *set_diff(struct set *set1, struct set *set2);
bool set_subset(struct set *set1, struct set *set2);
void set_free(struct set *set);
void set_test(void);
