/**
  Implements basic arithmetic operations in n 8-bit Galois field.
  Used internally by AES for many steps in encryption and decryption.

  @file field.c
  @author David Sweasey
*/

#include "field.h"

/** How many bits are in a byte */
#define SIZE_BYTE 8

byte fieldAdd( byte a, byte b )
{
  return ( a ^ b );
}

byte fieldSub( byte a, byte b )
{
  return ( a ^ b );
}

/**
  Finds the highest order 1-bit of the provided value

  @param val the value to check
  @return the index of the highest order 1-bit
*/
static int highestOrderBit( short val )
{
  int index = 0;
  for ( int i = 0; i < SIZE_BYTE * sizeof( short ); i++ ) {
    if ( val & ( 1 << i ) ) {
      index = i;
    }
  }
  return index;
}

byte fieldMul( byte a, byte b )
{
  // Phase 1: Multiplication
  unsigned short tempA = a;
  byte tempB = b;
  unsigned short sum = 0;
  for ( int i = 0; i < SIZE_BYTE; i++ ) {
    if ( ( tempB & 1 ) == 1 ) {
      sum ^= tempA;
    }
    tempB >>= 1;
    tempA <<= 1;
  }

  // Phase 2: Reduction to 8 bits
  unsigned short reducer = REDUCER;
  int index = highestOrderBit( sum );
  
  while ( index >= SIZE_BYTE ) {
    // Left shift the reducer to match the highest order 1-bit
    reducer <<= ( index - SIZE_BYTE );
    // Exclusive or to remove highest order 1-bit
    sum ^= reducer;
    // Reset reducer
    reducer = REDUCER;
    // Find new highest order 1-bit
    index = highestOrderBit( sum );
  }
  
  return (byte)sum;
} 
