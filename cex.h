/**
 * @file cex.h
 * @brief Top-level header for CEX
 */

#ifndef CEX_H
#define CEX_H

/* POSIX Dependencies */
#include <string.h>

/* CEX SETTINGS */
/* #define CEX_USE_NAMESPACE */ /* Enable if cex.* convention wanted */

#ifdef CEX_USE_NAMESPACE
struct cex {
        /** Find the last occurence of a substring within a string */
        char* (*strlstr)(const char*, const char*);
};
extern struct cex cex;
#else
/** Find the last occurence of a substring within a string */
char* strlstr(const char*, const char*);
#endif

#endif // CEX_H
