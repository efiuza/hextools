#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexl.h"

#define BUFFER_SIZE 50

/* Error Messages */

#define ERROR_BAD_USAGE \
    "Usage message...\n"

#define ERROR_OPENING_INPUT \
    "Error opening input file: \"%s\"\n"

#define ERROR_READING_INPUT \
    "Error reading input file (#%04d)...\n"

#define ERROR_OPENING_OUTPUT \
   "Error opening output file: \"%s\"\n" 

#define ERROR_WRITING_OUTPUT \
    "Error writing output file (#%04d)...\n"

#define ERROR_PROCESSING_INPUT \
    "Error processing input file (#%04ld)...\n"

#define ERROR_BUFFER_NARROW \
    "Sorry, insufficient read buffer...\n"

#define ERROR_UNKNOWN \
    "Sorry, an unknown error has just happened...\n"

/*
 * Main Program Entry Point
 */

int main(int argc, char *argv[]) {

    FILE *ifp, *ofp;
    char ifn[FILENAME_MAX], ofn[FILENAME_MAX];
    char ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE];
    int eno, diff, rt, rd, wr, cnt, frd, fwr;
    size_t lrd, lwr, lcnt, lpos;

    /* Parse application arguments... */
    /* ... */
    if (argc < 3) {
        fputs(ERROR_BAD_USAGE, stderr);
        goto abort_dft;
    }
    strcpy(ifn, argv[1]);
    strcpy(ofn, argv[2]);

    /* Open input file... */
    ifp = fopen(ifn, "rb");
    if (ifp == NULL) {
        fprintf(stderr, ERROR_OPENING_INPUT, ifn);
        goto abort_dft;
    }

    /* Open output file... */
    ofp = fopen(ofn, "wb");
    if (ofp == NULL) {
        fprintf(stderr, ERROR_OPENING_OUTPUT, ofn);
        goto abort_alt1;
    }

    diff = 0;
    lpos = 0;
    lcnt = BUFFER_SIZE;

    while ((lrd = fread(ibuf + diff, 1, lcnt - diff, ifp)) > 0) {
        if (lrd < lcnt - diff && (eno = ferror(ifp))) {
            fprintf(stderr, ERROR_READING_INPUT, eno);
            goto abort_alt2;
        }
        cnt = diff + (int)lrd;
        rt = hexl_encode(cnt, ibuf, obuf, &rd, &wr);
        lpos += rd;

        /* Update diff (difference between what
           has been supplied and what has actually
           been read) and move remaining content
           to the begining of buffer... */
        diff = cnt - rd;
        if (rd > 0 && diff > 0)
            memmove(ibuf, ibuf + rd, diff);

        if (rt == HEXL_EILSEQ || rt == HEXL_EINVAL) {
            fprintf(stderr, ERROR_PROCESSING_INPUT, lpos);
            goto abort_alt2;
        } else if (rt == HEXL_ENOBUFS) {
            if (rd < 1) {
                fputs(ERROR_BUFFER_NARROW, stderr);
                goto abort_alt2;
            }
        } else if (rt != HEXL_OK) {
            fputs(ERROR_UNKNOWN, stderr);
            goto abort_alt2;
        }

        if (wr > 0) {
            if (fwrite(obuf, 1, wr, ofp) != wr) {
                eno = ferror(ofp);
                fprintf(stderr, ERROR_WRITING_OUTPUT, eno);
                goto abort_alt2;
            }
        }
        if (feof(ifp))
            break;
    }

    fclose(ifp);
    fclose(ofp);

success:
    return EXIT_SUCCESS;

abort_alt2:
    fclose(ofp);
abort_alt1:
    fclose(ifp);
abort_dft:
    return EXIT_FAILURE;

}

