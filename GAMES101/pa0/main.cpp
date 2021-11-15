#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>
#define _USE_MATH_DEFINES


int main(){

    // Basic Example of cpp
    std::cout << "Example of cpp \n";
    float a = 1.0, b = 2.0;
    std::cout << a << std::endl;
    std::cout << a/b << std::endl;
    std::cout << std::sqrt(b) << std::endl;
    std::cout << std::acos(-1) << std::endl;
    std::cout << std::sin(30.0/180.0*acos(-1)) << std::endl;

    // Example of vector
    std::cout << "Example of vector \n";
    // vector definition
    Eigen::Vector3f v(1.0f,2.0f,3.0f);
    Eigen::Vector3f w(1.0f,0.0f,0.0f);
    // vector output
    std::cout << "Example of output(v, w) \n";
    std::cout << v << std::endl;
    std::cout << w << std::endl;
    // vector add
    std::cout << "Example of add \n";
    std::cout << v + w << std::endl;
    // vector scalar multiply
    std::cout << "Example of scalar multiply \n";
    std::cout << v * 3.0f << std::endl;
    std::cout << 2.0f * v << std::endl;

    // Example of matrix
    std::cout << "Example of matrix \n";
    // matrix definition
    Eigen::Matrix3f i,j;
    i << 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0;
    j << 2.0, 3.0, 1.0, 4.0, 6.0, 5.0, 9.0, 7.0, 8.0;
    // matrix output
    std::cout << "Example of output(i, j) \n";
    std::cout << i << std::endl;
    std::cout << j << std::endl;
    // matrix add i + j
    std::cout << i+j << std::endl;
    std::cout << j-i << std::endl;
    // matrix scalar multiply i * 2.0
    std::cout << i * 2.0 << std::endl;
    // matrix multiply i * j
    std::cout << i * j << std::endl;
    // matrix multiply vector i * v
    std::cout << i * v << std::endl;

    // TO DO: 给定一个点 P =(2,1), 将该点绕原点先逆时针旋转 45 ◦ ,再平移 (1,2), 计算出
    // 变换后点的坐标(要求用齐次坐标进行计算)
    
    Eigen::Vector3f p(2.0f, 1.0f, 1.0f);
    Eigen::Matrix3f rot;
    Eigen::Matrix3f tran;
    double theta = 45.0/190.0*M_PI;
    rota << cos(theta), -1.0*sin(theta), 0,
            sin(theta), cos(theta), 0,
            0, 0, 1;
    tran << 1, 0, 1,
            0, 1, 2,
            0, 0, 1;
    p = tran * rota * p;
    std::cout << p << std::endl;
    std::cout <<  "After rotation and transform the point sits at " 
        << p[0] << "," << p[1] << std::endl;
    return 0;
}