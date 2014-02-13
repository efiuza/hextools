#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexu.h"

/*
 * Macros & Definitions
 */

#define MODE_ENCODE 0
#define MODE_DECODE 1

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
        res = hexu_encode(argv[1], argv[2], &st);
        if (res != HEXU_OK) {
            fprintf(stderr, EMSG_UNKNOWN, res);
            goto _exit_failure;
        }
    }

_exit_success:
    return EXIT_SUCCESS;

_exit_failure:
    return EXIT_FAILURE;

}

