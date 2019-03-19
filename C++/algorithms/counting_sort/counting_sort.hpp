#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <vector>

using namespace std;

template <typename T, int S = 1 << (sizeof(T) * 8)>
void counting_sort_inplace(vector<T>& v) {
  array<int, S> c{};
  for (auto const& e : v) ++c[e];
  auto it = begin(v);
  for (auto const& e : c) it = fill_n(it, c[e], e);
}

// stable sort the collection based on f(e) for e in v
// like sorting vector<string> based on the k'th char
// return vector of original indices
template <typename T, typename Func,
          int S = 1 << (sizeof(result_of_t<Func(T)>) * 8)>
vector<T> counting_sort(const vector<T>& v, Func f) {
  array<int, S> c{};
  for (auto const& e : v) ++c[f(e)];
  partial_sum(begin(c), end(c), begin(c));
  vector<T> res(v.size());
  for (int q = v.size() - 1; q >= 0 && q < v.size(); --q)
    res[--c[f(v[q])]] = v[q];
  return res;
}

template <typename T, typename Func,
          int S = 1 << (sizeof(result_of_t<Func(T)>) * 8)>
vector<T> counting_sort2(const vector<T>& v, Func f) {
  array<int, S> c{};
  for (auto const& e : v) ++c[f(e)];
  for (int q = 0, sum = 0; q < S; ++q) {
    int t = c[q];
    c[q] = sum;
    sum += t;
  }
  vector<T> res(v.size());
  for (int q = 0; q < v.size(); ++q) res[c[f(v[q])]++] = v[q];
  return res;
}
