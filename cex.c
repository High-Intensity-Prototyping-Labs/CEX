/**
 * @file cex.c
 * @brief Top-level source file for CEX.
 */

#include "cex.h"


/**
 * @brief Locates the last occurence of substring `needle` in string `haystack`.
 *
 * The terminating null bytes are not compared.
 *
 * @param[in] haystack The string to search for the last occurrence of `needle` in.
 * @param[in] needle The substring to find within the string `haystack`.
 * @return char* A pointer to the beginning of the substring or NULL if the substring is not found.
 */
char *strlstr(const char *haystack, const char *needle) {
        size_t haylen;
        size_t neelen;
        const char *cursor;

        haylen = strlen(haystack);
        neelen = strlen(needle);

        /* Exclude case when haystack is zero-length */
        if(haylen == 0) {
                return NULL;
        }

        /* As per strstr(3) man page, empty 'needle' argument returns 'haystack' */
        if(neelen == 0) {
                return (char*)haystack;
        }

        /* Exclude case in which needle is longer than haystack */
        if(haylen < neelen) {
                return NULL;
        }

        cursor = &haystack[haylen-neelen-1];
        while(cursor >= haystack) {
                if(strncmp(cursor, needle, neelen) == 0) {
                        return (char*)cursor;
                }

                cursor--;
        }

        /* None found */
        return NULL;
}

#ifdef CEX_USE_NAMESPACE
struct cex cex = {
        .strlstr = strlstr,
};
#endif
