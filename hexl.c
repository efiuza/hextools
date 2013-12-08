/*
 * Local Constants and Macros
 */

#define HEXL_OK      0
#define HEXL_EILSEQ  1
#define HEXL_EINVAL  2
#define HEXL_ENOBUFS 3

#define CHAR_COMMENT '#'

#define IS_CHAR_EOL(ch) \
    ((ch) == '\n' || (ch) == '\r')

#define IS_CHAR_COMMENT(ch) \
    ((ch) == CHAR_COMMENT)

#define IS_CHAR_BLANK(ch) \
    ((ch) == ' '          \
    || (ch) == '\t'       \
    || (ch) == '\n'       \
    || (ch) == '\r'       \
    || (ch) == '\v'       \
    || (ch) == '\f')

#define IS_CHAR_HEXDIGIT(ch)         \
    (((ch) >= '0' && (ch) <= '9')    \
    || ((ch) >= 'A' && (ch) <= 'F')  \
    || ((ch) >= 'a' && (ch) <= 'f'))

#define EVAL_HEXDIGIT(ch)           \
    ((ch) >= '0' && (ch) <= '9'     \
    ? (ch) - '0'                    \
    : ((ch) >= 'A' && (ch) <= 'F'   \
      ? (ch) - 'A' + 10             \
      : ((ch) >= 'a' && (ch) <= 'f' \
        ? (ch) - 'a' + 10           \
        : 0)))

/*
 * State Control...
 */

#define IS_STATE_INIT(sw) \
    ((sw) == 0)

#define IS_STATE_OCTET(sw) \
    ((sw) == 1)

#define IS_STATE_COMMENT(sw) \
    ((sw) == 2)

#define SET_STATE_INIT(sw) \
    ((sw) = 0)

#define SET_STATE_OCTET(sw) \
    ((sw) |= 1)

#define SET_STATE_COMMENT(sw) \
    ((sw) |= 2)

#define CLEAR_STATE_OCTET(sw) \
    ((sw) &= -2)

#define CLEAR_STATE_COMMENT(sw) \
    ((sw) &= -3)

/*
 * Public Code Entry Points
 */

int
hexl_encode(int cnt, const char *src, char *dst, int *rd, int *wr) {

    unsigned char buf, octet;
    int i, j, tmp, status, result;

    /* Initialize locals... */
    result = HEXL_OK;
    SET_STATE_INIT(status);

    for (i = 0, j = 0; i < cnt; i++) {
        buf = (unsigned char) *(src + i);
        if (IS_STATE_COMMENT(status)) {
            if (IS_CHAR_EOL(buf))
                CLEAR_STATE_COMMENT(status);
            /* On windows, line endings are marked
               with two characteres (CR + LF). The
               second one can be ignored once it is
               also considered a blank character. */
            continue;
        } else if (IS_STATE_INIT(status) && IS_CHAR_COMMENT(buf)) {
            SET_STATE_COMMENT(status);
            tmp = i;
            continue;
        } else if (IS_STATE_INIT(status) && IS_CHAR_BLANK(buf)) {
            continue;
        } else if ((IS_STATE_INIT(status) || IS_STATE_OCTET(status))
            && IS_CHAR_HEXDIGIT(buf)) {
            buf = EVAL_HEXDIGIT(buf);
            if (IS_STATE_OCTET(status)) {
                CLEAR_STATE_OCTET(status);
                octet = (octet << 4) | buf;
                *(dst + j++) = (char)octet;
            } else {
                SET_STATE_OCTET(status);
                octet = buf;
            }
            continue;
        }
        result = IS_STATE_OCTET(status)
            ? HEXL_EILSEQ
            : HEXL_EINVAL;
        break;
    }

    if ((IS_STATE_OCTET(status) || IS_STATE_COMMENT(status)) && i >= cnt) {
        i = IS_STATE_OCTET(status)
            ? i - 1
            : tmp;
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

