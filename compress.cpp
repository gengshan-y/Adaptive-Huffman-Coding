/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Haffman coding
 * Filename:        compress.cpp
 * Description:     Compress the input file using Haffman tree.
                    $ ./compress <input_path> <output_path>
                    Header format: (only contains used symbols)
                    0x kk kk kk kk number of encoded symbols
                    0x kk          number of unique symbols
                    0x kk          ascii code of symbols
                    0x kk kk kk    count of each symbol
 * Sources of help: stack overflow, piazza
 ***/

#include <fstream>  // fstream includes header of iostream
#include "HCTree.hpp"  // should explicitly include .hpp file in "make"
#include "BitOutputStream.hpp"

/** helper method: symCombFreqs
 ** return the combination of symbol and freqs
 ** data format: 8 most significant bits are symbol, rest 24 bits are freqs
 */
unsigned int symCombFreqs(unsigned char sym, unsigned int freqs);

using namespace std;

int main(int argc, char* argv[]) {
  // Check for Arguments
  if (argc != 3) {
    cout << "Invalid number of arguments. \n"
         << "Usage: ./main <input filename> <output filename> \n";
      return -1;
  }

  // Open file
  ifstream in;
  in.open(argv[1], ios::binary);
  ofstream out(argv[2], std::ofstream::out);

  // Check if input file was opened
  if (!in.is_open()) {
    cout << "Invalid input file. No file was opened. Please try again. \n";
    return -1;
  }

  // Check for empty file
  in.seekg(0, ios_base::end);
  unsigned int len = in.tellg();
  if (len == 0) {
    in.close();
    out.close(); 
    cout << "Empty file. \n";
    return -1;
  }

  // Reset the stream to the begining of the file
  in.seekg(0, ios_base::beg);

  if (in.is_open()) {
    /*** MAIN FUNCTION IMPLIMENTATION ***/
    int tempChar;  // use int instead of char(0-127)/unsigned char
    vector<unsigned int> freqs (256, 0);  // use unsigned int since may > 10m
    HCTree HCT;

    /** Count the freqs of symbols **/
    while ( (tempChar = in.get()) != EOF ) {  // EOF defined as -1
      freqs[tempChar]++;
    }
    
    /** Build the Huffman coding trie in HCT **/
    HCT.build(freqs);  

    /** Write frequency info to header file **/
    BitOutputStream outBuf(out);
    unsigned int tempCount = 0;
    unsigned char tempUnCount = 0;
    /* reserve space for countings */
    out.write((char*)&tempCount, sizeof(tempCount));
    out.write((char*)&tempUnCount, sizeof(tempUnCount));

    /* write header frequency */
    unsigned int symAndFreqs;
    int tempIntCount = 0;  // tempUnCount can be 0 255, we need it as buffer
    for (int i = 0; i < 256 ; i++) {
      if (freqs[i] != 0) {
        symAndFreqs = symCombFreqs(i, freqs[i]);
        out.write((char*)&symAndFreqs, sizeof(symAndFreqs));
        tempIntCount ++;
      }
    }
    tempUnCount = tempIntCount - 1;  // since we represent 0 as 1 unique symbol

    /** Encoding **/
    /* reset the stream to the begining of the file */
    in.clear();
    in.seekg(0, ios_base::beg);
    /* encode the file */
    while ( (tempChar = in.get()) != EOF ) {
      HCT.encode(tempChar, outBuf);
      tempCount ++;
    }
   
    /** Add counting information to the header **/
    out.clear();
    out.seekp(0, ios_base::beg);
    out.write((char*)&tempCount, sizeof(tempCount));
    out.write((char*)&tempUnCount, sizeof(tempUnCount));
    
    /* flush all the rest */
    out.seekp(0, ios_base::end);
    outBuf.flush();
    /* close the input file */
    in.close();
    out.close();
  }  
  return 0;
}

unsigned int symCombFreqs(unsigned char sym, unsigned int freqs) {
  unsigned int tempFreqs = sym;
  tempFreqs = tempFreqs << 24;
  return (tempFreqs + freqs);
}
