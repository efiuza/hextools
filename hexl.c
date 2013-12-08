#include "hexl.h"

/*
 * Local Constants and Macros
 */

#define HEXL_OK      0
#define HEXL_EILSEQ  1
#define HEXL_EINVAL  2
#define HEXL_ENOBUFS 3

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

#define IS_HEXDIGIT_CHAR(ch)         \
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
        : 0)))

/*
 * Private Routines
 */



/*
 * Public Entry Points
 */

int
hexl_encode(int cnt, const char *src, char *dst, int *rd, int *wr) {

    unsigned char ch, _ch;
    int i, j, cmmt, is_cmmt, result;

    /* Initialize locals... */
    result = HEXL_OK;
    is_cmmt = 0;

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
            cmmt = i;
            continue;
        }
        if (IS_BLANK_CHAR(ch))
            continue;
        if (IS_HEXDIGIT_CHAR(ch)) {
            if (++i < cnt) {
                _ch = (unsigned char) *(src + i);
                if (IS_HEXDIGIT_CHAR(_ch)) {
                    ch = (HEX2BIN(ch) << 4) | HEX2BIN(_ch);
                    *(dst + j++) = (char)ch;
                    continue;
                }
                result = HEXL_EILSEQ;
                break;
            }
            i--;
            result = HEXL_ENOBUFS;
            break;
        }
        /* If execution reaches this section of code
           the source buffer has invalid characters
           and the function should be terminated
           indicating the error on return. */
        result = HEXL_EINVAL;
        break;
    }

    /* Check if buffer ended inside a comment
       section. In this case, the source pointer
       must point back to the comment character
       and return to the user an empty buffer
       indicator. */ 
    if (is_cmmt) {
        i = cmmt;
        result = HEXL_ENOBUFS;
    }

    /* Update references... */
    *rd = i;
    *wr = j;

    return result;

}

int hexl_decode(int cnt, const char *src, char *dst) {

    return 0;

}

