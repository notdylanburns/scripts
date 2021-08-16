#include "logger.h"

const char *DefaultPrefix[] = { "[ FATAL ] ", "[ ERROR ] ", "[ WARN ] ", "[ LOG ] ", NULL };

Logger *create_logger(FILE *out, FILE *err, enum LogLevel ll, const char **prefixes) {
    Logger *l = malloc(sizeof(Logger));
    if (l == NULL)
        return NULL;

    l->out = out;
    l->err = err;
    l->ll = ll;

    l->prefixes = prefixes;

    if (prefixes == NULL) {
        l->prefixes = malloc(sizeof(const char *) * 5);
        if (l->prefixes == NULL) {
            free(l);
            return NULL;
        }

        char **ptr = (char **)DefaultPrefix;
        for (int i = 0; *ptr; ptr++, i++) {
            l->prefixes[i] = *ptr;
        }
    }

    return l;
}

void destroy_logger(Logger *l) {
    free(l);
}

void llog(Logger *l, char *msg) {
    if (l == NULL)
        l = DefaultLogger;

    if (l->ll < LOG)
        return;
    
    fprintf(l->out, "%s%s\n", l->prefixes[LOG], msg);
}

void lwarn(Logger *l, char *msg) {
    if (l == NULL)
        l = DefaultLogger;

    if (l->ll < WARNING)
        return;

    fprintf(l->out, "%s%s\n", l->prefixes[WARNING], msg);

}

void lerror(Logger *l, char *msg) {
    if (l == NULL)
        l = DefaultLogger;

    if (l->ll < ERROR)
        return;

    fprintf(l->err, "%s%s\n", l->prefixes[ERROR], msg);
}

void lfatal(Logger *l, int errorcode, char *msg) {
    if (l == NULL)
        l = DefaultLogger;

    if (l->ll < FATAL)
        return;

    fprintf(l->err, "%s%s\n", l->prefixes[FATAL], msg);

    exit(errorcode);
}

void lmsg(Logger *l, enum LogLevel ll, int errorcode, char *msg) {
    switch (ll) {
        case FATAL:
            lfatal(l, errorcode, msg);
            break;
        
        case ERROR:
            lerror(l, msg);
            break;

        case WARNING:
            lwarn(l, msg);
            break;
        
        case LOG:
            llog(l, msg);
            break;
        
        default:
            break;
    }
}

void llogf(Logger *l, const char *fmt, ...) {
    if (l == NULL)
        l = DefaultLogger;
    
    if (l->ll < LOG)
        return;

    va_list v;
    va_start(v, fmt);

    fprintf(l->out, "%s", l->prefixes[LOG]);
    vfprintf(l->out, fmt, v);
    fprintf(l->out, "\n");

    va_end(v);
}

void lwarnf(Logger *l, const char *fmt, ...) {
    if (l == NULL)
        l = DefaultLogger;
    
    if (l->ll < WARNING)
        return;

    va_list v;
    va_start(v, fmt);

    fprintf(l->out, "%s", l->prefixes[WARNING]);
    vfprintf(l->out, fmt, v);
    fprintf(l->out, "\n");

    va_end(v);
}

void lerrorf(Logger *l, const char *fmt, ...) {
    if (l == NULL)
        l = DefaultLogger;
    
    if (l->ll < ERROR)
        return;

    va_list v;
    va_start(v, fmt);

    fprintf(l->err, "%s", l->prefixes[ERROR]);
    vfprintf(l->err, fmt, v);
    fprintf(l->err, "\n");

    va_end(v);
}

void lfatalf(Logger *l, int errorcode, const char *fmt, ...) {
    if (l == NULL)
        l = DefaultLogger;
    
    if (l->ll < FATAL)
        return;

    va_list v;
    va_start(v, fmt);

    fprintf(l->err, "%s", l->prefixes[FATAL]);
    vfprintf(l->err, fmt, v);
    fprintf(l->err, "\n");

    va_end(v);

    exit(errorcode);
}

void lmsgf(Logger *l, enum LogLevel ll, int errorcode, const char *fmt, ...) {
    if (l == NULL)
        l = DefaultLogger;
    
    if (l->ll < ll)
        return;

    FILE *ostream;
    const char *prefix;
    
    va_list v;
    va_start(v, fmt);

    switch (ll) {
        case FATAL:
            ostream = l->err;
            prefix = l->prefixes[FATAL];
            break;
        
        case ERROR:
            ostream = l->err;
            prefix = l->prefixes[ERROR];
            break;

        case WARNING:
            ostream = l->out;
            prefix = l->prefixes[WARNING];
            break;
        
        case LOG:
            ostream = l->out;
            prefix = l->prefixes[LOG];
            break;
        
        default:
            return;
    }

    fprintf(ostream, "%s", prefix);
    vfprintf(ostream, fmt, v);
    fprintf(ostream, "\n");

    va_end(v);

    if (ll == FATAL)
        exit(errorcode);

}