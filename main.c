#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexl.h"

#define BUFFER_SIZE 100

int main(int argc, char *argv[]) {

    FILE *ifp, *ofp;
    char ifn[FILENAME_MAX], ofn[FILENAME_MAX];
    char ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE];
    int cnt, rd, wrt, st;

    /* Parse applications arguments... */
    /* ... */

    /* Open input file... */
    ifp = fopen(ifn, "rb");
    if (ifp == NULL) {
        printf("Error opening input file: \"%s\"\n", ifn);
        return EXIT_FAILURE;
    }

    /* Open output file... */
    ofp = fopen(ofn, "wb");
    if (ofp == NULL) {
        printf("Error openig output file: \"%s\"\n", ofn);
        fclose(ifp);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

