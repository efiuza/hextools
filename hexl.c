#include "hexl.h"

/*
 * Local Constants and Macros
 */

#define CHR_COMMENT '#'
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
    return 0;
}

int hexl_decode(int cnt, const char *src, char *dst, int opt) {

    char ch, ibuf[IBUFSZ];
    int i;

    if (i < 1)
        goto _failure;

    for (i = 0; i < cnt; i++) {
        ch = *(src + i);
        if (IS_BLANK(ch))
            continue;
    }

    return i;

    _failure:
    return 0;

}

