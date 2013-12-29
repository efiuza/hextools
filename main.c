#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexu.h"

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
    "Sorry, an unknown error has just happened...\n"

/*
 * Main Program Entry Point
 */

int main(int argc, char *argv[]) {

    /* Parse application arguments... */
    /* ... */
    if (argc < 3) {
        fputs(EMSG_BAD_USAGE, stderr);
        goto abort_dft;
    }
    strcpy(ifn, argv[1]);
    strcpy(ofn, argv[2]);


_exit_success:
    return EXIT_SUCCESS;

_exit_failure:
    return EXIT_FAILURE;

}

