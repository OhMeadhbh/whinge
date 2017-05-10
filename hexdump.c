/* hexdump.c
**
** Copyright (c) 1985, 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** This file defines the implementation of the HEXDUMP functions. For
** more information, see hexdump.h.
*/

/* Macro Definitions */
#define _C_HEXDUMP

/* File Includes */
#include "hexdump.h"

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */

/* Variable Declarations */

/* Function Definitions */

int hexdump( void * data, unsigned int length ) {
  return( fhexdump( stdout, data, length ) );
}

int fhexdump( FILE * file, void * data, unsigned int length ) {
  unsigned char * cdata = (unsigned char *) data;
  unsigned char buf[ 16 ];
  unsigned int i;
  unsigned int bytes_written = 0;

  for( i = 0; i < length; i++ ) {
    if( 0 == ( i % 16 ) ) {
      bytes_written += fprintf( file, "%08X: ", (unsigned int) & cdata[ i ] );
    }
    bytes_written += fprintf( file, "%02X ", cdata[ i ] );
    buf[ i % 16 ] =
      ( ( cdata[ i ] > 31 ) && ( cdata[ i ] < 128 ) ) ? cdata[ i ] : '.';
    if( 15 == ( i % 16 ) ) {
      bytes_written += fprintf( file, "|%16.16s|\n", buf );
    }
  }

  for( ; 0 != ( i % 16 ); i++ ) {
    buf[ i % 16 ] = ' ';
    bytes_written += fprintf( file, "   " );
  }

  if( 0 != ( length % 16 ) ) {
    bytes_written += fprintf( file, "|%16.16s|\n", buf );
  }

  return( bytes_written );
}
