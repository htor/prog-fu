#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <strings.h>

struct list { struct list *prev, *next; void *data; int datasize; };
struct list *list_create(void);
int list_size(struct list *list);
struct list *list_prepend(struct list *list, void *data, int datasize);
struct list *list_append(struct list *list, void *data, int datasize);
bool list_contains(struct list *list, void *data);
void list_remove(struct list *list, void *data);
void list_clear(struct list *list);
void list_traverse(struct list *list, 
        void (*callback)(struct list *cursor), bool reverse);
void list_free(struct list *list);
void list_test(void);
