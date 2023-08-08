/**
  Header file which layout the various function headers required for
  completing encryption and decryption. Each function is a step in
  one or both processes.

  @file aes.h
  @author David Sweasey
*/

#ifndef _AES_H_
#define _AES_H_

#include "field.h"

/** Number of bytes in an AES key or an AES block. */
#define BLOCK_SIZE 16

/** Numer of rows when a data block is arranged in a square. */
#define BLOCK_ROWS 4

/** Numer of columns when a data block is arranged in a square. */
#define BLOCK_COLS 4

/** Number of bytes in a word. */
#define WORD_SIZE 4

/** Number of roudns for 128-bit AES. */
#define ROUNDS 10

/** The index where word2 begins in subkey generation */
#define WORD2 4

/** The index where word3 begins in subkey generation */
#define WORD3 8

/** The index where word4 begins in subkey generation */
#define WORD4 12

#endif

/**
  Computes the g function used in creating subkeys
  from the original 16-byte key. Takes a 4-byte input (src)
  and returns a 4-byte result (dest). 

  @param src the 4-byte input
  @param dest the 4-byte output
  @param r round number between 1 and 10
*/
void gFunction( byte dest[ WORD_SIZE ], byte const src[ WORD_SIZE ], 
  int r );

/**
  Fills in the subkey array with subkeys for each round of
  AES.

  @param subkey the subkey array to fill
  @param key the key to use to compute subkeys
*/
void generateSubkeys( byte subkey[ ROUNDS + 1 ][ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/**
  Adds the provided subkey to the given data array.

  @param data the data array to add the computed subkey to
  @param key the subkey
*/
void addSubkey( byte data[ BLOCK_SIZE ], byte const key[ BLOCK_SIZE ] );

/**
  Rearranges a block of 16 data values from a 1D arrangement
  to a 2D arrangement.

  @param square the 4x4 array to convert data values to
  @param data the 16 data value block to convert from
*/
void blockToSquare( byte square[ BLOCK_ROWS ][ BLOCK_COLS ], byte const data[ BLOCK_SIZE ]);

/**
  Rearranges a 4x4 arrangement of data values to a 1D array
  of 16 values. The inverse of blockToSquare.

  @param data the 16 element array to convert to
  @param square the 4x4 array of data to convert from
*/
void squareToBlock( byte data[ BLOCK_SIZE ], byte const square[ BLOCK_ROWS ][ BLOCK_COLS ] );

/**
  Shifts the 2nd row by 1 column to the left, 3rd row by 2 columns,
  and 4th row by 3.

  @param square the 4x4 square of values to shift
*/
void shiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ]);

/**
  Shifts the 2nd row by 1 column to the right, 3rd row by 2 columns,
  and 4th row by 3. The inverse of shiftRows.

  @param square the 4x4 square of values to shift
*/
void unShiftRows( byte square[ BLOCK_ROWS ][ BLOCK_COLS ]);

/**
  Creates four new columns based on multiplying each column
  by a specific "mixing matrix"

  @param square the 4x4 square of values to operate on
*/
void mixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ]);

/**
  Performs the inverse operation on the 4x4 square. Multiplies
  each column by the inverse of the "mixing matrix"

  @param square the 4x4 square of values to operate on
*/
void unMixColumns( byte square[ BLOCK_ROWS ][ BLOCK_COLS ]);

/**
  Encrypts a 16-byte block of data using the provided key. Generates
  the 11 subkeys from the key, adds the first subkey, then 
  performs 10 rounds of necessary operations to encrypt the block

  @param data the data to encrypt
  @param key the key to use for encryption
*/
void encryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );

/**
  Decrypts a 16-byte block of data using the given key. Generates the
  11 subkeys from the key, performs 10 rounds of inverse operations and
  then an add subkey to decrypt the block

  @param data the data to decrypt
  @param key the key to use for decryption
*/
void decryptBlock( byte data[ BLOCK_SIZE ], byte key[ BLOCK_SIZE ] );
