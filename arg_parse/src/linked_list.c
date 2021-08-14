#include "linked_list.h"

struct LinkedList *new_linkedlist() {
    struct LinkedList *ll = calloc(1, sizeof(struct LinkedList));
    if (ll == NULL)
        return NULL;

    return ll;
}

struct ListItem *new_listitem(char *name) {
    struct ListItem *li = calloc(1, sizeof(struct ListItem));
    if (li == NULL)
        return NULL;

    li->name = name;
    return li;
}

struct ListItem *add_listitem(struct LinkedList *l, char *name) {
    struct ListItem *next = l->start, *li = new_listitem(name);
    if (li == NULL)
        return NULL;

    if (next == NULL)
        l->start = li;
    else {
        while (next->next != NULL)
            next = next->next;

        next->next = li;
    }
    
    l->size++;

    return li;
    
}

char *get_listitem(struct LinkedList *l, char *p) {
    struct ListItem *li = l->start;
    while (li != NULL) {
        if (!strcmp(li->name, p))
            return li->name;
        li = li->next;
    }

    return NULL;
}

struct ListItem *index_listitem(struct LinkedList *l, unsigned int index) {
    if (index >= l->size)
        return NULL;

    struct ListItem *li = l->start;

    for (int i = 0; i < index; i++)
        li = li->next;

    return li;
}

void destroy_linkedlist(struct LinkedList *l) {
    if (l == NULL) 
        return;

    struct ListItem *next, *li = l->start;
    while (li != NULL) {
        next = li->next;
        destroy_listitem(li);
        li = next;
    }
}

void destroy_listitem(struct ListItem *l) {
    free(l);
}