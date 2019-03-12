#include "suffix_tree.hpp"

int main(int argc, char** argv) {
  string x = argv[1];
  SuffixTree st(x);
  st.print();
}
