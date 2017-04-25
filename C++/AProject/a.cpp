#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string line;
    constexpr const char *filename = "reddit_post.txt";
    ifstream myfile(filename);
    cout << boolalpha << myfile.is_open() << '\n';
    myfile.close();
    cout << boolalpha << myfile.is_open() << '\n';
    while (getline(myfile, line)) {
        cout << line << '\n';
    }
    return 0;
}
