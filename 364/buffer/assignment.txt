CS 364                                                       Spring 97

                      DUE ___________________
       
                             Assignment 1

In this assignment, you will unblock buffered input records and
repack the byte data obtained into a new set of blocked files.

The records inside the blocks have varying sizes according the 
following scheme.

   The data types are character (c), string (s), integer (d) and float(f).
   The size of the data of the given type will also be encoded, with
   the exception of character data, which will always have size 1.

   The data layout will be encoded as a format string, similar but not
   equivalent to C I/O format strings:

     (xiyjzk....)  where x, y, z and so on are the data type indicators
                   and i, j, k and so on are the size indicators.
     The parenthesis symbols, "(" and ")" are part of the format string.

   For instance (s5d3) would mean a string of length 5 followed by 
   an integer taking up three bytes (as an ascii value).

   Since character data is always length 1, the length indicator is 
   omitted.  Floating point data is formatted as l.r where l is the 
   number of decimal places to the left of the decimal and r is the 
   number  of places to the right of the decimal point.

    A more robust format string might be

     (s5d3cf3.5s2cd3d3f1.2)

Data:

   Data immediately follows the format string in the buffer:

     (s5d3cf3.5s2cd3d3f1.2)keith123q12312345xyz987654321

   The data is then interpreted as follows:

        s5:    keith
        d3:    123
        c:     q
        f3.5:  123.12345
        s2:    xy
        c:     z
        d3:    987
        d3     654
        f1.2   3.21

The next record follows immediately in the buffer:

 (s5d3cf3.5s2cd3d3f1.2)keith123q12312345xyz987654321(d1d1cs2)12abc(d5)13579...

THE BUFFER SIZE IS 64 (although this value is subject to change and,
rest assured that I will change it!).  If the buffer is exhausted
before the data is, inspect the next bufferfull until all inputs are
exhausted.

Your program must distribute all the string data to one file, all the
character data to another, all  the integer data to yet another, and all the
floating point data to a fourth file.  The same formatting methods must
be used to encode the data (WHERE APPROPRIATE!)

Thus the sample above would be distributed:

  string file:    (s5s2s2...)keithxybc....
               or (s5)keith(s2)xy(s2)bc... 

  integer file    (d3d3d3d1d1d5...)1239876541213579...
               or (d35)123(d3)987(d3)654(d1)1(d1)2(d5)13579... 

  float file:     (f3.5f1.2...12312345321
               or (f3.5)12312345(f1.2)321

  character file:  (ccc...)qza...    (really?)
               or  (c)q(c)z(c)a...


File inputs on the command line must be used.

Use system calls: read, write open, close, etc.. This requires file
descriptors, not handles.

Assumptions / other issues:

1. The formating digit will be between 1-9, inclusive.

2. No format/data will require more than 2 buffers full to completely 
   process, but should NOT depend on the value 64, but rather the constant
   BUFFER SIZE.

3. Some sample data is in directory ~kbg/364/Buffer.

This document is in ~kbg/364/adm/buffer  






