#include "option_map.h"

static unsigned int hash(char *v) {
    unsigned int hash = 5381;
    int c;

    for (int i = 0; i < strlen(v); i++) {
        c = v[i];
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

struct OptionMap *new_optionmap() {
    struct OptionMap *o = malloc(sizeof(struct OptionMap));
    if (o == NULL)
        return NULL;

    o->hashf = hash;
    o->buckets = calloc(NUM_BUCKETS, sizeof(struct ll_ *));
    if (o->buckets == NULL) {
        free(o);
        return NULL;
    }

    return o;
}

struct LinkedList *add_kvpair(struct OptionMap *o, char *k, char *v) {
    unsigned int index = o->hashf(k) % NUM_BUCKETS;

    struct ll_ *prev = NULL, *bucket = o->buckets[index];
    char exists = 0;
    while (bucket != NULL) {
        prev = bucket;
        if (!strcmp(bucket->key, k)) { 
            exists = 1;
            free(k);
            break;
        }
        bucket = bucket->next;
    }

    if (!exists) {
        if (prev == NULL) {
            o->buckets[index] = malloc(sizeof(struct ll_));
            if (o->buckets[index] == NULL)
                return NULL;

            bucket = o->buckets[index];
        } else {
            prev->next = malloc(sizeof(struct ll_));
            if (prev->next == NULL)
                return NULL;

            bucket = prev->next;
        }

        bucket->key = k;
        bucket->value = NULL;
        bucket->next = NULL;
        
    }

    if (bucket->value == NULL) {
        bucket->value = new_linkedlist();
        if (bucket->value == NULL)
            return NULL;
    }

    if (add_listitem(bucket->value, v) == NULL)
        return NULL;

    return bucket->value;
}

struct LinkedList *get_opt(struct OptionMap *o, char *key) {
    unsigned int index = o->hashf(key) % NUM_BUCKETS;

    struct ll_ *bucket = o->buckets[index];
    while (bucket != NULL) {
        if (!strcmp(bucket->key, key)) 
            return bucket->value;
        bucket = bucket->next;
    }

    return NULL;
    
}

void destroy_optionmap(struct OptionMap *o) {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        if (o->buckets[i] != NULL) {
            struct ll_ *tmp = NULL, *b = o->buckets[i];
            while (b != NULL) {
                free(b->key);
                destroy_linkedlist(b->value);
                tmp = b->next;
                free(b);
                b = tmp;
            }
        }
    }
    free(o->buckets);
    free(o);
}