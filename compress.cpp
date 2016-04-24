#include <fstream>  // fstream includes header of iostream
#include "AHCTree.hpp"  // should explicitly include .hpp file in "make"
#include "BitOutputStream.hpp"

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
    AHCTree AHCT(out, in);   // initialize AHC Tree
    int tempChar;  // temporary read symbol

    /** Count the freqs of symbols **/
    while ( (tempChar = in.get()) != EOF ) {  // EOF defined as -1
      AHCT.encode(tempChar);
    }
    
    /* flush all the rest */
    AHCT.end();
    /* close the input file */
    in.close();
    out.close();
  }  
  return 0;
}
