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

        /* Exclude case in which needle is longer than haystack */
        if(haylen < neelen) {
                return NULL;
        }

        cursor = &haystack[haylen-neelen-1];
        while(cursor > haystack) {
                if(strcmp(cursor, needle) == 0) {
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
