#include "hexl.h"

/*
 * Local Constants and Macros
 */

#define IS_EOL_CHAR(a) \
    ((a) == '\n' || (a) == '\r')

#define IS_COMMENT_CHAR(a) \
    ((a) == '#')

#define IS_BLANK(a) \
    ((a) == ' '     \
    || (a) == '\t'  \
    || (a) == '\n'  \
    || (a) == '\v'  \
    || (a) == '\f'  \
    || (a) == '\r')

#define IS_HEXDIGT(a)              \
    (((a) >= '0' && (a) <= '9')    \
    || ((a) >= 'A' && (a) <= 'F')  \
    || ((a) >= 'a' && (a) <= 'f'))

/*
 * Private Routines
 */



/*
 * Public Entry Points
 */

int hexl_encode(int cnt, const char *src, char *dst) {

    char ch, buf[2];
    int i, is_cmmt;

    if (cnt < 1)
        goto _abort;

    for (i = 0; i < cnt; i++) {
        ch = *(src + i);
        /* checks whether the current character
           belongs to a comment... */
        if (is_cmmt) {
            if (IS_EOL_CHAR(ch))
                is_cmmt = 0;
            continue;
        }
        if (IS_COMMENT_CHAR(ch)) {
            is_cmmt = 1;
            continue;
        }
        if (IS_BLANK(ch))
            continue;
    }

    return i;

_abort:
    return -1;

}

int hexl_decode(int cnt, const char *src, char *dst) {

    return 0;

}

