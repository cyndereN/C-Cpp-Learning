#include <iostream>
#include <string>
using namespace std;

struct student{
    string name;
    int score;
};

int main(){
    student a[100], t;
    int n;
    cin >> n;
    for(int i=1 ; i<=n ; i++)  {cin >> a[i].name; cin >> a[i].score;}
    for(int i=1 ; i<=n-1; i++){
        for(int j=1 ; j<=n-i ; j++){
            if(a[j].score < a[j+1].score){  //from high to low
                t = a[j]; a[j] = a[j+1]; a[j+1] = t;
            }
        }
    }
    for(int i=1; i<=n ; i++)  cout << a[i].name << endl;
    return 0;
}