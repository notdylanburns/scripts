#ifndef _OPTION_MAP_H_GUARD_
#define _OPTION_MAP_H_GUARD_

#include "linked_list.h"

#define NUM_BUCKETS 256

typedef unsigned int (Hashf)(char *);

struct ll_ {
    char *key;
    struct LinkedList *value;
    struct ll_ *next;
};

struct OptionMap {
    struct ll_ **buckets;
    Hashf *hashf;
};

extern struct OptionMap *new_optionmap();
extern struct LinkedList *add_kvpair(struct OptionMap *o, char *k, char *v);
extern struct LinkedList *get_opt(struct OptionMap *o, char *key);
extern void destroy_optionmap(struct OptionMap *o);

#endif