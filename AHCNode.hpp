/***
 * Name:            Gengshan Yang
 * Date:            Apr 21 2016
 * Assignment #2:   Adaptive Haffman coding
 * Filename:        AHCNode.hpp
 * Description:     Adaptive Haffman Tree Node Class
 * Sources of help: stack overflow, piazza
 ***/

#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

using namespace std;

/** A class, instances of which are nodes in an AHCTree.
 */
class AHCNode {
 public:
    unsigned int count;  // number of times val has occured in file so far
    int symbol;  // 0~255 indicates the ascii symbols, -1 indicates NYT
    int order;  //ordering system to track counts
    AHCNode* c0;  // pointer to '0' child
    AHCNode* c1;  // pointer to '1' child
    AHCNode* p;   // pointer to parent

    AHCNode(unsigned int count,
      int symbol,
      int order,
      AHCNode* c0 = 0,
      AHCNode* c1 = 0,
      AHCNode* p = 0)
        : count(count), symbol(symbol), order(order), c0(c0), c1(c1), p(p) { }

    /** Less-than comparison, so HCNodes will work in std::priority_queue
     *  We want small counts to have high priority.
     *  And we want to break ties deterministically.
     */
    bool operator<(const AHCNode& other);
};

/** For printing an AHCNode to an ostream
 */
ostream& operator<<(ostream&, const AHCNode&) __attribute__((weak)); // shut the linker up
ostream& operator<<(ostream& stm, const AHCNode& n) {
    stm << "[" << n.count << "," << (int) (n.symbol) << "]";
    return stm;
}

#endif // HCNODE_HPP
