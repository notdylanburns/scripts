#include "parse.h"

struct ParseOption *new_option(enum ArgType t, char *name, unsigned int num) {
    struct ParseOption *o = malloc(sizeof(struct ParseOption));
    if (o == NULL) 
        return NULL;

    *o = NewParseOption(t, name, num);
    return o;
}

struct Result *parse_args(int argc, char **argv, unsigned int num_opts, struct ParseOption **opts, enum ParseMode pm) {
    if (argc == 0) 
        return NULL;

    struct Result *r = new_result();
    if (r == NULL)
        return NULL;

    r->switches = new_linkedlist();
    r->options = new_optionmap();
    r->positional = new_linkedlist();

    if (r->switches == NULL || r->options == NULL || r->positional == NULL)
        return NULL;
    
    if (pm == PM_SEPARATE) {
        for (int i = 0; i < argc; i++) {
            char matched = 0;
            for (int j = 0; j < num_opts; j++) {
                if (!strcmp(argv[i], opts[j]->name)) {
                    matched = 1;
                    switch (opts[j]->type) {
                        case ARG_SWITCH:
                            if (add_switch(r, argv[i]) == NULL)
                                goto nomem;
                            break;

                        case ARG_OPTION:
                            for (int k = 0; k < opts[j]->num_values; k++) {
                                if (i + k + 1 >= argc) {
                                    fprintf(stderr, "%s expects %d parameters\n", opts[j]->name, opts[j]->num_values);
                                    goto fail;
                                } else if (add_option(r, argv[i], argv[i + k + 1]) == NULL)
                                    goto nomem;
                            }
                            i += opts[j]->num_values;
                            break;
                        
                        default:
                            goto fail;
                    }
                }
                if (matched)
                    break;
            }

            if (!matched) 
                if (add_positional(r, argv[i]) == NULL)
                    goto nomem;
        }
    } else if (pm == PM_DEFAULT) {

    } else 
        return NULL;

    return r;

nomem:
    fprintf(stderr, "Insufficient memory.\n");
fail:
    destroy_result(r);
    return NULL;
}

void destroy_parseoption(struct ParseOption *o) {
    free(o);
}