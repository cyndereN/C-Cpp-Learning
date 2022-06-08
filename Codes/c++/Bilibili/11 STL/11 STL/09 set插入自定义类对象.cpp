需要重载小于号

重载要点：

1 两个const

2 两个不同的类必须能比较出大小来

为什么不用重载等号set也能去重？

因为由A < B false  ，B < A false  可推出A == B


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
    //输出4是正确的
    std::cout << setData.size() << std::endl;
    return 0;
}