#include<iostream>  
#include<map>  
#include<algorithm>  
#include<utility>  
using namespace std;  
  
int main()  
{  
    map<string,int> arr;  
    map<string,int> buf{{"红",255},{"橙",254},{"黄",253}};  
    
    arr.insert(make_pair("小明",123456));//插入单个值  
    arr.insert({"小红",123}); //用初值列插入单个值  
    
    arr.insert({make_pair("小兰",1234),  
    make_pair("小黑",9876) }); //使用初值列插入多个值  
    /*等价于 arr.insert({ {"小兰",1234}, 
    {"小黑",9876} }); */  
    
    arr.insert(buf.begin(),buf.end()); //使用迭代器插入其他map容器的值  
    
    pair<map<string,int>::iterator,bool> ret;  
    ret = arr.insert(pair<string,int>("小红",123456));  
    if(ret.second == false){  
        cout<<"This value already exists,insert error---";  
        cout<<"   key/value: "<<ret.first->first<<" "<<ret.first->second<<endl;  
    } //检查插入的值是否已经存在，注意返回的是已经存在的值  
    
    map<string,int>::iterator it = arr.begin(); //带提示位置的插入，正确的提示可以让插入更高效  
    arr.insert(it,make_pair("小白",333));  
    
    map<string,int>::iterator iter;  
    iter = arr.insert(it,make_pair("小红",333));//带提示位置的插入，如果重复则返回已经存在的值的迭代器，否则返回插入的值的迭代器  
    cout<<iter->first <<" "<<iter->second <<endl;  
    
    map<string,int> mymap;  
    mymap.insert(arr.begin(),arr.find("小白")); //范围内插入  
    
    cout<<endl;  
    for(auto&i:arr) //输出arr容器的值  
        cout<<i.first<<" "<<i.second<<endl;  
    cout<<endl;  

    for(auto&i:mymap) //输出mymap容器的值  
        cout<<i.first<<" "<<i.second<<endl;  
    cout<<endl;  
}  

/*
This value already exists,insert error— key/value: 小红 123
小红 123

小兰 1234
小明 123456
小白 333
小红 123
小黑 9876
橙 254
红 255
黄 253

小兰 1234
小明 123456
*/

struct rgb{  
    int r;  
    int g;  
    int b;  
    string color;  
}RGB1,RGB2;  
  
int main()  
{  
    map<int,rgb> rainbow;  
    rainbow = {  
        {1,{255,0,0,"red"}},  
        {3,{255,255,0,"yellow"}},  
        {4,{0,255,0,"green"}},  
        {6,{0,0,255,"blue"}},  
        {7,{255,0,255,"purple"}}  
    };  
    
    RGB1 = {255,125,0,"orange"};  
    rainbow.emplace(2, RGB1); //安放一个值  
    //相当于 rainbow.insert(make_pair(2,RGB1));  
    
    RGB2 = {0,255,255,"cyan"};  
    map<int,rgb>::iterator it = rainbow.begin();  
    advance(it,4); //将迭代器 it 向后移动四下  
    rainbow.emplace_hint(it,5,RGB2); //带提示的安放，提示恰当可以提高效率  
    //相当于 rainbow.insert(it,make_pair(5,RGB2));  
    
    for(auto&i:rainbow)  
        cout<<i.first<<" "<<i.second.color<<":"<<i.second.r<<","<<i.second.g<<","<<i.second.b<<endl;  


    return 0;
}  

/*
1 红:255,0,0
2 橙:255,125,0
3 黄:255,255,0
4 绿:0,255,0
5 青:0,255,255
6 蓝:0,0,255
7 紫:255,0,255
*/