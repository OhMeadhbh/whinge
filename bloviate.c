/* bloviate.c
**
** Copyright (c) 1985, 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** This file defines the implementation of the BLOVIATE assertion
** functions. For information about the API, please see bloviate.h.
*/

/* Macro Definitions */
#define _C_BLOVIATE

/* File Includes */
#include "bloviate.h"
#include <time.h>

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */
static int _bloviate_log( char *time, char *format, va_list ap );
static void _set_time( void );

/* Variable Declarations */
int bloviate_time = 0;
FILE * bloviate_file = (FILE *) NULL;
int (*bloviate_log)( char * d, char *f, va_list ap ) = _bloviate_log;

static char _timebuffer[ 20 ];

/* Function Definitions */
int bloviate( int inequality, char * format, ... ) {
  int (*_log)( char * d, char * f, va_list ap ) = bloviate_log;
  va_list argp;

  va_start( argp, format );

  if( _log != NULL ) {
    if( ! inequality ) {
      _set_time();
      return( bloviate_log( _timebuffer, format, argp ) );
    } else {
      return( 0 );
    }
  } else {
    return( -1 );
  }
}

static void _set_time( ) {
  time_t t;

  if( bloviate_time ) {
    time( &t );
    strftime( _timebuffer, 20, "%Y-%m-%d %H:%M:%S", localtime( & t ) );
  } else {
    _timebuffer[0] = '\0';
  }
}

static int _bloviate_log( char *time, char *format, va_list ap ) {
  FILE * _out = (NULL == bloviate_file) ? stderr : bloviate_file;
  int bytes_print = 0;

  bytes_print = fprintf( _out, ";" );

  if( bloviate_time && ( NULL != time ) ) {
    bytes_print += fprintf( _out, "%s ", time );
  }

  bytes_print += vfprintf( _out, format, ap );

  bytes_print += fprintf( _out, "\n" );

  return( bytes_print );
}
