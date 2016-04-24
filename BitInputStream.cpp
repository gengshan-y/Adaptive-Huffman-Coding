/***
 * Name:            Gengshan Yang
 * Date:            Apr 17 2016
 * Assignment #2:   Haffman coding 
 * Filename:        BitInputStream.cpp
 * Description:     Class for reading files bitwise
 * Sources of help: stack overflow, piazza
 ***/

#include <fstream>
#include "BitInputStream.hpp"

void BitInputStream::fill() {
  buf = in.get();
  nbits = 0;
}

int BitInputStream::readBit() {
  // If all bits in the buffer are read, fill the buffer first
  if (nbits == 8) {
    fill();
  }
  // Get the bit at the appriopriate location in the bit
  // buffer, and return the appropriate int
  unsigned char tempValue = bitValue(buf, nbits);
  nbits ++;
  return tempValue;
}

unsigned char BitInputStream::bitValue(unsigned char buf, int n) {
  // move the appropriate bit to the least bit
  buf = buf >> n;
  // clear the high bits
  buf = buf & 0x01;  // && is not for logic operator 
  return buf;
}

int BitInputStream::readSym() {
  int tempBit = 0;
  for (int i = 0; i < 9; i++) {
    tempBit = tempBit + (readBit() <<  i);
  }
return tempBit;
}
