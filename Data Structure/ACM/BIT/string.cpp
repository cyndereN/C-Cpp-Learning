#include <iostream>
#include <string>
using namespace std;

int main(){
    string str1 = "Hello";
    char str2[] = "world";
    string str3;
    str3.push_back('!');
    cout << str1 << " " << str2 << str3 << endl;
    return 0;
}


str.length(); str.size(); //O(n)
str.insert(str.begin(), 'a'); //Insert at iterator O(n)
str.insert(1, "aaa"); //Insert at index[1] O(1)
str.c_str(); //Return C string for printf O(n)
str.append(str2); str += str2;  //O(n)
str.compare(str2); //strcmp(str, str2)
str == str2; //strcmp(str, str2) == 0;
str += 'a'; //str.push_back('a');