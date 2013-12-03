#ifndef _HEXL_H
#define _HEXL_H

/**
 * Interface
 */

/* @return
 *     Returns 1 on success, 0 on error.
 * @description
 *     Fills the destination buffer with the binary representation of
 *     the source buffer ASCII encoded hexadecimal contents. The
 *     destination buffer must be at least half the size of the source
 *     buffer. The integer references passed as arguments are updated
 *     with the amount of bytes read from and written to the source and
 *     destination buffers respectively. The last one preserves the state
 *     of the encoding process and is useful for segmented encodings.
 *     On start its value should be 0.
 */
int
hexl_encode(
    int count,
    const char *source,
    char *destination,
    int *read,
    int *written,
    int *state
);

/* @return
 *     Returns the number of bytes written to the destination buffer.
 * @description
 *     Fills the destination buffer with the ASCII encoded hexadecimal
 *     representation of the source buffer contents. The destination
 *     buffer must be twice as big as the source buffer.
 */
int hexl_decode(int count, const char *source, char *destination);

#endif

