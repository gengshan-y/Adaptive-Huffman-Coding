/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Haffman coding  
 * Filename:        BitOutputStream.hpp
 * Description:     Class for writing files bitwise
 * Sources of help: stack overflow, piazza
 ***/

#ifndef BITOUTSTREAM_HPP
#define BITOUTSTREAM_HPP

#include <iostream>
#include <fstream>

/***  Bitwise ouput stream
 ***  Construction: BitOutputStream name_bitwisebuf(name_ostream);
 **/
class BitOutputStream {
 private:
  unsigned char buf;  // 1 byte buffer for bits
  int nbits;  // how many bits have been written
  std::ostream & out;  // reference to the output stream

 public:
  /*** Initialize a BitOutputStream that will
   *** the given ostream for output
   **/
  BitOutputStream(std::ostream & os) : out(os) {  // why cant use ini list??
    // clear buffer and bit counter
    buf = 0;
    nbits = 0;
  }

  /*** Send the buffer to the output, and clear it
   **/
  void flush();

  /** Return a char that is the same as the input char 
   ** except that the nth bit from the right has been 
   ** set to the input bit.
   */
  unsigned char setBit(unsigned char buf, int bit, int n);

  /** Write the least significant bit of the argument to
   ** the bit buffer, and increment the bit buffer index.
   ** But flush the buffer first, if it is full.
   */
  void writeBit(int i);

  /** **/
  void writeSym(int symbol);
};

#endif  // BITOUTSTREAM_HPP
