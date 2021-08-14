#include "result.h"

struct Result *new_result() {
    struct Result *r = calloc(1, sizeof(struct Result));
    if (r == NULL)
        return NULL;

    return r;
}

switch_t get_switch(struct Result *r, char *s) {
    return get_listitem(r->switches, s);
}

optionlist_t *get_option(struct Result *r, char *o) {
    return get_opt(r->options, o);
}

char *get_positional(struct Result *r, char *p) {
    return get_listitem(r->positional, p);
}

char *index_postional(struct Result *r, unsigned int index) {
    struct ListItem *li = index_listitem(r->positional, index);
    if (li == NULL)
        return NULL;

    return li->name;
}

switch_t add_switch(struct Result *r, char *s) {
    char *sh = malloc(strlen(s) + 1);
    if (sh == NULL)
        return NULL;

    strncpy(sh, s, strlen(s) + 1);

    struct ListItem *li = add_listitem(r->switches, sh);
    if (li == NULL) {
        free(sh);
        return NULL;
    }

    return li->name;
}

optionlist_t *add_option(struct Result *r, char *key, char *value) {
    char *kh = malloc(strlen(key) + 1);
    if (kh == NULL)
        return NULL;

    strncpy(kh, key, strlen(key) + 1);

    char *vh = malloc(strlen(value) + 1);
    if (vh == NULL) {
        free(kh);
        return NULL;
    }

    strncpy(vh, value, strlen(value) + 1);

    return add_kvpair(r->options, kh, vh);
}

char *add_positional(struct Result *r, char *p) {
    char *ph = malloc(strlen(p) + 1);
    if (ph == NULL)
        return NULL;

    strncpy(ph, p, strlen(p) + 1);

    struct ListItem *li = add_listitem(r->positional, ph);
    if (li == NULL) {
        free(ph);
        return NULL;
    }

    return li->name;
}

void destroy_result(struct Result *r) {
    if (r == NULL)
        return;
    destroy_linkedlist(r->switches);
    destroy_optionmap(r->options);
    destroy_linkedlist(r->positional);
    free(r);
}