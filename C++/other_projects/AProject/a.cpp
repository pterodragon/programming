#include <bits/stdc++.h>
#include <boost/format.hpp>

using namespace std;

struct string_view
{
    char const* data;
    std::size_t size;
};

inline std::ostream& operator<<(std::ostream& o, string_view const& s)
{
    return o.write(s.data, s.size);
}

template<class T>
constexpr string_view get_name()
{
    char const* p = __PRETTY_FUNCTION__;
    while (*p++ != '=');
    for (; *p == ' '; ++p);
    char const* p2 = p;
    int count = 1;
    for (;;++p2)
    {
        switch (*p2)
        {
        case '[':
            ++count;
            break;
        case ']':
            --count;
            if (!count)
                return {p, std::size_t(p2 - p)};
        }
    }
    return {};
}

template <typename T>
constexpr auto type_name_length = get_name<T>().size;

#define typeof(x) cout << "type of " << #x << ": " << get_name<decltype(x)>() << '\n'
#define valueof(x) cout << "value of " << #x << ": " << x << '\n'

template<typename T_, typename U_, typename V_>
class X {
public:
    typedef T_ T;
    typedef U_ U;
    typedef V_ V;
    class Inner {
    public:
        Inner(const X& outer) : outer(outer) {}
        void p() {
            valueof(outer.f(3));
            valueof(outer.g(3));
            valueof(outer.h(3));
        }
        const X& outer;
    };
    X(T_ f, U_ g, V_ h) : f(f), g(g), h(h) {}
    Inner makeInner() { return Inner(*this); }
    T_ f;
    U_ g;
    V_ h;
};

template<typename... T>
X<T...> makeX(T&&... args) {
    return X<T...>(std::forward<T>(args)...);
}

int add1(int x) {
    return x + 1;
}
int times10(int x) {
    return x * 10;
}

int minus5(int x) {
    return x - 5;
}

typedef int (*func)(int);

int main() {
    //func f1 = add1;
    //auto x = makeX(f1, times10, &minus5);
    auto x = makeX(&add1, &times10, &minus5);
    auto inner = x.makeInner();
    inner.p();
    valueof(inner.outer.f(5));
    valueof(inner.outer.g(5));
    valueof(inner.outer.h(5));
    //X::Inner inner(x);
    valueof(x.f(2));
    valueof(x.g(2));
    valueof(x.h(2));
    //valueof(inner.outer.f(2));
    //valueof(inner.outer.g(2));
    //valueof(inner.outer.h(2));
    typeof(x);
    typeof(add1);
    typeof(times10);
    typeof(minus5);
    typeof(x.f);
    typeof(x.g);
    typeof(x.h);
    return 0;
}

