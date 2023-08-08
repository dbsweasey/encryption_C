/**
  Header file enumerating functionallity for basic
  8-bit Galois field arithmetic operations. Used by AES for 
  parts of the encryption and decryption processes. 

  @file field.h
  @author David Sweasey
*/

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/** Type used for our field, an unsigned byte. */
typedef unsigned char byte;

/** Number of bits in a byte. */
#define BBITS 8

/** The hex value used for the reducer during the 2nd phase of multiplication */
#define REDUCER 0x11B

#endif

/**
  Performs the addition operation of two bytes
  in the 8-bit Galois field. Returns the result

  @param a first byte to add
  @param b second byte to add
  @return the result of addition
*/
byte fieldAdd( byte a, byte b );

/**
  Performs the subtraction operation of two bytes
  in the 8-bit Galois field. Returns the result

  @param a byte to subtract from
  @param b byte to subtract
  @return the result of subtraction
*/
byte fieldSub( byte a, byte b );

/**
  Perfoms the multiplication operation of two bytes
  in the 8-bit Galois field. Reutrns the result

  @param a first byte to multiply
  @param b second byte to multiply
  @return the result of multiplication
*/
byte fieldMul( byte a, byte b );
