#include <arg_parse/arg.h>

#include <stdio.h>

int main(int argc, char **argv) {
    argc--;
    argv++;

    struct ParseOption *opts[] = {
        &NewSwitch("-h"),
        &NewOption("-p", 1),
        &NewOption("--log-level", 1),
    };
    
    struct Result *r = parse_args(argc, argv, 3, opts);
    char *res = get_switch(r, "-h");
    printf("%s\n", res ?: "null");

    struct LinkedList *ll = get_option(r, "-p");
    if (ll != NULL)
        for (int i = 0; i < ll->size; i++)
            printf("%s\n", index_listitem(ll, i)->name);
    for (int i = 0; i < r->positional->size; i++) 
        printf("%s\n", index_postional(r, i));

    return 0;
}