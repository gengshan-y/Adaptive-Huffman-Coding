/***
 * Name:            Gengshan Yang
 * Date:            Apr 16 2016
 * Assignment #2:   Haffman coding 
 * Filename:        HCTree.cpp
 * Description:     Huffman Tree class
 * Sources of help: stack overflow, piazza
 ***/

#include <iostream>
#include <queue>
#include <stack>
#include "HCTree.hpp"  //include the corresponding .hpp file for each .cpp file

HCTree::~HCTree() {
  deleteAll(root);
}

void HCTree::deleteAll(HCNode* n) {  // dont need to declare static this time
  if (n == 0)
    return;
  // delete all nodes in the left subtree
  deleteAll(n->c0);
  // delete all nodes in the right subtree
  deleteAll(n->c1);
  // delete the root
  delete n;
}

void HCTree::build(const vector<unsigned int>& freqs) {
  std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> pq;
  // use priority queue to store forests
  HCNode* tempC0;
  HCNode* tempC1;

  /** Initialize the forest **/
  for (int i = 0; i < 256 ; i++) {
    if (freqs[i] != 0) {
      leaves[i] = new HCNode(freqs[i], i);
      pq.push(leaves[i]);
    }
  }

  /** Edge case: if only one symbol exist **/
  if (pq.size() == 1) {
    root = pq.top();
    return;
  }

  /** Build the Huffman tree iteratively for n-1 times **/
  for (int i = pq.size(); i > 1 ; i --) {
    /* get the top 2 symbols */
    tempC0 = pq.top();
    pq.pop();
    tempC1 = pq.top();
    pq.pop();
    //  this root will finally become the root of the whole tree
    root = new HCNode(tempC0->count+tempC1->count, tempC0->symbol);
    /* build a subtree */
    root->c0 = tempC0;
    root->c1 = tempC1;
    tempC0->p = root;
    tempC1->p = root;
    pq.push(root);
  }
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {
  stack<int> tempCode;
  int tempWrite;
  HCNode* tempNode = leaves[symbol];

  /** Edge case: only one symbol exists **/  
  if (leaves[symbol] == root)
    out.writeBit(0);
  /** Handle other cases **/
  while ( tempNode->p != 0 ) {  // iterate until reaching the root
    if (tempNode->p->c0 == tempNode) {
      tempCode.push(0);  // store codes in stack
    } else {
      tempCode.push(1);
    }
    tempNode = tempNode->p;
  }
  /* pop the stack and write */
  while (!tempCode.empty()) {
    tempWrite = tempCode.top();
    out.writeBit(tempWrite);
    tempCode.pop();
  } 
}

int HCTree::decode(BitInputStream& in) const {
  int tempChar;
  HCNode* tempNode = root;
           
  // handle one existing symbol
  if (root && !root->c0) {
    tempChar = in.readBit();
  }        
           
  while ( (tempNode->c0) && (tempNode->c1) && ( (tempChar = in.readBit()) != EOF ) ) {
    if (tempChar == 0)
      tempNode = tempNode->c0;
    else
      tempNode = tempNode->c1;
  }        
           
  if (tempChar == EOF)
    return EOF;   
  else {          
    return tempNode->symbol;
  }
}
