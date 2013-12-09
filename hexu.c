#include <stdio.h>
#include <string.h>
#include "hexl.h"
#include "hexu.h"

/*
 * Local Definitions
 */

#define BUFFER_SIZE 50

/*
 * Implementation
 */

int hexu_encode(const char *ifn, const char *ofn, struct hexu_stat *stat) {

    char ibuf[BUFFER_SIZE], obuf[BUFFER_SIZE];
    int rd, wr, cnt, ret, diff = 0;
    int pos = 0, eno = HEXU_OK;

    FILE *ifp, *ofp;
    size_t frd, fwr, fcnt = BUFFER_SIZE;

    /* Initialize stat structure... */
    /* ... */

    /* Open input file... */
    ifp = fopen(ifn, "rb");
    if (ifp == NULL) {
        eno = HEXU_EBADFR;
        goto _exit;
    }

    /* Open output file... */
    ofp = fopen(ofn, "wb");
    if (ofp == NULL) {
        eno = HEXU_EBADFW;
        goto _exit_close_input;
    }

    while ((frd = fread(ibuf + diff, 1, fcnt - diff, ifp)) > 0) {

        if (frd < fcnt - diff && ferror(ifp)) {
            eno = HEXU_EIOR;
            goto _exit_close_both;
        }

        cnt = diff + (int)frd;
        ret = hexl_encode(cnt, ibuf, obuf, &rd, &wr);

        /* Update file position... */
        pos += rd;

        switch (ret) {
            case HEXL_OK:
                break;
            case HEXL_ENOBUFS:
                if (rd > 0)
                    break;
                eno = HEXU_ENOBUFS;
                goto _exit_close_both;
            case HEXL_EILSEQ:
                eno = HEXU_EILSEQ;
                goto _exit_update_stat;
            case HEXL_EINVAL:
                eno = HEXU_EINVAL;
                goto _exit_update_stat;
            default:
                eno = HEXU_EFAULT;
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
            fwr = wr;
            if (fwrite(obuf, 1, fwr, ofp) != fwr) {
                eno = HEXU_EIOW;
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
    return eno;

}


