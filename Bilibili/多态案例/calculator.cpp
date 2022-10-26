// 多态的优点：
// · 代码组织结构清晰
// · 可读性强
// · 利用前期和后期的扩展以及维护

#include <iostream>
using namespace std;

// 分别利用普通写法和多态技术实现

// 普通
class Calculator{
public:
    int getResult(string oper){
        if (oper=="+"){
            return m_Num1 + m_Num2;
        }
        else if (oper == "-"){
            return m_Num1 - m_Num2;
        }
        else if (oper == "*"){
            return m_Num1 * m_Num2;
        }

        // 如果想扩展新的功能，需要修改原码
        // 在真实开发中，提倡开闭原则
        // 开闭原则：对扩展进行开发，对修改进行关闭
    }
    
    int m_Num1;
    int m_Num2;
};

void test01(){
    Calculator c;
    c.m_Num1 = 10;
    c.m_Num2 = 10;
    c.getResult("+");

}


// 利用多态实现计算器
// 实现计算器抽象类
class AbstractCalculator{
public:
    virtual int getResult(){
        return 0;
    }

    int m_Num1;
    int m_Num2;
};

class AddCalculator : public AbstractCalculator{
public:
    int getResult(){
        return m_Num1 + m_Num2;
    }
};

class SubCalculator : public AbstractCalculator{
public:
    int getResult(){
        return m_Num1 - m_Num2;
    }
};

class MulCalculator : public AbstractCalculator{
public:
    int getResult(){
        return m_Num1 * m_Num2;
    }
};

void test02(){
    // 多态使用条件
    // 父类指针引用指向子类对象
    // 加法运算
    AbstractCalculator *abc = new AddCalculator;
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    abc->getResult();
    delete abc;
    
    abc = new SubCalculator; 
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    abc->getResult();
    delete abc;

    abc = new MulCalculator; 
    abc->m_Num1 = 10;
    abc->m_Num2 = 10;
    abc->getResult();
    delete abc;
}

int main(){
    test02();
    system("pause");
    return 0;
}