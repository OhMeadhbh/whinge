/* hexdump.h
**
** Copyright (c) 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** This file containst the interface to the HEXDUMP implementation. To
** use it, simply pass a pointer and a length to the hexdump()
** function and it will emit an old-school style hexdump on standard
** output.
*/

/* Macro Definitions */
#ifndef _H_HEXDUMP
#define _H_HEXDUMP

/* File Includes */
#include <stdio.h>

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */
int hexdump( void * data, unsigned int length );
int fhexdump( FILE * file, void * data, unsigned int length );

/* Variable Declarations */

#endif /* _H_HEXDUMP */

