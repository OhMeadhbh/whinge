/* example_hexdump.c
**
** Copyright (c) 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** A program to test and demonstrate the use of hexdump() related
** functions.
*/

/* Macro Definitions */

/* File Includes */
#include "hexdump.h"
#include <stdio.h>

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */

/* Global Variable Declarations */

char * test_string_array [] = {
  "hello",
  "doctor",
  "yesterday",
  "tomorrow"
};

/* Function Definitions */

int main( int argc, char * argv [] ) {
  int count;

  printf( "Printing memory from around %08X\n", (unsigned int) test_string_array );
  count = hexdump( test_string_array, 32 );
  printf( "I think I printed %d bytes.\n\n", count );

  printf( "Printing memory from around %08X\n", (unsigned int) test_string_array );
  count = hexdump( test_string_array[0], 17 );
  printf( "I think I printed %d bytes.\n\n", count );

  fprintf( stderr, "Printing memory from around %08X\n", (unsigned int) test_string_array );
  count = fhexdump( stderr, test_string_array, 32 );
  fprintf( stderr, "I think I printed %d bytes.\n\n", count );

  fprintf( stderr, "Printing memory from around %08X\n", (unsigned int) test_string_array );
  count = fhexdump( stderr, test_string_array[0], 17 );
  fprintf( stderr, "I think I printed %d bytes.\n\n", count );

  return( 0 );
}
