#ifndef _HEXU_H
#define _HEXU_H

/*
 * Interface
 */

#define HEXU_OK      0
#define HEXU_ENOBUFS 1
#define HEXU_EILSEQ  2
#define HEXU_EINVAL  3
#define HEXU_EBADFR  4
#define HEXU_EBADFW  5
#define HEXU_EIOR    6
#define HEXU_EIOW    7
#define HEXU_ENOTSUP 8
#define HEXU_EFAULT  9

struct hexu_stat {
    int nr_chars;
    int nr_lines;
    int ln_init;
    int ln_cur;
};

struct hexu_opt {
    short grpsz;
    short lnsz;
};

int
hexu_encode(
    const char *infile,
    const char *outfile,
    struct hexu_stat *stat
);

int
hexu_decode(
    const char *infile,
    const char *outfile,
    struct hexu_opt *opts
);

#endif

