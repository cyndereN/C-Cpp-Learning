��Ҫ����С�ں�

����Ҫ�㣺

1 ����const

2 ������ͬ��������ܱȽϳ���С��

Ϊʲô�������صȺ�setҲ��ȥ�أ�

��Ϊ��A < B false  ��B < A false  ���Ƴ�A == B


#include <iostream>
#include <set>
class Point {
public:
    double x;
    double y;
    Point() = default;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
    bool operator<(const Point& p) const {
        if (this->x < p.x)return true;
        if (this->x > p.x)return false;
        if (this->y < p.y)return true;
        return false;
    }
};
int main()
{
    std::set<Point> setData;
    setData.insert(Point(1, 1));
    setData.insert(Point(1, 2));
    setData.insert(Point(2, 1));
    setData.insert(Point(2, 2));
    setData.insert(Point(2, 2));
    //���4����ȷ��
    std::cout << setData.size() << std::endl;
    return 0;
}