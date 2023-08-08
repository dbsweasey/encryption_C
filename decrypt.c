/**
  Contains the main method, which begins program execution. Reads the 
  input files and performs decryption and writes the plaintext into
  the provided file. The prgram requires three files
    - usage; decrypt: <key-file> <input-file> <output-file>

  @file decrypt.c
  @author David Sweasey
*/
#include "io.h"
#include "aes.h"
#include "field.h"

/** The number of required command-line args */
#define REQUIRED_ARGS 4

/** Expands to the command-line argument containing the key file */
#define KEYFILE argv[1]

/** Expands to the command-line argument containing the input file */
#define INPUTFILE argv[2]

/** Expands to the command-line argument containing the output file */
#define OUTPUTFILE argv[3]

/** The zero byte used for padding */
#define ZEROBYTE 0x00

/**
  Prints the program usage and exits with a status of 1.
*/
static void usage()
{
  fprintf( stderr, "usage: decrypt <key-file> <input-file> <output-file>\n");
  exit(1);
}

/**
  Attempts to open the provided file. If it cannot be opened, exit the program.
  
  @param filename the filename to test
*/
static void testFile( char *filename )
{
  FILE *file = fopen( filename, "rb" );
  if ( file == NULL ) {
    fprintf( stderr, "Can't open file: %s\n", filename );
    exit(1);
  }
  fclose( file );
}

/**
  Checks for zerobytes at the end of the ciphertext which is padding from
  encryption. Removes them.

  @param data the ciphertext
  @param size the number of bytes within the ciphertext
*/
static void unpad( byte *data, int *size )
{
  byte zero = ZEROBYTE;
  // Check last 16 values for 0 bytes
  int initSize = *size;
  for ( int i = initSize - 1; i >= initSize - BLOCK_SIZE; i-- ) {
    if ( data[i] == zero ) {
      (*size)--;
    } else {
      break;
    }
  }
}

/**
  Main method begins program execution. Checks if there were a correct
  number of arguments, and that each file can be opened and is valid
  (e.g. key file must contain 16 bytes). If all inputs are valid,
  performs decryption and writes the results to the provided
  output file.

  @param argc number of command-line arguments
  @param argv command-line arguments
  @return program exit status
*/
int main( int argc, char *argv[] )
{
  if ( argc != REQUIRED_ARGS ) {
    usage();
  }
  for ( int i = 1; i < REQUIRED_ARGS - 1; i++ ) {
    testFile( argv[i] );
  }

  // Read in key file and make sure it is 16 bytes long
  int size = 0;
  byte *key = readBinaryFile( KEYFILE, &size );
  if ( size != BLOCK_SIZE ) {
    free( key );
    fprintf( stderr, "Bad key file: %s\n", KEYFILE );
    return( EXIT_FAILURE );
  }

  // Read in ciphertext file and enusre it has a multiple of 16 bytes
  size = 0;
  byte *data = readBinaryFile( INPUTFILE, &size );
  if ( size % BLOCK_SIZE != 0 ) {
    free( data );
    free( key );
    fprintf( stderr, "Bad ciphertext file length: %s\n", INPUTFILE );
    return( EXIT_FAILURE );
  }

  for ( int i = 0; i < size / BLOCK_SIZE; i++ ) {
    decryptBlock( data + i * BLOCK_SIZE, key );
  }

  unpad( data, &size );
  
  // Print the plaintext to the output file
  writeBinaryFile( OUTPUTFILE, data, size );

  free( key );
  free( data );
  return EXIT_SUCCESS;
}
