/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Haffman coding 
 * Filename:        uncompress.cpp
 * Description:     Uncompress the encoded file using Haffman tree.
                    $ ./uncompress <input_path> <output_path>
                    Header format: (only contains used symbols)
                    0x kk kk kk kk number of encoded symbols
                    0x kk          number of unique symbols
                    0x kk          ascii code of symbols
                    0x kk kk kk    count of each symbol
 * Sources of help: stack overflow, piazza
 ***/

#include <fstream>
#include "HCTree.hpp"

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
  ofstream out(argv[2], ofstream::out);

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
    /*** MAIN IMPLIMENTATION OF UNCOMPRESS***/
    vector<unsigned int> freqs (256, 0);
    HCTree HCT;
    unsigned int tempCount;  // number of total symbols
    unsigned char tempUnCount;  // number of unique symbols

    /** Read lastBuffer and count information **/
    in.read((char*)&tempCount, sizeof(tempCount));
    in.read((char*)&tempUnCount, sizeof(tempUnCount));

    /** Read frequency info **/
    unsigned int symAndFreqs;
    unsigned char tempIndex;
    for (int i = tempUnCount + 1; i > 0; i--) {
      in.read((char*)&symAndFreqs, sizeof(symAndFreqs));
      tempIndex = symAndFreqs >> 24;
      freqs[tempIndex] = (symAndFreqs << 8) >> 8;
    }
    
    /** Build the Huffman coding trie in HCT **/
    HCT.build(freqs);

    /** Decode using bit buffer **/
    int tempSymbol;
    BitInputStream inBuf(in);
    while (!in.eof() && tempCount) {
      tempSymbol = HCT.decode(inBuf);
      if (tempSymbol != EOF)
        out << (byte)tempSymbol;
      tempCount --;
    }
  } 
  return 0;
}
