#ifndef _LOGGER_H_GUARD_
#define _LOGGER_H_GUARD_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

enum LogLevel {
    FATAL,
    ERROR,
    WARNING,
    LOG,
    QUIET,
};

typedef struct {
    FILE *out;
    FILE *err;
    enum LogLevel ll;
    const char **prefixes; // 5 string array containing logging prefixes (index 4 should be NULL)
} Logger;

extern const char *DefaultPrefix[];
#define DefaultLogger     (&(Logger){ .out = stdout, .err = stderr, .ll = LOG, .prefixes = DefaultPrefix })
#define DefaultWithLL(ll) (&(Logger){ .out = stdout, .err = stderr, .ll = ll, .prefixes = DefaultPrefix })

extern Logger *create_logger(FILE *out, FILE *err, enum LogLevel ll, const char **prefixes);
extern void destroy_logger(Logger *l);

extern void llog(Logger *l, char *msg); // out
extern void lwarn(Logger *l, char *msg); // out
extern void lerror(Logger *l, char *msg); // err
extern void lfatal(Logger *l, int errorcode, char *msg); // err
extern void lmsg(Logger *l, enum LogLevel ll, int errorcode, char *msg);

extern void llogf(Logger *l, const char *fmt, ...);
extern void lwarnf(Logger *l, const char *fmt, ...);
extern void lerrorf(Logger *l, const char *fmt, ...);
extern void lfatalf(Logger *l, int errorcode, const char *fmt, ...);
extern void lmsgf(Logger *l, enum LogLevel ll, int errorcode, const char *fmt, ...);

#endif