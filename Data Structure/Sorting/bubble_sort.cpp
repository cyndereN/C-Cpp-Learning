#include <iostream>
using namespace std;

//O(n^2)
int main(){
    int a[1005], t, n;
    cin >> n;
    for(int i=1 ; i<=n ; i++)  cin >> a[i];
    for(int i=1 ; i<=n-1; i++){
        for(int j=1 ; j<=n-i ; j++){
            if(a[j]<a[j+1]){  //from high to low
                t = a[j]; a[j] = a[j+1]; a[j+1] = t;
            }
        }
    }
    for(int i=1; i<=n ; i++)  cout << a[i] << endl;
    return 0;
}