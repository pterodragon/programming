#include <cassert>
#include <cstdint>
#include <iostream>

using namespace std;

class Solution {
public:
  int hammingWeight(uint32_t n) {
    unsigned int count = 0;
    do {
      count += n & 1;
    } while (n >>= 1);
    return count;
  }
};

int main() {
  auto sol = Solution();
  assert(sol.hammingWeight(1) == 1);
  assert(sol.hammingWeight(0) == 0);
  assert(sol.hammingWeight(0u - 1) == 32);
  return 0;
}
