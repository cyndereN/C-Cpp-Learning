Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. 
Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. 
Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. 
For example, there will not be input like 3a or 2[4].

The test cases are generated so that the length of the output will never exceed 10^5.

Input: s = "3[a]2[bc]"
Output: "aaabcbc"

```cpp
#include <iostream>
#include <string>

using namespace std;

string decodeString(string s) {
    string result;
    int i = 0;
    while (i < s.length()) {
        if (isdigit(s[i])) {
            int count = 0;
            while (isdigit(s[i])) {
                count = count * 10 + (s[i] - '0');
                i++;
            }
            int start = i + 1;
            int end = start;
            int bracket = 1;
            while (bracket > 0) {
                if (s[end] == '[') {
                    bracket++;
                } else if (s[end] == ']') {
                    bracket--;
                }
                end++;
            }
            string sub = decodeString(s.substr(start, end - start - 1));
            for (int j = 0; j < count; j++) {
                result += sub;
            }
            i = end;
        } else {
            result += s[i];
            i++;
        }
    }
    return result;
}

int main() {
    string s = "2[a3[de]]";
    string result = decodeString(s);
    cout << result << endl; // expected output: adededeadedede
    return 0;
}
```


```cpp
class Solution {
public:
    string decodeString(string s) {
         stack<string> chars;
        stack<int> nums;
        string res;
        int num = 0;
        for(char c : s) {
            if(isdigit(c)) {
                num = num*10 + (c-'0');                              
            }
            else if(isalpha(c)) {
                res.push_back(c);                
            }
            else if(c == '[') {
                chars.push(res);
                nums.push(num);
                res = "";
                num = 0;
            }
            else if(c == ']') {
                string tmp = res;
                for(int i = 0; i < nums.top()-1; ++i) {
                    res += tmp;
                }
                res = chars.top() + res;
                chars.pop(); nums.pop();
            }
        }
        return res;
    }
};
```