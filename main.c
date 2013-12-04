#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexl.h"

#define BUFFER_SIZE 100

/* Error Messages */

#define ERROR_OPENING_INPUT \
    "Error opening input file: \"%s\"\n"

#define ERROR_OPENING_OUTPUT \
   "Error opening output file: \"%s\"\n" 

/*
 * Main Program Entry Point
 */

int main(int argc, char *argv[]) {

    FILE *ifp, *ofp;
    char ifn[FILENAME_MAX], ofn[FILENAME_MAX];
    char ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE];
    int cnt, rd, wrt, st;

    /* Parse application arguments... */
    /* ... */

    /* Open input file... */
    ifp = fopen(ifn, "rb");
    if (ifp == NULL) {
        printf(ERROR_OPENING_INPUT, ifn);
        goto abort_dft;
    }

    /* Open output file... */
    ofp = fopen(ofn, "wb");
    if (ofp == NULL) {
        printf(ERROR_OPENING_OUTPUT, ofn);
        goto abort_alt1;
    }

success:
    return EXIT_SUCCESS;

abort_alt2:
    fclose(ofp);

abort_alt1:
    fclose(ifp);

abort_dft:
    return EXIT_FAILURE;

}

