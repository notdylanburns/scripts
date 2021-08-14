#include "parse.h"

struct ParseOption *new_option(enum ArgType t, char *name, int num) {
    struct ParseOption *o = malloc(sizeof(struct ParseOption));
    if (o == NULL) 
        return NULL;

    *o = NewParseOption(t, name, num);
    return o;
}

struct ParseOption *get_parseoption(struct ParseOption **opts, unsigned int num_opts, char *f) {
    for (int i = 0; i < num_opts; i++) {
        if (!strcmp(opts[i]->name, f))
            return opts[i];
    }

    return NULL;
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
                            if (opts[j]->num_values < 0) {
                                for (int k = 0; (i + k + 1) < argc; k++) {
                                    if (add_option(r, argv[i], argv[i + k + 1]) == NULL)
                                        goto nomem;
                                }
                                return r;
                            } else {
                                for (int k = 0; k < opts[j]->num_values; k++) {
                                    if (i + k + 1 >= argc) {
                                        fprintf(stderr, "%s expects %d parameters\n", opts[j]->name, opts[j]->num_values);
                                        goto fail;
                                    } else if (add_option(r, argv[i], argv[i + k + 1]) == NULL)
                                        goto nomem;
                                }
                                i += opts[j]->num_values;
                            }
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
        for (int i = 0; i < argc; i++) {
            if (strlen(argv[i]) && argv[i][0] == '-' && argv[i][1] != '-') {
                for (char *c = (argv[i] + 1); *c; c++) {
                    char s[3] = { '-', *c, '\0' };
                    struct ParseOption *o = get_parseoption(opts, num_opts, s);
                    if (o != NULL) {
                        switch (o->type) {
                            case ARG_SWITCH:
                                if (add_switch(r, s) == NULL) 
                                    goto nomem;
                                break;

                            case ARG_OPTION:
                                if (o->num_values != 0 && *(c + 1) == '\0') {
                                    if (o->num_values < 0) {
                                        for (int k = 0; (i + k + 1) < argc; k++) {
                                            if (add_option(r, s, argv[i + k + 1]) == NULL)
                                                goto nomem;
                                        }
                                        return r;
                                    } else {
                                        for (int j = 0; j < o->num_values; j++) {
                                            if (i + j + 1 >= argc) {
                                                fprintf(stderr, "Option '%s' expects %d parameters\n", o->name, o->num_values);
                                                goto fail;
                                            } else if (add_option(r, s, argv[i + j + 1]) == NULL)
                                                goto nomem;
                                        }
                                    }
                                } else {
                                    fprintf(stderr, "Option '%s' expects %d parameters\n", o->name, o->num_values);
                                    goto fail;
                                }
                                i += o->num_values;
                                break;
                        }
                    } else {
                        fprintf(stderr, "Unrecognised option: '%s'\n", s);
                        goto fail;
                    }
                }
            } else if (strlen(argv[i]) > 1 && argv[i][0] == '-' && argv[i][1] == '-') {
                struct ParseOption *o = get_parseoption(opts, num_opts, argv[i]);
                if (o != NULL) {
                    switch (o->type) {
                        case ARG_SWITCH:
                            if (add_switch(r, o->name) == NULL) 
                                goto nomem;
                            break;

                        case ARG_OPTION:
                            if (o->num_values < 0) {
                                for (int k = 0; (i + k + 1) < argc; k++) {
                                    if (add_option(r, o->name, argv[i + k + 1]) == NULL)
                                        goto nomem;
                                }
                                return r;
                            } else {
                                for (int j = 0; j < o->num_values; j++) {
                                    if (i + j + 1 >= argc) {
                                        fprintf(stderr, "Option '%s' expects %d parameters\n", o->name, o->num_values);
                                        goto fail;
                                    } else if (add_option(r, argv[i], argv[i + j + 1]) == NULL)
                                        goto nomem;
                                }
                                i += o->num_values;
                            }
                            break;
                    }
                }
            } else {
                if (get_parseoption(opts, num_opts, argv[i]) != NULL) {
                    fprintf(stderr, "In default mode, options must start with '-' or '--'\n");
                    goto fail;
                } else {
                    if (add_positional(r, argv[i]) == NULL)
                        goto nomem;
                }
            }
        }
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