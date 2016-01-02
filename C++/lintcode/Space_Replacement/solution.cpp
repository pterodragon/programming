#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * @param string: An array of Char
     * @param length: The true length of the string
     * @return: The true length of new string
     */
    int replaceBlank(char string[], int length) {
        // Write your code
        int no_of_space = 0;
        for (int i = 0; i < length; i++) {
            if (string[i] == ' ') {
                no_of_space++;
            }
        }
        int L = length + no_of_space * 2;
        int i = length - 1;
        int j = L - 1;
        string[L] = '\0';

        while (i >= 0) {
            if (string[i] == ' ') {
                string[j--] = '0';
                string[j--] = '2';
                string[j--] = '%';
            } else {
                string[j--] = string[i];
            }
            i--;
        }
        return L;
    }
};

int main() {
	Solution sol;
	char ca[20] = "hello world";
	int length = 11;
	int new_length = sol.replaceBlank(ca, 11);
	cout << ca << endl;
	cout << new_length << endl;
	return 1;
}
