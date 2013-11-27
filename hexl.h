#ifndef _HEXL_H
#define _HEXL_H

/**
 * Interface
 */

/* @return
 *     Returns the number of bytes written to the destination buffer.
 * @description
 *     Fills the destination buffer with the binary representation of
 *     the source buffer ASCII encoded hexadecimal contents. The
 *     destination buffer must be at least half the size of the source
 *     buffer.
 */
int hexl_encode(int count, const char *source, char *destination);

/* @return
 *     Returns the number of bytes written to the destination buffer.
 * @description
 *     Fills the destination buffer with the ASCII encoded hexadecimal
 *     representation of the source buffer contents. The destination
 *     buffer must be twice as big as the source buffer.
 */
int hexl_decode(int count, const char *source, char *destination);

#endif

