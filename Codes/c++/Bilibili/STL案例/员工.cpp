#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include <string>
#include <ctime>

#define CEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker{
public:
    string m_name;
    int m_salary;
};

void createWorker(vector<Worker>& v){
    string nameSeed = "ABCDEFGHIJ";
    for(int i = 0; i<10;i++){
        Worker worker;
        worker.m_name = "employee ";
        worker.m_name += nameSeed[i];
        worker.m_salary = rand()%10001 + 10000;  // 10000~20000
        v.push_back(worker);
    }
}

void setGroup(vector<Worker>& v, multimap<int, Worker>& m){
    for(vector<Worker>::iterator it = v.begin(); it != v.end();it++){
        // 随机编号
        int deptId = rand() % 3;  // 0, 1, 2
        // 将员工插入到分组
        m.insert(make_pair(deptId, *it));
    }
}

void showWorkerByGroup(multimap<int, Worker> &m){
    cout << "CEHUA: " << endl;
    multimap<int, Worker>::iterator pos = m.find(CEHUA); 
    int count = m.count(CEHUA);
    int index = 0;
    for( ; pos!=m.end() && index < count ; pos++, index++){
        cout << "Name: " << pos->second.m_name << "; Salary: " << pos->second.m_salary << endl;
    }
}

int main(){
    srand((unsigned int)time(NULL));

    vector<Worker> workers;

    createWorker(workers);
    
    //分组
    multimap<int, Worker> mWorkers;
    setGroup(workers, mWorkers);

    // 测试
    for(vector<Worker>::iterator it = workers.begin(); it != workers.end();it++){
        cout << "name: " << it->m_name << " " << it->m_salary << endl;
    }
    
    // 打印
    showWorkerByGroup(mWorkers);

    return 0;
}