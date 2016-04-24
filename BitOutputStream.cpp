/***
 * Name:            Gengshan Yang
 * Date:            Apr 17 2016
 * Assignment #2:   Haffman coding 
 * Filename:        BitOutputStream.cpp
 * Description:     Class for writing files bitwise
 * Sources of help: stack overflow, piazza
 ***/

#include <fstream>
#include "BitOutputStream.hpp"

void BitOutputStream::flush() {
  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

unsigned char BitOutputStream::setBit(unsigned char buf, int bit, int n) {
  // reserve the least n bits
  unsigned char tempChar = (buf << (8-n)) >> (8-n);
  // expose the n+1 bit
  buf = (buf >> (n+1)) << 1;
  // set bit
  buf = (buf + bit) << n;
  // return value
  return (buf + tempChar); 
}

void BitOutputStream::writeBit(int i) {
  // Is the bit buffer full? Then flush it.
  if (nbits == 8) {
    flush();
  }
  // Write the least significant bit of i into the buffer
  buf = setBit(buf, i && 0x0001, nbits);
  // Increment the index
  nbits++;
}
