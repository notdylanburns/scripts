#ifndef _PARSE_H_GUARD_
#define _PARSE_H_GUARD_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "result.h"

#define ARGS_REST -1

enum ArgType {
    ARG_SWITCH,
    ARG_OPTION,
};

enum ParseMode {
    PM_DEFAULT,
    PM_SEPARATE,
};

struct ParseOption {
    enum ArgType type;
    char *name;
    int num_values;
};

#define NewParseOption(t, n, v) (struct ParseOption){ \
    .type = (t), \
    .name = (n), \
    .num_values = (v), \
}

#define NewSwitch(n) (struct ParseOption){ \
    .type = ARG_SWITCH, \
    .name = (n), \
    .num_values = 0, \
}

#define NewOption(n, v) (struct ParseOption){ \
    .type = ARG_OPTION, \
    .name = (n), \
    .num_values = (v), \
}

extern struct ParseOption *new_parseoption(enum ArgType t, char *name, int num);
extern struct ParseOption *get_parseoption(struct ParseOption **opts, unsigned int num_opts, char *f);
extern struct Result *parse_args(int argc, char **argv, unsigned int num_opts, struct ParseOption **opts, enum ParseMode pm);
extern void destroy_parseoption(struct ParseOption *o);

#endif