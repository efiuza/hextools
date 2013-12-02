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
    || (ch) == '\v'       \
    || (ch) == '\f'       \
    || (ch) == '\r')

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

/*
 * Private Routines
 */



/*
 * Public Entry Points
 */

int hexl_encode(int cnt, const char *src, char *dst) {

    char ch, buf;
    int i, is_cmmt;

    for (i = 0; i < cnt; i++) {
        ch = *(src + i);
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
        if (IS_HEXDIGIT_CHAR(ch)) {
            buf = HEX2BIN(ch) << 4;
        }
        break;
    }

    return i;

}

int hexl_decode(int cnt, const char *src, char *dst) {

    return 0;

}

