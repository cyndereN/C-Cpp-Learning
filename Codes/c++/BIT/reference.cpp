#include <iostream>
using namespace std;

void swap_cpp(int &a, int &b){
    int t = a; a = b; b = t;
}

int main(){
    int a = 3, b = 4;
    swap_cpp(a, b);
    cout << a << " " << b << "\n";
}

// in c

void swap_c(int* a, int* b){
    int t = *a; *a = *b; *b = t;
}