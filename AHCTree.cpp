/***
 * Name:            Gengshan Yang
 * Date:            Apr 16 2016
 * Assignment #2:   Haffman coding 
 * Filename:        HCTree.cpp
 * Description:     Huffman Tree class
 * Sources of help: stack overflow, piazza
 ***/

#include <iostream>
#include "AHCTree.hpp"  //include the corresponding .hpp file for each .cpp file

AHCTree::~AHCTree() {
  deleteAll(root);
}

void AHCTree::deleteAll(AHCNode* n) {  // dont need to declare static this time
  if (n == 0)
    return;
  // delete all nodes in the left subtree
  deleteAll(n->c0);
  // delete all nodes in the right subtree
  deleteAll(n->c1);
  // delete the root
  delete n;
}

void AHCTree::encode(int symbol) {
  if (!leaves[symbol]) {  // no symbol of that leaf was build before
    outbuf.writeSym(symbol);  // write the ascii of symbol
    writePath(NYT);  // write the path from root to NYT
  }
  else 
    writePath(leaves[symbol]);
  updateTree(symbol);
}

void AHCTree::writePath(AHCNode* des) {
  stack<int> tempCode;  // temporary inverse storage of coding

  while ( des->p != 0 ) {  // iterate until reaching the root
    if (des->p->c0 == des) {
      tempCode.push(0);  // store codes in stack
    } else {
      tempCode.push(1);
    }
    des = des->p;
  }

  /* pop the stack and write */
  int tempWrite;
  while (!tempCode.empty()) {
    tempWrite = tempCode.top();
    outbuf.writeBit(tempWrite);
    tempCode.pop();
  } 
}

void AHCTree::updateTree(int symbol) {
  AHCNode* tempNode;
  if (leaves[symbol]) {  // if this symbol is in the tree
    tempNode = leaves[symbol];
    while(tempNode) {
      if (tempNode->p)
        swap(findMax(tempNode->count), tempNode);
      tempNode->count++; 
      tempNode = tempNode->p;
    }
  } 
  else {  // new symbol
    NYT->c0 = new AHCNode(0, -1, 512-size);
    nodes[512-size++] = NYT->c0;
    NYT->c1 = new AHCNode(1, symbol, 512-size);
    nodes[512-size++] = NYT->c1;
    leaves[symbol] = NYT->c1;
    NYT->c0->p = NYT;
    NYT->c1->p = NYT;
    NYT = NYT->c0;

    tempNode = NYT;
    while (tempNode->p) {  // update count until root
      tempNode = tempNode->p;
      if (tempNode->p)
        swap(findMax(tempNode->count), tempNode);  // swap order and position
      tempNode->count++;
    }
  }
}

AHCNode* AHCTree::findMax(unsigned int count) const {
  int order = 512;  // order of nodes
  while(nodes[order]->count > count)
    order--;
  return nodes[order];
}

void AHCTree::swap(AHCNode* n1, AHCNode* n2) {
  if (n1->p->c0 == n1)
    n1->p->c0 = n2;
  else
    n1->p->c1 = n2;

  if (n2->p->c0 == n2)
    n2->p->c0 = n1;
  else
    n2->p->c1 = n2;

  AHCNode* temp = n1->p;
  n1->p = n2->p;
  n2->p = temp;

  int tempO = n1->order;
  n1->order = n2->order;
  n2->order = tempO;

  temp = nodes[n1->order];
  nodes[n1->order] = nodes[n2->order];
  nodes[n2->order] = temp;
}

int AHCTree::decode() {
  int tempVal;
  AHCNode* tempNode = root;
  
  while(tempNode->c0) {  // move down to leaf
    tempVal = inbuf.readBit();
    if (tempVal == 0)
      tempNode = tempNode->c0;
    else
      tempNode = tempNode->c1;
  }

  
  if (tempNode == NYT) {
    tempVal = inbuf.readSym(); 
  }
  else {
    tempVal = tempNode->symbol;   
  }
  
  if (tempVal == 0x01ff)
    return tempVal;
      
  updateTree(tempVal & 0x00ff);
  return tempVal;
}

void AHCTree::end() {
  for (int i = 0; i < 9; i++)
    outbuf.writeBit(1);
  outbuf.flush();
}
