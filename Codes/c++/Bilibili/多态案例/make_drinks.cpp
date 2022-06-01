#include <iostream>
using namespace std;

class AnstractDrinking{
public:
    // 煮水
    virtual void Boil() = 0;
    // 冲泡
    virtual void Brew() = 0;    
    // 倒入杯中
    virtual void PourInCup() = 0;
    // 辅助作料
    virtual void PutSth() = 0;

    void makeDrink(){
        Boil(); 
        Brew();
        PourInCup();
        PutSth();
    }
};

class Coffee : public AbstractDrinking{
    void Boil(){
        cout << "煮水" << endl;
    }

    void Brew(){
        cout << "冲泡咖啡" << endl;
    }

    void PourInCup(){
        cout << "倒入杯中" << endl;
    }
    void PutSth(){
        cout << "加入糖和牛奶" << endl;
    }

};

class Tea : public AbstractDrinking{
    void Boil(){
        cout << "煮水" << endl;
    }

    void Brew(){
        cout << "冲泡茶叶" << endl;
    }

    void PourInCup(){
        cout << "倒入杯中" << endl;
    }
    void PutSth(){
        cout << "加入枸杞" << endl;
    }

};

void doWork(AbstractDrinking *abs){
    abs->makeDrink();
    delete abs; // 释放
}

void test01(){
    doWork(new Coffe);
    doWork(new Tea);
}

int main(){
    system("pause");
    return 0;
}