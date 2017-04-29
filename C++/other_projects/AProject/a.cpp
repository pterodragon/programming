#include <bits/stdc++.h>
#include <boost/format.hpp>


using namespace std;

template<typename X>
X&& oh(typename remove_reference<X>::type& a) noexcept {
    cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<X&&>(a);
} 

template<typename X>
X&& oh2(X& a) noexcept {
    cout << __PRETTY_FUNCTION__ << '\n';
    return static_cast<X&&>(a);
} 

void f(int& x) {
    cout << __PRETTY_FUNCTION__ << '\n';
    cout << x << '\n';
}

void f(int&& x) {
    cout << __PRETTY_FUNCTION__ << '\n';
    cout << x << '\n';
}

int get1() {
    return 1;
}

template<typename T> 
void g(T&& arg) { 
    f(oh<T>(arg));
    f(oh2(arg));
} 
int main() {
    cout << "int x = 1; g(x)" << '\n';
    int x = 1;
    g(x);
    cout << "g(get1())" << '\n';
    g(get1());
}
