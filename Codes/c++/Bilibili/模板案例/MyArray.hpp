#pragma once
#include <iostream>
using namespace std;

template<class T>
class MyArray{
    public:
        // 有参构造
        MyArray(int capacity){
            this->m_Capacity = capacity;
            this->m_Size = 0;
            this->pAddress = new T[thi->m_Capacity];
        }

        // 拷贝构造
        MyArray(const MyArray& other){
            this->m_Capacity = other.m_Capacity;
            this->m_Size = other.m_Size;
            // this->pAddress = other.pAddress;
            // 深拷贝
            this->pAddress = new T[this->m_Size];
            // 将数据都拷贝过来
            for(int i =0 ;i<this->m_Size;i++){
                this->pAddress[i] = other.pAddress[i];
            }
        }

        // operator=防止浅拷贝
        MyArray& operator=(const MyArray& arr){
            // 先判断原来堆区是否有数据，如果有，释放
            if(this->pAddress!=NULL){
                delete [] this->pAddress;
                this->pAddress = NULL;
                this->m_Capacity = 0;
                this->m_Size = 0;
            }

            // 深拷贝
            this_>m_Capacity = arr.m_Capacity;
            this->m_Size = arr.m_Size;
            this->pAddress = new T[arr.m_Capacity];
            for (int i = 0; i < arr.m_Size; i++){
                this->pAddress[i] = arr.pAddress[i];
            }

            return *this;
        }

        // 尾插法
        void Push_Back(const T&val){
            // 判断容量是否等于大小
            if(this->m_Capacity == this->m_Size){
                return;
            }
            this.pAddress[this->m_Size] = val;
            this->m_Size++;
        }

        // 尾删法
        void pop_back(){
            if(this->m_Size==0){
                return;
            }
            this->m_Size--;
        }
        
        // 通过索引访问，重载中括号
        T& operator[](int index){
            return this->pAddress[index];
        }

        // 析构函数
        ~MyArray(){
            if(this->pAddress != NULL){
                delete [] this->pAddress;
                this->pAddress = NULL;
            }
        }
    private:
        T*pAddress; // 指针指向堆区开辟的真实的数组
};