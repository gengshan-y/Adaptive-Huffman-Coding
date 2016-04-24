/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Haffman coding  
 * Filename:        BitInputStream.hpp
 * Description:     Class for reading files bitwise
 * Sources of help: stack overflow, piazza
 ***/

#ifndef BITINSTREAM_HPP
#define BITINSTREAM_HPP

#include <iostream>
#include <fstream>  
// dont #include "HCTree.hpp" for dependent reference reason

/***  Bitwise input stream
 ***  Construction: BitInputStream name_bitwisebuf(name_istream);
 **/
class BitInputStream {
 private:
  unsigned char buf;  // 1 byte buffer for bits
  int nbits;  // how many bits have been read from
  std::istream& in;  // the input stream to be used

 public:
  /** Initialize a BitInputStream that will use
    * the given istream for input.
   */
  BitInputStream(std::istream & is) : in(is)
  { buf = 0; // clear buffer
    nbits = 8; // initialize bit index
  }

  /** Fill the buffer from the input */
  void fill();

  /** Read the next bit from the bit buffer.
    * Fill the buffer from the input stream first if needed.
    * Return 1 if the bit read is 1;
    * return 0 if the bit read is 0;
   */
  int readBit();
  
  /** Return the nth bit from the right of a byte argument **/
  unsigned char bitValue(unsigned char b, int n);
  
  /** Read in 9 bits standing for symbols and return **/
  int readSym();
};

#endif  // BITINSTREAM_HPP
