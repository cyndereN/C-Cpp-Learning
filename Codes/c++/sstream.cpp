#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main(){
    string line;
    while(getline(cin, line)){
        int sum = 0, x;
        stringstream ss(line);  //字符串流
        while(ss >> x)  sum += x;
        cout << sum << "\n";
    }
    return 0;
}