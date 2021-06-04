#include <bits/stdc++.h>
using namespace std;

int main(int argc, char){
    int sum = 0;
    int K, i;
    cin >> K;
    for(i = 1; K-i>=0 ; i++){
        sum += i*i;
        K -= i;
    }
    sum += K * i;
    cout << sum << endl;
    return 0;
}