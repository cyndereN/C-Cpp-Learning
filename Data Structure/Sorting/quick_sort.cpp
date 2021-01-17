#include <bits/stdc++.h>
using namespace std;

int a[105];


//Worst: O(n^2)
//Average: O(nlogn)
void quick_sort(int left, int right){ //from low to high
    int i, j, t, base;
    if(left > right)
        return;

    base = a[left];
    i = left;
    j = right;

    while(i!=j){
        while(a[j]>=base && i<j)  j--;
        while(a[i]<=base && i<j)  i++;

        if(i<j){
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }

    a[left] = a[i];
    a[i] = base;

    quick_sort(left,i-1);
    quick_sort(i+1,right);
}

int main(){
    int n;
    cin >> n;

    for(int i=1; i<=n; i++)  cin >> a[i];
    
    quick_sort(1,n);

    for(int i=1; i<=n; i++)  cout << a[i] << " ";

    return 0;
}