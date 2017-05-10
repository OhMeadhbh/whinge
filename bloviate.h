/* bloviate.h
**
** Copyright (c) 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** This  file   defines  the  interface  to   the  BLOVIATE  assertion
** functions. BLOVIATE  is not  a testing framework;  it's more  of an
** implementation of  assert() that doesn't call  abort(). It's useful
** for  testing if you're  looking for  something more  free-form than
** what's typically provided by a test framework.
**
** BLOVIATE provides the function:
**
**   int bloviate( int inequality, char *format, ... )
**
** If the inequality  parameter is false (zero), it  prints the format
** message to  STDERR, using the variadic arguments  like printf(). In
** this sense, bloviate is like a conditional printf().
**
** Like printf(), bloviate() returns the number of characters printed.
**
** Bloviate  prints  to  STDERR  by  default,  but  users  can  assign
** bloviate_file to point to  some other FILE structure (either stdout
** or one created with the fopen() function.
**
** bloviate() will prepend an ISO 8601 style combined date/time string
** to  the  messages it  prints  if  you  assing the  global  variable
** bloviate_time to be non-zero.
**
** bloviate_log  is a  pointer to  a  function that  takes a  timedate
** string, a  format string and varargs. Developers  can redefine this
** function to do something other than log messages to a FILE.
*/

/* Macro Definitions */
#ifndef _H_BLOVIATE
#define _H_BLOVIATE

/* File Includes */
#include <stdio.h>
#include <stdarg.h>

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */
int bloviate( int inequality, char * format, ... );

/* Variable Declarations */
int bloviate_time;
FILE *bloviate_file;
int (*bloviate_log)( char * time, char * format, va_list ap );

#endif /* _H_BLOVIATE */

