/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Star Point: Adaptive Haffman coding
 * Filename:        AHCTree.hpp
 * Description:     Adaptive Huffman Tree class
 * Sources of help: stack overflow, piazza
 ***/

#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <vector>
#include <stack>
#include <fstream>
#include "AHCNode.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

using namespace std;

/** Adaptive Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class AHCTree {
 private:
    AHCNode* root;
    AHCNode* NYT;  // pointer to NYT node
    int size; 
    vector<AHCNode*> leaves;  // pointers to nodes representing symbols
    vector<AHCNode*> nodes;  // pointers to nodes representing orders
    std::ostream & out;  // output buffer
    BitOutputStream outbuf;
    std::istream & in;
    BitInputStream inbuf;

 public:
    explicit AHCTree(std::ostream & os, std::istream & is)
      : out(os), outbuf(os), in(is), inbuf(is) {
        root = new AHCNode(0, -1, 512);  // initiallize AHC Tree, with NTY node
        NYT = root;
        size = 1;
        leaves = vector<AHCNode*>(256, (AHCNode*) 0);
        nodes = vector<AHCNode*>(513, (AHCNode*) 0);
        nodes[512] = NYT;
    }

    ~AHCTree();

    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    void encode(int symbol);

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int decode();

    void end();
 private:
    static void deleteAll(AHCNode* n);
    
    void writePath(AHCNode* des);

    void updateTree(int symbol);

    AHCNode* findMax(unsigned int count) const;

    void swap(AHCNode* n1, AHCNode* n2);
};

#endif // HCTREE_HPP
