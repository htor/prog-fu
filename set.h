struct set
{
    struct list *list;
};

struct set *set_create(void);
int set_size(struct set *set);
bool set_contains(struct set *set, int data);
void set_insert(struct set *set, int data);
void set_remove(struct set *set, int data);
struct set *set_union(struct set *set1, struct set *set2);
struct set *set_intersect(struct set *set1, struct set *set2);
struct set *set_diff(struct set *set1, struct set *set2);
bool set_subset(struct set *set1, struct set *set2);
void set_to_array(struct set *set, int *arr);
void set_free(struct set *set);
