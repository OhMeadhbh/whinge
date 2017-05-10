/* example_bloviate.c
**
** Copyright (c) 2017 Meadhbh S. Hamrick
** Released under a BSD license, see license.txt for details
**
** A program to test and demonstrate the use of bloviate() related
** functions.
*/

/* Macro Definitions */

/* File Includes */
#include "bloviate.h"

/* Typedefs, Structs, Unions, Enums */

/* Function Prototypes */
int _return_the_number_twelve( void );
void *_return_a_null( void );

/* Global Variable Declarations */

/* Function Definitions */

int main( int argc, char * argv [] ) {

  /* BLOVIATE is a package I wrote years ago to provide assert()
  ** without abort(). With a tiny bit of updating, I turned it into a
  ** lightweight testing function.
  **
  ** Let's say you're writing several functions you want to test; you
  ** *COULD* use something like CUnit or one of the other very decent
  ** testing frameworks. Or... you could just include the bloviate.c
  ** file in your package and use the bloviate() function to print out
  ** warnings when your free-form tests fail.
  **
  ** Here's an example. It *SHOULD* print out the error message when
  ** you run this program (I horked _return_the_number_twelve() to
  ** return an unexpected value.)
  */

  int expected = 12;
  int actual   = _return_the_number_twelve();
  bloviate( expected == actual, "Error in _return_the_number_twelve()" );

  /* Let's say you have a different function. And I'm going to try to
  ** make this one work correctly. Here's what happens:
  */

  bloviate( NULL == _return_a_null(), "Error in _return_a_null()." );

  /* This last call *SHOULD NOT* cause an error message to be emitted
  ** because the comparison in the first argument resolves to true.
  */

  /* Another thing you can do is include parameters to be printed in
  ** the error messages. We use a standard printf() format string, so
  ** if you know what to do with printf(), you know what to do here.
  */

  expected = 12;
  actual   = _return_the_number_twelve();
  bloviate( expected == actual,
            "Called _return_the_number_twelve(). Got %d, Expected %d",
            actual, expected );

  /* If you're lazy, you can do this:
  */

  bloviate( 12 == _return_the_number_twelve(),
            "DANGER WILL ROBINSON!. Got %d, Expected %d on file/line %s/%d",
            actual, expected, __FILE__, __LINE__ );

  /* Let's say you want to be lazy but you want to use the comparison to
  ** trigger some other action. bloviate() returns the number of bytes it
  ** prints out, so you can check to see if it print 0 bytes and assume the
  ** test was successful, if so. Note that this only works if you define
  ** an error message.
  */

  if( 0 != bloviate( 12 == _return_the_number_twelve(),
             "Still broken, dude. Got %d, Expected %d on file/line %s/%d",
             actual, expected, __FILE__, __LINE__ ) ) {
    printf( "I'm going to kick off some other process here...\n" );
  }

  /* For a time in the 1980s it was fashionable to print a timestamp
  ** on everything. Mostly to show how well your system handled the
  ** Y2K problem. Bloviate doesn't do this by default, but if you set
  ** the variable bloviate_time to a non-zero value, error messages
  ** are prepended with a timestamp.
  */

  bloviate_time = 1;
  bloviate( 0 != 0, "What do you mean zero doesn't equal zero?" );

  /* You can also have bloviate() send it's output to a file by
  ** changing the bloviate_file global variable.
  */

  bloviate_file = tmpfile();
  bloviate( 0 != 0, "This line *SHOULD* go into the temp file" );

  /* Usually people will set bloviate_file once and then forget it.
  ** You can return to the default behaviour by resetting
  ** bloviate_file to NULL.
  */

  bloviate_file = (FILE *)NULL;
  bloviate( 0 != 0, "You should see this line show up on STDERR" );
  
  /* And you can turn off the timestamping behaviour by resetting
  ** bloviate_time to zero.
  */

  bloviate_time = 0;
  bloviate( 0 != 0, "Hopefully you won't see a timestamp here." );

  return( 0 );
}

/* Function: _return_the_number_twelve()
**
** This function intentionally returns the wrong value. (Though I
** guess if we used base-11 numbers, this *WOULD* be correct.) 
*/
int _return_the_number_twelve() {
  return( 11 );
}

/* Function: _return_a_null()
**
** This is a sample function that returns a NULL void pointer.
*/
void *_return_a_null() {
  return( NULL );
}
