struct list
{
    struct list_node *first;
    struct list_node *last;
    int size;
};

struct list_node
{
    struct list_node *prev, *next;
    int data;
};

struct list *list_create(void);
int list_size(struct list *list);
struct list *list_prepend(struct list *list, int data);
struct list *list_append(struct list *list, int data);
void list_remove(struct list *list, int data);
bool list_contains(struct list *list, int data);
void list_traverse(struct list *list, 
        void (*callback)(struct list_node *cursor), bool reverse);
void list_to_array(struct list *list, int *arr);
void list_free(struct list *list);
void list_print(struct list_node *list);
void list_clear(struct list *list);
