## 第4章 数学之趣 ———— 数学游戏的乐趣

### 4.1 金刚坐飞机

乘客按1,2...N的顺序上飞机，但是有一人插队并随机坐了。假如其他人也随机坐了/先坐自己的，如果被占了就随机选，第i个乘客坐到自己位置的概率分别是多少？

问题1：1/N
问题2：https://cloud.tencent.com/developer/article/1062061

### 4.2 瓷砖覆盖地板

地板是NxM的，能否用1x2的瓷砖覆盖?

1. N=1，M为偶数可以，M/2块
2. NxM为奇数，不行
3. N和M至少有一个为偶数，可以简单重复N次1中的做法，NM/2块

### 4.3 买票找零

每张球票50，n个人有50，n个人有100，一开始没零钱，问这2n个人有多少种排队方式，使得找的开钱？

任意时刻，手持100的比手持50的少，类似括号匹配。 Catalan数

### 4.4 点是否在三角形内

解法1：三角形的面积等于三个点的面积之和，如果点在三角形内，那么三个点的面积之和等于点到三个点的面积之和。如果点在三角形外，那么三个点的面积之和大于点到三个点的面积之和。

```cpp
struct point{
    double x;
    double y;
};

double area(point A, point B, point C){

    double a, b, c = 0;

    // 计算三角形边长分别为a,b,c
    Compute(A,B,C,a,b,c);

    double p = (a+b+c)/2;
    return sqrt(p*(p-a)*(p-b)*(p-c)); // 海伦公式

    bool isInTriangle(point A, point B, point C, point D){
        return(area(A,B,C) >= area(A,B,D) + area(A,C,D) + area(B,C,D));
    }
    
}
```

解法2：叉乘

D在AB,BC,CA的同侧，那么D在三角形内

假设三角形的三个点按照顺时针（或者逆时针）顺序是A,B,C。对于某一点P，求出三个向量PA,PB,PC, 然后计算以下三个叉乘（^表示叉乘符号）：

t1 = AD^AB,
t2 = BD^BC,
t3 = CD^CA,
如果t1，t2，t3同号（同正或同负），那么P在三角形内部，否则在外部。


```python
import numpy as np

def inTri(a, b, c, p):
    ab = b-a
    ap = p-a
    bc = c-b
    bp = p-b
    ca = a-c
    cp = p-c
    // 此处依赖a,b,c位置关系，如果是逆时针，需要改变符号
    if np.cross(ab,ap)>0 and np.cross(bc,bp)>0 and np.cross(ca,cp)>0:    # 在三角形内部
        return 1
    if np.cross(ab,ap) * np.cross(bc,bp) * np.cross(ca,cp) == 0:         # 在边上
        return 0
    return -1                                                            # 在三角形外部

if __name__=='__main__':
    # 给出一个p点在三角形外部的示例
    a = np.array([0,0])
    b = np.array([1,0])
    c = np.array([0,1])
    p = np.array([1,1])
    ans = inTri(a,b,c,p)
    print(ans)    # 最终输出为-1

```

解法3：重心坐标
所以对于平面内任意一点，都可以由如下方程来表示

P = A +  u * (C – A) + v * (B - A) // 方程1

如果系数u或v为负值，那么相当于朝相反的方向移动，即BA或CA方向。那么如果想让P位于三角形ABC内部，u和v必须满足什么条件呢？有如下三个条件

u >= 0

v >= 0

u + v <= 1

几个边界情况，当u = 0且v = 0时，就是点A，当u = 0,v = 1时，就是点B，而当u = 1, v = 0时，就是点C

整理方程1得到P – A = u(C - A) + v(B - A)

令v0 = C – A, v1 = B – A, v2 = P – A，则v2 = u * v0 + v * v1，现在是一个方程，两个未知数，无法解出u和v，将等式两边分别点乘v0和v1的到两个等式

(v2) • v0 = (u * v0 + v * v1) • v0

(v2) • v1 = (u * v0 + v * v1) • v1

注意到这里u和v是数，而v0，v1和v2是向量，所以可以将点积展开得到下面的式子。

v2 • v0 = u * (v0 • v0) + v * (v1 • v0)  // 式1

v2 • v1 = u * (v0 • v1) + v * (v1• v1)   // 式2

解这个方程得到

u = ((v1•v1)(v2•v0)-(v1•v0)(v2•v1)) / ((v0•v0)(v1•v1) - (v0•v1)(v1•v0))

v = ((v0•v0)(v2•v1)-(v0•v1)(v2•v0)) / ((v0•v0)(v1•v1) - (v0•v1)(v1•v0))


```cpp
// Determine whether point P in triangle ABC
bool PointinTriangle(Vector3 A, Vector3 B, Vector3 C, Vector3 P)
{
    Vector3 v0 = C - A ;
    Vector3 v1 = B - A ;
    Vector3 v2 = P - A ;

    float dot00 = v0.Dot(v0) ;
    float dot01 = v0.Dot(v1) ;
    float dot02 = v0.Dot(v2) ;
    float dot11 = v1.Dot(v1) ;
    float dot12 = v1.Dot(v2) ;

    float inverDeno = 1 / (dot00 * dot11 - dot01 * dot01) ;

    float u = (dot11 * dot02 - dot01 * dot12) * inverDeno ;
    if (u < 0 || u > 1) // if u out of range, return directly
    {
        return false ;
    }

    float v = (dot00 * dot12 - dot01 * dot02) * inverDeno ;
    if (v < 0 || v > 1) // if v out of range, return directly
    {
        return false ;
    }

    return u + v <= 1 ;
}
```

### 4.4扩展 判断点在平面哪侧

### 4.4扩展 判断点在扇形范围内与否

### 4.5 磁带文件存放优化

### 4.6 桶中取黑白球

### 4.7 蚂蚁爬杆