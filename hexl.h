#ifndef _HEXL_H
#define _HEXL_H

/**
 * Constants
 */

#define HEXL_RWSZ16  0
#define HEXL_RWSZ32  0
#define HEXL_RWSZ64  0
#define HEXL_GRPSZ1  0
#define HEXL_GRPSZ2  0
#define HEXL_GRPSZ4  0
#define HEXL_GRPSZ8  0
#define HEXL_ILEND   0
#define HEXL_IBEND   0
#define HEXL_DEFAULT (HEXL_RWSZ16 | HEXL_GRPSZ1 | HEXL_ILEND)

/**
 * Interface
 */

/* @description Converts the hexadecimal content of a buffer into binary.
 */
int hexl_encode(int count, const char *source, char *destination, int options);

/* @description Converts the binary content of a buffer into an hexadecimal representation.
 */
int hexl_decode(int count, const char *source, char *destination, int options);

#endif
