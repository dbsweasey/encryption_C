/**
  Header file enumerates the functionality of 
  IO. Reads input files and writes to output files.

  @file io.h
  @author David Sweasey
*/

#include "field.h"
#include <stdio.h>
#include <stdlib.h>

/**
  Reads contents of a binary file with the provided name. Returns
  a pointer to a dynamically allocated array of bytes. This
  array contains the entire file. The size parameter, which should
  be passed by reference, will be updated to reflect how
  many bytes are in the array.

  @param filename the name of the file to read
  @param size will be updated to reflect the number of bytes in the array
  @return a dynamically allocated array containing all of 
          the bytes of the file
*/
byte *readBinaryFile( char const *filename, int *size );

/**
  Writes the contents of a provided data array to the
  file. The size parameter tells the function how many bytes
  are contained in the data array.

  @param filename the file to write to
  @param data the data array (in binary)
  @param size the number of bytes in the array
*/
void writeBinaryFile( char const *filename, byte *data, int size );
