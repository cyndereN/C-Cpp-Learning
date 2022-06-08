#include <iostream>
using namespace std;
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

// 5名选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除最低分，取平均
class Person{
    public:
        Person(string name, int score){
            this->m_name = name;
            this->m_score = score;
        }

        string m_name;
        int m_score;
};

void creatPerson(vector<Person> &v){
    string nameSeed = "ABCDE";
    for(int i = 0; i< 5; i++){
        string name = "player";
        name+=nameSeed[i];
        int score = 0;

        Person p(name, score);
        v.push_back(p);
    }
}

void setScore(vector<Person>&v){
    for(vector<Person>::iterator it = v.begin(); it!=v.end(); it++){
        // 将分数放到deque中
        deque<int> d;
        for(int i=0;i<10;i++){
            int score = rand()%41+ 60; // 60~100
            d.push_back(score);
        }
       

        // 排序
        sort(d.begin(), d.end());

        // 去除最高分最低分
        d.pop_back(); d.pop_front();

        int sum = 0;

        for(deque<int>::iterator dit = d.begin(); dit!=d.end(); dit++){
            sum += *dit;
        }
        
        int avg = sum/d.size();
        it->m_score = avg;
    }


    
}


int main(){

    // 随机数种子
    srand((unsigned int)time(NULL));
    // 创建五名选手
    vector<Person> v;
    creatPerson(v);

    setScore(v);


    for(vector<Person>::iterator it = v.begin(); it!=v.end(); it++){
        cout << "姓名: " << (*it).m_name << "分数: " << (*it).m_score << endl;
    }

    

    return 0;
}