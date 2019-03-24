#include "suffix_tree.hpp"

int main(int argc, char** argv) {
  string x = argv[1];
  SuffixTree st(x);
  st.print();
}

// #include "suffix_tree2.hpp"
// 
// int main(int argc, char** argv) {
//   string s{argv[1]};
//   SuffixTree2 st(s);
//   st.print();
// }
