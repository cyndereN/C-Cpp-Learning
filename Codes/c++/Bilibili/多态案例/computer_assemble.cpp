#include <iostream>
// 抽象不同零件类
using namespace std;
class CPU{
public:
    // 抽象的计算函数
    virtual void calculate() = 0;

};

class GPU{
public:
    // 抽象的显示函数
    virtual void display() = 0;

};

class Memory{
public:
    // 抽象的存储函数
    virtual void store() = 0;
};

class Computer{
public:
    Computer(CPU* cpu, GPU* gpu, Memory* mem){
        this->cpu = cpu;
        this->gpu = gpu;
        this->mem = mem;
    }

    ~Computer(){
        if(this->cpu != NULL){
            delete this->cpu;
            this->cpu = NULL;
        }
        if(this->gpu != NULL){
            delete this->gpu;
            this->gpu = NULL;
        }
        if(this->mem != NULL){
            delete this->mem;
            this->mem = NULL;
        }
    }

    void work(){
        this->cpu->calculate();
        this->gpu->display();
        this->mem->store();
    }

private:
    CPU* cpu;
    GPU* gpu;
    Memory* mem;
};

class IntelCPU : public CPU{
public:
    virtual void calculate(){
        cout << "intel cpu开始工作" << endl;
    }
};

class IntelGPU : public GPU {
public:
    virtual void display() {
        cout << "intel gpu开始工作" << endl;
    }
};

class IntelMemory : public Memory{
public:
    virtual void store() {
        cout << "intel memory开始工作" << endl;
    }
};

class LenovoMemory : public Memory{
public:
    virtual void store() {
        cout << "Lenovo memory开始工作" << endl;
    }
};


void test01(){
    CPU* intelCPU = new  IntelCPU;
    GPU* intelGPU = new IntelGPU;
    Memory* intelMem = new IntelMemory;

    // 组装电脑
    Computer* computer1 = new Computer(intelCPU, intelGPU, intelMem);
    computer1 -> work();
    delete computer1;

    Computer* computer2 = new Computer(new IntelCPU, new IntelGPU, new LenovoMemory);
    computer2->work();
    delete computer2;
}


int main(){
    test01();
    return 0;
}