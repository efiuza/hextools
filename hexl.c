#include "hexl.h"

/*
 * Local Constants and Macros
 */

#define COMMENT_CHAR '#'

#define IS_EOL_CHAR(ch) \
    ((ch) == '\n' || (ch) == '\r')

#define IS_COMMENT_CHAR(ch) \
    ((ch) == COMMENT_CHAR)

#define IS_BLANK_CHAR(ch) \
    ((ch) == ' '          \
    || (ch) == '\t'       \
    || (ch) == '\n'       \
    || (ch) == '\r'       \
    || (ch) == '\v'       \
    || (ch) == '\f')

#define IS_HEXDIGT_CHAR(ch)          \
    (((ch) >= '0' && (ch) <= '9')    \
    || ((ch) >= 'A' && (ch) <= 'F')  \
    || ((ch) >= 'a' && (ch) <= 'f'))

#define HEX2BIN(ch)                 \
    ((ch) >= '0' && (ch) <= '9'     \
    ? (ch) - '0'                    \
    : ((ch) >= 'A' && (ch) <= 'F'   \
      ? (ch) - 'A' + 10             \
      : ((ch) >= 'a' && (ch) <= 'f' \
        ? (ch) - 'a' + 10           \
        : 0)));

#define GET_COMMENT_STATE(st) \
    ((st) & 1)

#define SET_COMMENT_STATE(st, cmmt) \
    ((st) = (st) | ((cmmt) & 1))

/*
 * Private Routines
 */



/*
 * Public Entry Points
 */

int
hexl_encode(
    int cnt,
    const char *src,
    char *dst,
    int *rd,
    int *wrt,
    int *st) {

    unsigned char ch, _ch;
    int r, s, i, j, is_cmmt;

    /* Initialize locals... */
    r       = 1;
    s       = *st;
    is_cmmt = GET_COMMENT_STATE(s);

    for (i = 0, j = 0; i < cnt; i++) {
        ch = (unsigned char) *(src + i);
        /* Checks whether the current character
           belongs to a comment section... */
        if (is_cmmt) {
            if (IS_EOL_CHAR(ch))
                is_cmmt = 0;
            /* On windows, line endings are marked
               with two characteres (CR + LF). The
               second one can be ignored once it is
               also considered a blank character. */
            continue;
        }
        if (IS_COMMENT_CHAR(ch)) {
            is_cmmt = 1;
            continue;
        }
        if (IS_BLANK_CHAR(ch))
            continue;
        if (IS_HEXDIGIT_CHAR(ch) && ++i < cnt) {
            _ch = (unsigned char) *(src + i);
            if (IS_HEXDIGIT_CHAR(_ch)) {
                ch = (HEX2BIN(ch) << 4) | HEX2BIN(_ch);
                *(dst + j++) = (char)ch;
                continue;
            }
        }
        /* If execution reaches this section of code
           the source buffer has invalid characters
           and the function should be terminated
           indicating an error on return. */
        r = 0;
        break;
    }

    /* Update state... */
    SET_COMMENT_STATE(s, is_cmmt);

    /* Update references... */
    *rd  = i;
    *wrt = j;
    *st  = s;

    return r;

}

int hexl_decode(int cnt, const char *src, char *dst) {

    return 0;

}

