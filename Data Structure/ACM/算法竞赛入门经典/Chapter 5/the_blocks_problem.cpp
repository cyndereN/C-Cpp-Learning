/*
  n blocks, numbered 0~n-1
  - move a onto b, put back the block on a and b, then put a over b
  - move a over b, put back the block on a, then put a over b (pile)
  - pile a onto b, put back the block on b, then put a (pile) over b
  - pile a over b, put a (pile) over b (pile)
  - quit, end
  print from bottom up
*/

#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn]; // Each pile[i] is a vector

void find_block(int a, int &p, int &h){
    for(p=0 ; p<n ; p++)
        for(h=0 ; h<pile[p].size() ; h++)
            if(pile[p][h]==a)  return;
}

void clear_above(int p, int h){
    for (int i=h+1 ; i<pile[p].size() ; i++){
        int b = pile[p][i];
        pile[b].push_back(b);
    }
    pile[p].resize(h+1); //Only keep elements of index [0~h]
}

void pile_onto(int p, int h, int p2){  //Move the block above pile[p][h] onto p2
    for(int i=h ; i<pile[p].size() ; i++)
        pile[p2].push_back(pile[p][i]);
    pile[p].resize(h);
}

void print(){
    for(int i=0 ; i<n ; i++){
        printf("%d:", i);
        for(int j=0 ; j<pile[i].size() ; j++)  printf(" %d", pile[i][j]);
        printf("\n");
    }
}

int main(){
    int a, b;
    cin >> n;
    string s1, s2;
    for(int i=0 ; i<n ; i++)  pile[i].push_back(i);
    while(cin >> s1 >> a >> s2 >> b){
        int pa, pb, ha, hb;
        find_block(a, pa, ha);
        find_block(b, pb, hb);
        if(pa == pb)  continue;  //Invalid
        if(s2 == "onto")  clear_above(pb, hb);
        if(s1 == "move")  clear_above(pa, ha);
        pile_onto(pa, ha, pb);
    }
    print();
    return 0;
}