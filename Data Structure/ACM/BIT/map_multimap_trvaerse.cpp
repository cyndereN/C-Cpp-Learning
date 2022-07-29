#include <bits/stdc++.h>

// 1、使用find和count函数。count函数求出某个键出现的次数，find函数返回一个迭代器，指向第一个拥有正在查找的键的实例。

// 2、使用lower_bound(key)和upper_bound(key)

// 3、使用equat_range(key)

//       返回一个迭代器的pair对象，first成员等价于lower_bound(key)，second成员等价于upper_bound(key)


using namespace std;

int main(int argc, char **argv){
    map<string,int> arr1;//定义一个空的map容器  
    
    map<string,int> arr2{  
        {"小明",10086},  
        {"小红",1008611},  
        {"小兰",123456}  
    };//使用初值列定义一个包含三个string/int的map容器  
    for(auto i:arr2) //输出所有元素  
        cout<<i.first<<" "<<i.second<<endl;  
    cout<<endl;  
    
    map<string,int> arr3(arr2);//使用一个map容器作为初始值  
    for(auto i:arr3) //输出所有元素  
        cout<<i.first<<" "<<i.second<<endl;  
    cout<<endl;  
    
    map<string,int> arr4(++arr2.begin(),arr2.end());//使用迭代器赋值  
    for(auto i:arr4) //输出所有元素  
        cout<<i.first<<" "<<i.second<<endl;  
    cout<<endl;  

    multimap<string, int> m_map;

    string s("中国"), s1("美国");

    m_map.insert(make_pair(s,50));
    m_map.insert(make_pair(s,55));
    m_map.insert(make_pair(s,60));
    m_map.insert(make_pair(s1,30));
    m_map.insert(make_pair(s1,20));
    m_map.insert(make_pair(s1,10));

    // method 1
    int k;
    multimap<string, int>::iterator m;
    m = m_map.find(s);
    for (k = 0; k!= m_map.count(s); k++, m++){
        cout << m->first << "--" << m->second << endl;
    }

    // method 2
    multimap<string,int>::iterator beg,end;
    beg = m_map.lower_bound(s1);
    end = m_map.upper_bound(s1);
    for(m = beg;m != end;m++)
        cout << m->first << "--" << m->second << endl;

    // method 3
    beg = m_map.equal_range(s).first;
    end = m_map.equal_range(s).second;
    for(m = beg;m != end;m++)
        cout<<m->first<<"--"<<m->second<<endl;


    return 0;
}