# Whinge

Whinge is a collection of simple c routines I find I use on a regular
basis. Rather than do the smart thing, which is compile them all into
a library and then reference the library, I just put them all here so
I can copy individual files into other projects.

## License

This package is released under a [BSD 3-clause license](license.txt).

## Building & Testing Whinge

At some point I should have an auto-tools generated make file so I can
be assured Whinge will compile on any GNU supported system. But I'm
lazy, and like I said, my way of dealing with dependency management is
just to ignore it and copy source code files directly into various
other packages. If you want to fork this package an add a more modern
Makefile, knock yourself out.

So the Makefile I have in this package now just builds the .o files,
unit tests and example programs (where appropriate.) To build things,
make sure you have a c-compiler and make installed. I'm assuming Make
knows how to pick the right $(CC) compiler. This makes all the .o's
and executables. If it doesn't work on Windows, it's your own damn
fault (live free or die.)

    make all

If you want to run all the tests, you can run this:

    make test

And if you want to remove all the files we generated with the previous
two commands, try this:

    make clean

## bloviate.c

I'm kind of a Test Driven Development (TDD) fan (I'm including BDD
and ATDD and <foo>DD in the TDD umbrella.) I like to write simple
programs to test an API before the API is completed, often before I
even start writing the API implementation. If you know how you're
going to use it, it helps you figure out what should be in the
programmers' interface.

I'm less of a fan of TDD packages. When I run tests, I usually want a
yes/no answer; I don't need an XML file that gets ingested into a
report that tells my boss what percentage of the API we've
tested. That's often bullshit. If your boss is pressuring you to get
daily progress on test coverage to the degree he needs to write a
report to send to your manager's manager, then there's something wrong
with your process. In my experience, it is extremely easy to lie about
coverage in such systems; your management should be focused on the
quality of your testing, not an abstract number which is simple to
game.

Kent Beck's <foo>Unit pattern is nice. But I find I often don't use
the whole setup-test-test-test-teardown process as much as you
think. My tests tend to be setup-test.

So... I find I prefer having a set of primitives that test for
equality and spit out a message if something's unexpected. You may not
like this style of building tests, and that's entirely okay. When I
wrote the original version of bloviate.c in the 1980s, I was looking
for something like assert() that didn't call abort().

To use bloviate.c in a test program, include [bloviate.h](bloviate.h)
in your C program:

    #include "bloviate.h"

Then you can do things like this:

    unsigned int expected = 4;
    unsigned int actual = function_under_test();
    bloviate( actual == expected, "function_under_test() failed" );

This snippit calls the function function_under_test() and compares its
result to 4. If it's not true, it prints out the message
"function_under_test() failed". It's that simple.

But I found a lot of what I wanted in reports was to see the actual
and expected values, I modified it so it does varargs and passes them
to the printf, so you can do this:

    unsigned int e = 4;
    unsigned int a = function_under_test();
    bloviate( actual == expected, "expected %d, got %d", e, a );

I use the standard printf() library, so anything that works with a
printf() should work with bloviate().

A typical pattern for using bloviate() is when you're building a test
program for package. If the package under test is in foo.c and foo.h,
and the test program is called test_foo.c, these are example commands
that *should* work to compile the test program:

    cc -c -o test_foo.o test_foo.c
    cc -o test_foo blovate.o test_foo.o

And I almost forgot to mention, bloviate.c uses global variables to
define it's behaviour, so there are a few things you can change if you
need to.

By default, bloviate() prints on STDERR. If you don't like that, you
can set the global variable bloviate_file to any other FILE data
structure (like stdout or some other file you open.)

bloviate() can print out the date and time if you set the global
variable bloviate_time to a non-zero value. (By default it does not
print out time and date.)

If you REALLY want to change the behaviour of bloviate(), the global
variable bloviate_log is a pointer to a function that takes a
date/time string, a string and varargs and does something with
it. This is useful if you want to convert your error messages into
morse code and transmit them across telegraph wires.

## hexdump.c

When I was a kid, we frequently used a system monitor to figure out
why our systems were doing weird things. I spent A LOT of time looking
at hexdumps. And the format I got used to was from (I think) that
Commodore PET. You get an address on the left, a number of bytes and
then some

Using hexdump.c is straight-forward, pass an address and a length to the
hexdump() function or a FILE *, address and length to the fhexdump()
function and it will print out a hexdump that looks vaguely like this:

    00000000: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |................|
    00000010: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |................|