#ifndef _LINKED_LIST_H_GUARD_
#define _LINKED_LIST_H_GUARD_

#include <stdlib.h>
#include <string.h>

struct LinkedList {
    unsigned int size;
    struct ListItem *start;
};

struct ListItem {
    char *name;
    struct ListItem *next;
};

extern struct LinkedList *new_linkedlist();
extern struct ListItem *new_listitem(char *name);
extern struct ListItem *add_listitem(struct LinkedList *l, char *name);
extern struct ListItem *index_listitem(struct LinkedList *l, unsigned int index);
extern char *get_listitem(struct LinkedList *l, char *p);
extern void destroy_linkedlist(struct LinkedList *l);
extern void destroy_listitem(struct ListItem *l);

#endif