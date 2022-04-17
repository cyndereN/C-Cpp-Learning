#include <iostream>
using namespace std;

//O(n+m)

int main(){
    int book[1005], i, j, t, n;
    for(int i=0; i<1000; i++)  book[i] = 0;
    cin >> n;
    
    for(int i=1; i<n; i++){
        cin >> t;
        book[t]++;
    }

    for(i=1000; i>=0; i--){
        for(j=1; j<book[i]; j++)
            cout << i << endl;
    }
    
    return 0;

}
