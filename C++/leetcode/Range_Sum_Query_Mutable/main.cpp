#include <iostream>

#include "solution.hpp"
#include <prettyprint.hpp>

using namespace std;

int main() {
  NumArray numarray({1, 3, 5});
  int s = numarray.sumRange(0, 2);
  cout << "numarray({1, 3, 5})\n";
  cout << "numarray.sumRange(0, 2) = " << s << endl;
  return 0;
}
