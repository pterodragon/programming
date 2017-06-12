#include <bits/stdc++.h>
#include <boost/format.hpp>

#include "temp/print_type.hpp"

using namespace std;

int main() {
    constexpr int N = 100;
    int* a = new int[N];
    int* mid = a + 50;
    int* end = a + N;
    auto oh = end - mid;
    delete[] a;
    cout << type_name<decltype(oh)>() << endl;
    cout << oh << endl;
    return 0;
}

