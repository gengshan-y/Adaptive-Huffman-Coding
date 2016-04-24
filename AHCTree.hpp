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
    std::istream & in;  // input buffer
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

    /**  Adaptively build tree and encode symbol, given an input symbol
     */
    void encode(int symbol);

    /** Adaptively build tree and decode symbol, return the decoded symbol
     */
    int decode();

    /** Write to NYF and EOF code, then flush() when encoding is finished
     */
    void end();
 private:
    /** Helper method for ~AHCTree **/
    static void deleteAll(AHCNode* n);
    
    /** Helper method: write the path from root to des**/
    void writePath(AHCNode* des);
    
    /** Helper method: updata tree given symbol**/
    void updateTree(int symbol);
 
    /** find the max-ordered node with the same count as tempNode**/
    AHCNode* findMax(AHCNode* tempNode) const;

    /** swap position and order attribute**/
    void swap(AHCNode* n1, AHCNode* n2);
};

#endif // HCTREE_HPP
