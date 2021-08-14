#ifndef _RESULT_H_GUARD_
#define _RESULT_H_GUARD_

#include <stdlib.h>

#include "linked_list.h"
#include "option_map.h"

typedef char * switch_t;
typedef struct LinkedList optionlist_t;

struct Result {
    struct LinkedList *switches;
    struct OptionMap *options;
    struct LinkedList *positional;
};

#define NewResult(s, o, p) (struct Result){ \
    .switches = s, \
    .options = o, \
    .positional = p, \
}

extern struct Result *new_result();
extern switch_t get_switch(struct Result *r, char *f);
extern optionlist_t *get_option(struct Result *r, char *o);
extern char *get_positional(struct Result *r, char *p);
extern char *index_postional(struct Result *r, unsigned int index);
extern switch_t add_switch(struct Result *r, char *s);
extern optionlist_t *add_option(struct Result *r, char *key, char *value);
extern char *add_positional(struct Result *r, char *p);
extern void destroy_result(struct Result *r);

#endif