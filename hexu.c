#include <stdio.h>
#include <string.h>
#include "hexl.h"
#include "hexu.h"

/*
 * Local Definitions
 */

#define BUFFER_SIZE 32

/*
 * Implementation
 */

int hexu_encode(const char *ifn, const char *ofn, struct hexu_stat *stat) {

    char *ibufp, ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE];
    int rd, wr, cnt, ret, diff;
    int pos = 0, result;
    struct hexu_stat st;

    FILE *ifp, *ofp;
    size_t frd, fwr, fcnt;

    /* Initialize statistics structure... */
    /* ... */
    memset(&st, 0, sizeof(struct hexu_stat));

    /* Set initial result... */
    result = HEXU_OK;

    /* Open input file... */
    ifp = fopen(ifn, "rb");
    if (ifp == NULL) {
        result = HEXU_EBADFR;
        goto _exit;
    }

    /* Open output file... */
    ofp = fopen(ofn, "wb");
    if (ofp == NULL) {
        result = HEXU_EBADFW;
        goto _exit_close_input;
    }

    /* ibufp starts pointing to the begining
       of the input buffer... */
    ibufp = ibuf;
    cnt = BUFFER_SIZE;
    diff = 0;

    while ((rd = (int)fread(ibufp, 1, cnt, ifp)) > 0) {

        if (rd != cnt) {
            if (ferror(ifp)) {
                result = HEXU_EIOR;
                goto _exit_close_both;
            }
            cnt = rd;
        }

        if (diff > 0)
            cnt += diff;

        ret = hexl_encode(cnt, ibuf, obuf, &rd, &wr);

        /* update statistics... */
        /* ... */

        /* check return status... */
        if (ret != HEXL_OK && (ret != HEXL_NOBUFS || rd < 0)) {
            result = ret == HEXL_EILSEQ ? HEXU_EILSEQ
              : (ret == HEXL_EINVAL ? HEXU_EINVAL
                : (ret == HEXL_ENOBUFS ? HEXU_NOBUFS
                  : HEXU_EFAULT));
            goto _exit_close_both;
        }

        /* Update diff (difference between what
           has been supplied and what has actually
           been read) and move remaining content
           to the begining of buffer... */
        diff = cnt - rd;
        if (rd > 0 && diff > 0)
            memmove(ibuf, ibuf + rd, diff);

        if (wr > 0) {
            if (fwrite(obuf, 1, wr, ofp) != wr) {
                result = HEXU_EIOW;
                goto _exit_close_both;
            }
        }

        if (feof(ifp))
            break;

    }

_exit_update_stat:
    /* ... */

_exit_close_both:
    fclose(ofp);

_exit_close_input:
    fclose(ifp);

_exit:
    return result;

}


