#ifndef _PARSE_H_GUARD_
#define _PARSE_H_GUARD_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "result.h"

enum ArgType {
    ARG_SWITCH,
    ARG_OPTION,
    ARG_POSITIONAL,
};

struct ParseOption {
    enum ArgType type;
    char *name;
    unsigned int num_values;
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

extern struct ParseOption *new_parseoption(enum ArgType t, char *name, unsigned int num);
extern struct Result *parse_args(int argc, char **argv, int num_opts, struct ParseOption **opts);

#endif