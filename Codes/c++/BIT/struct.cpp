#include <iostream>
#include <algorithm>
using namespace std;

//Point a, b(1,2) ==> a(0, 0) ; b(1, 2)
struct Point{
    int x, y;    //构造函数(ctor)，无返回值
    //Point(int x=0, int y=0) { this->x = x; this->y = y; }
    Point(int x=0, int y=0):x(x),y(y) {}  //把成员变量x初始化为参数x，成员变量y初始化为参数y
};

Point operator + (const Point& A, const Point& B){
    return Point(A.x+B.x, A.y+B.y);
}

ostream& operator << (ostream &out, const Point& p){
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

bool operator < (Point a, Point b){
    if(a.x!=b.x){
        return a.x < b.x;
    }
    return a.y < b.y;
}


int main(){
    Point a, b(1,2);
    a.x=3;
    cout << a+b <<"\n";

    Point points[1000];
    points[0] < points[1];
    sort(points, points + 10);
    return 0;
}



//----------------------------
struct node{
    int number;
    node* next;
    node(int _number = 0, node* _next = NULL){
        number = _number;
        next = _next;
    }
};

int main(){
    node a = node(0);
    node* b = new node(1, &a);
    return 0;
}
