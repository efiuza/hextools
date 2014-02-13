#include <stdio.h>
#include <string.h>
#include "hexl.h"
#include "hexu.h"

/*
 * Local Definitions
 */

#define INPUT_BUFFER 8192
#define OUTPUT_BUFFER (INPUT_BUFFER / 2)

/*
 * Implementation
 */

int hexu_encode(const char *ifn, const char *ofn, struct hexu_stat *stat) {

    char ibuf[INPUT_BUFFER], obuf[OUTPUT_BUFFER], *ibp;
    int rd, wr, cnt, rem, ret, result;

    int i, ln, lns, chs;
    char _ch, ch;

    FILE *ifp, *ofp;

    /* Initialize result... */
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

    /* Initial parameters... */
    ibp = ibuf;
    cnt = INPUT_BUFFER;
    rem = 0;
    chs = 0;
    lns = 0;
    ln  = 0;
    ch  = 0;

    while ((rd = (int)fread(ibp, 1, cnt, ifp)) > 0) {

        if (rd != cnt) {
            if (rd > cnt || ferror(ifp)) {
                result = HEXU_EIOR;
                goto _exit_close_both;
            }
            cnt = rd;
        }

        if (rem > 0) {
            cnt += rem;
            /* data consistency check... */
            if (cnt > INPUT_BUFFER) {
                result = HEXU_EFAULT;
                goto _exit_close_both;
            }
        }

        ret = hexl_encode(cnt, ibuf, obuf, &rd, &wr);

        /* data consistency check... */
        if (rd < 0 || rd > cnt) {
            result = HEXU_EFAULT;
            goto _exit_close_both;
        }

        /* update statistics before checking status... */
        if (rd > 0) {
            for (i = 0; i < rd; i++) {
                _ch = ch;
                ch = *(ibuf + i);
                if (ch != '\n' && ch != '\r')
                    continue;
                if (ch != '\n' || _ch != '\r')
                    lns++;
                ln = chs + i + 1;
            }
            chs += i;
        }

        /* check return status... */
        if (ret != HEXL_OK && (ret != HEXL_ENOBUFS || rd < 1)) {
            result = ret == HEXL_ENOBUFS ? HEXU_ENOBUFS
              : (ret == HEXL_EILSEQ ? HEXU_EILSEQ
                : (ret == HEXL_EINVAL ? HEXU_EINVAL
                  : HEXU_EFAULT));
            goto _exit_close_both;
        }

        /* update rem (remainder from the last encode
           operation) and move remaining content
           to the begining of input buffer... */
        rem = cnt - rd;
        if (rd > 0 && rem > 0)
            memmove(ibuf, ibuf + rd, rem);

        /* update fread parameters... */
        ibp = ibuf + rem;
        cnt = INPUT_BUFFER - rem;

        if (wr > 0) {
            if (fwrite(obuf, 1, wr, ofp) != wr) {
                result = HEXU_EIOW;
                goto _exit_close_both;
            }
        }

        if (feof(ifp))
            break;

    }

_exit_close_both:
    fclose(ofp);

_exit_close_input:
    fclose(ifp);

    /* update stat reference... */
    stat->nr_chars = chs;
    stat->nr_lines = lns;
    stat->ln_init  = ln;
    stat->ln_cur   = chs - ln;

_exit:
    return result;

}


