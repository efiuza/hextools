#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexu.h"

/*
 * Macros & Definitions
 */

#define MODE_ENCODE 0
#define MODE_DECODE 1

/* Messages */

#define MSG_STATS                      \
    "Stats:\n"                         \
    " # bytes processed......: %d\n"   \
    " # lines processed......: %d\n"   \
    " # last line offset.....: %d\n"   \
    " # last line byte offset: %d\n\n"

/* Error Messages */

#define EMSG_BAD_USAGE \
    "Usage message...\n"

#define EMSG_OPENING_INPUT \
    "Error opening input file: \"%s\"\n"

#define EMSG_READING_INPUT \
    "Error reading input file (#%04d)...\n"

#define EMSG_OPENING_OUTPUT \
   "Error opening output file: \"%s\"\n" 

#define EMSG_WRITING_OUTPUT \
    "Error writing output file (#%04d)...\n"

#define EMSG_PROCESSING_INPUT \
    "Error processing input file (#%04ld)...\n"

#define EMSG_BUFFER_NARROW \
    "Sorry, insufficient read buffer...\n"

#define EMSG_UNKNOWN \
    "Sorry, an unknown error has just happened... (#%04d)\n"

/*
 * Main Program Entry Point
 */

int main(int argc, char *argv[]) {

    int mode = MODE_ENCODE; /* encode/decode switch... */
    int res; /* result of encoding/decoding... */
    struct hexu_stat st; /* stats from encoding... */

    /* Parse application arguments... */
    /* ... */
    if (argc < 3) {
        fputs(EMSG_BAD_USAGE, stderr);
        goto _exit_failure;
    }

    if (mode == MODE_ENCODE) {
        /* perform encoding... */
        res = hexu_encode(
            argv[1],
            argv[2],
            &st
        );
        /* print stats... */
        fprintf(
            stdout,
            MSG_STATS,
            st.nr_chars,
            st.nr_lines,
            st.ln_init,
            st.ln_cur
        );
        /* check return value... */
        if (res != HEXU_OK) {
            switch (res) {
                case HEXU_ENOBUFS:
                    fputs(EMSG_BUFFER_NARROW, stderr);
                    break;
                default:
                    fprintf(stderr, EMSG_UNKNOWN, res);
                    break;
            }
            goto _exit_failure;
        }
    }

_exit_success:
    return EXIT_SUCCESS;

_exit_failure:
    return EXIT_FAILURE;

}

