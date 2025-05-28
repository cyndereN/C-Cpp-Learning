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

You have a triangle defined by the 3D points P1, P2 and P3, and another separate point P4. You do not have access to the normal of the triangle. How do you determine on which side of the triangle point P4 is? (Point traversal order is from 1 to 3)

1. Calculate the normal vector N of the triangle defined by points P1, P2, and P3. You can calculate the normal vector as follows:

N = (P2 - P1) x (P3 - P1)

where "x" denotes the cross product operator.

2. Calculate the vector V from any point on the triangle, for example, P1, to the point P4:

V = P4 - P1

3. Calculate the dot product between the normal vector N and the vector V:

dot = N . V

4. If the dot product is positive, then point P4 is on the same side of the triangle as the normal vector N. If the dot product is negative, then point P4 is on the opposite side of the triangle as the normal vector N.

5. If the dot product is zero, then point P4 is on the plane of the triangle. To determine whether point P4 is inside or outside the triangle, you can perform a barycentric coordinate test.

### 4.4扩展 判断点在扇形范围内与否

在二维中，检测点是否在扇形(circular sector)内，设扇形的顶点为p，物品位置为o，半径为r，从方向u两边展开角度theta平分扇形。
问题等同于检测o和p的距离小于r，及p-p的方向在u两边theta的角度范围内。


```cpp
// Naive
bool IsPointInCircularSector(
    float px, float py, float ux, float uy, float r, float theta,
    float ox, float oy)
{
    assert(cosTheta > -1 && cosTheta < 1);
    assert(squaredR > 0.0f);
 
    // D = O - P
    float dx = ox - px;
    float dy = oy - py;
 
    // |D| = (dx^2 + dy^2)^0.5
    float length = sqrt(dx * dx + dy * dy);
 
    // |D| > r
    if (length > r)
        return false;
 
    // Normalize D
    dx /= length;
    dy /= length;
 
    // acos(D dot U) < theta
    return acos(dx * ux + dy * uy) < theta;
}
```

注意优化：

如果r为常数，我们可以预计算r^2。

另外，如果theta是常数，我们可以预计算cos(theta)，然后用dx * ux + dy * uy > cos(Theta)来代替acos(dx * ux + dy * uy) < theta。因为cos(theta)在[0, pai]范围内单调递减

此外，由于除法一般较乘法慢得多，可以把除以|o-p|移到不等式右边，由于其非负所以不用变号

```cpp
// Basic: use squareR and cosTheta as parameters, move sqrt() later, eliminate division
bool IsPointInCircularSector1(
    float px, float py, float ux, float uy, float squaredR, float cosTheta,
    float ox, float oy)
{
    assert(cosTheta > -1 && cosTheta < 1);
    assert(squaredR > 0.0f);
 
    // D = O - P
    float dx = ox - px;
    float dy = oy - py;
 
    // |D|^2 = (dx^2 + dy^2)
    float squaredLength = dx * dx + dy * dy;
 
    // |D|^2 > r^2
    if (squaredLength > squaredR)
        return false;
 
    // |D|
    // still need to calculate sqrt(), however if return false earlier, no need to calculate
    float length = sqrt(squaredLength);
 
    // D dot U > |D| cos(theta)
    return dx * ux + dy * uy > length * cosTheta;
}
// 注意，虽然比较长度时不用开平方，在夹角的检测里还是要算一次开平方，但这也比必须算开平方好，因为第一个检测失败就不用算了。
```

将来优化：

去除开平方，可以分情况讨论不等号左右两侧的正负性 https://www.cnblogs.com/miloyip/archive/2013/04/19/3029852.html

优化浮点比较和分支

### 4.5 磁带文件存放优化

### 4.6 桶中取黑白球

### 4.7 蚂蚁爬杆

碰撞次数 = 所有向右的蚂蚁+所有向左的蚂蚁

### 4.8 三角形测试用例

8 bits
第0位表示等腰，第1位表示等边，等等。各位取1表示该状态为真，其中第7位表示该状态是否为三角形，是则为1，否则为0。那么便可很方便的表示几种状态同时存在，如10010001则表示这是一个直角等腰三角形。剩余的第6位和第5位可以留作错误编码，比如用于表示两边之和小于第三边等。


作为一名测试者，要测试一个程序，具体的工作就是要分析程序可能出现的漏洞，并编制测试用例来有针对性的进行测试，观察程序是否正常工作。通常测试可以分为以下三个方面：程序在正常输入下的功能测试，测试程序在非法输入时的表现，测试程序对边界值附近输入的处理。

### 4.9 数独知多少

### 4.10 数字哑谜和回文

第一题：找出符合条件的九位数，每位数互不相同（1~9的某个排列），满足高n位能被n整除。例如abcdefghi，高两位ab能被2整除，高三位abc能被3整除，以此类推。能不能找出所有的解？

解法1：穷举9^9，然后使用剪枝避免不必要的运算，如b、d、f、h为奇数时就可以直接跳过，大大缩小了要检验的区间。

解法2：https://www.cnblogs.com/Linkabox/p/3361437.html

第二题：有这样一个乘法算式：人过大佛寺*我=寺佛大过人
这里面每一个汉字代表一个数字，并且不同汉字代表的数字不同，找出这些数字来？

```cpp
#include <string.h>
#include <stdio.h>

int main()
{
    bool flag;
    bool IsUsed[10];
    int number,revert_number,t,v;
    for (number =0;number < 100000;number++)
    {
        flag =true;
        memset(IsUsed,0,sizeof(IsUsed));
        t=number;
        revert_number=0;
        for (int i=0;i<5;++i)//得到翻转数字
        {
            v=t%10;
            revert_number= revert_number* 10 +v;
            t/=10;
            if(IsUsed[v])    //确保没有重复的数字，有重复的下面检验直接跳过
                flag=false;
            else
                IsUsed[v]=1;    
        }
        if (flag && (revert_number % number == 0))//没有重复数字且没有余数
        {
            v=revert_number /number;
            if (v<10 && !IsUsed[v])
            {
                printf("%d * %d = %d\n",number,v,revert_number);
            }
        }
    }
    return 0;
}

//21978 * 4 = 87912
//请按任意键继续. . .
```


### 4.11 扫雷