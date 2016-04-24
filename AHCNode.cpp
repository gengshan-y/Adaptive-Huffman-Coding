#include <iostream>
#include "AHCNode.hpp"

bool AHCNode::operator<(const AHCNode& other) {
  if (count != other.count)
    return count>other.count;
  return symbol < other.symbol;  // have to do this coz pri_que is not stable
}
