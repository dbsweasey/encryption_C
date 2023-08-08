/**
  Responsible for reading and writing input and output files,
  respectively.

  @file io.c
  @author David Sweasey
*/

#include "io.h"

/** How many bytes to read into the dynamically allocated array at a time */
#define INIT_CAP 16

byte *readBinaryFile( char const *filename, int *size)
{
  FILE *binary = fopen( filename, "rb" );
  
  int capacity = INIT_CAP;
  byte *buffer = (byte *)calloc( capacity, sizeof(byte) );
  int len;
  while ( ( len = fread( buffer + *size, sizeof(byte), INIT_CAP, binary ) ) != 0 ) {
    *size += len;
    if (len == INIT_CAP) {
      capacity += INIT_CAP;
      buffer = (byte *)realloc( buffer, sizeof(byte) * capacity );
    }
  }

  fclose( binary );
  return buffer;
}

void writeBinaryFile( char const *filename, byte *data, int size )
{
  FILE *file = fopen( filename, "wb" );

  fwrite( data, sizeof(byte), size, file );
  fclose( file );
}
