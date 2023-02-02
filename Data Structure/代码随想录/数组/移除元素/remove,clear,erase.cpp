#include <vector>
#include <string>
#include <iostream>
#include <typeinfo>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> vec;
    cout << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;

    vec.push_back(1); //没有push_back，下面的语句将发生段错误, 因为vec[0]的原因，上面的vec并没分配内存
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    vec.push_back(2);
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    vec.push_back(3);
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    vec.push_back(4);
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    vec.push_back(5);
    vec.push_back(6);
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    cout << "vec[10] = " << vec[10] << endl;
    cout << vec[0] << " " << vec[10] << endl;

    cout << &vec[0] << endl;

    decltype(auto) lamb = []()
    { return 5; };

    cout << lamb << endl;
    cout << typeid(lamb).name() << endl;
    cout << typeid(vec).name() << endl;
    cout << typeid(vec[0]).name() << endl;
    // cout << typeid([](){return 5;}).name() << endl;

    // vec.assign(5, 100);
    // for (auto it : vec)
    // {
    //     cout << it << " ";
    // }
    // cout << endl;

    // cout << &vec[0] << endl;
    
    // cout << "\n---------test assgin----------" << endl;
    // vec.assign(10, 100);
    for (auto it : vec)
    {
        cout << it << " ";
    }
    cout << endl;

    cout << &vec[0] << endl;
    cout << "size = " << vec.size() << ", capacity " << vec.capacity() << endl;

    cout << "\n---------test remove----------" << endl;
    // vec.push_back(10);
    auto new_end_vec = std::remove(vec.begin(), vec.end(), 1);
    for (auto it : vec)
    {
        cout << it << " ";
    }
    cout << endl;
    cout << &vec[0] << endl;
    cout << "size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    cout << "new end iter index = " << distance(vec.begin(), new_end_vec) << endl;
    // 将没被删除的元素放在链表的开始位置，并返回一个指向新的超尾值的迭代器。
    cout << "\n---------test clear----------" << endl;
    vec.clear();
    cout << "vec[0] = " << vec[0] << ",size = " << vec.size() << ", capacity " << vec.capacity() << endl;
    // vec.shrink_to_fit();
    vector<int>().swap(vec); //效果和shrink_to_fit类似，回收内存
    cout << "size = " << vec.size() << ", capacity " << vec.capacity() << endl;


    vector<int> v;
   
    v.push_back(20);
    v.push_back(10);
    v.push_back(30);
    v.push_back(20);
    v.push_back(40);
    v.push_back(20);
    v.push_back(10);

    cout << "\n---------test remove----------" << endl;
        for(int i=0;i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\nsize = " << v.size() << ", capacity " << v.capacity() << endl;

    vector<int>::iterator new_end_v;
    new_end_v = std::remove(v.begin(), v.end(), 20);

    for(int i=0;i<v.size(); i++){
        cout << v[i] << " ";
    }

    cout << "\nsize = " << v.size() << ", capacity " << v.capacity() << endl;
    cout << "new end iter index = " << distance(v.begin(), new_end_v) << endl;

    cout << "\n---------test remove+erase----------" << endl;
    // changes container size
    // O(n) https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    v.erase(new_end_v, v.end());
    for(int i=0;i<v.size(); i++){
        cout << v[i] << " ";
    }

    cout << "\nsize = " << v.size() << ", capacity " << v.capacity() << endl;
    cout << "\n---------test erase----------" << endl;
  
  //This effectively reduces the container size by the number of elements removed, which are destroyed. 这个操作会让容器的size减小，减小的个数为删除的元素个数。
  // 迭代器用于erase删除元素后，其后会失效，即不能再用该迭代器操作向量。

  vector<int> vv;
	vv.push_back(100);
	vv.push_back(300);
	vv.push_back(300);
	vv.push_back(300);
	vv.push_back(300);
	vv.push_back(500);

  

	vector<int>::iterator itor;

  for( itor = vv.begin(); itor != vv.end(); itor++)
	{
		cout<< *itor <<" ";
	}	

  cout << "\nsize = " << vv.size() << ", capacity " << vv.capacity() << endl;
  
	for( itor = vv.begin(); itor != vv.end(); itor++ )
	{
		if( *itor == 300 )
		{
			itor = vv.erase(itor);
		}
	}
 
	for( itor = vv.begin(); itor != vv.end(); itor++)
	{
		cout<< *itor <<" ";
	}	

  // 迭代器itor指向第一个元素100，不满足条件，itor++；

  // 迭代器itor指向第二个元素300，满足条件，调用erase删除300，之后vec是{ 100  300 300 300 500 }

  // 迭代器itor++，指向第三个元素，会调过一个300，满足条件，调用erase，删除300，之后vec是 { 100 300 300 500 }

  // 迭代器itor++，指向第四个元素，指向500，所以最终vec中的数据就是{ 100 300 300 500 }

  // 主要是vec中的数据不断变化，但是itor的指向一直在增加的缘故

  cout << "\nsize = " << vv.size() << ", capacity " << vv.capacity() << endl;

  vector<int> vvv;
	vvv.push_back(100);
	vvv.push_back(300);
	vvv.push_back(300);
	vvv.push_back(300);
	vvv.push_back(300);
	vvv.push_back(500);
  
  itor = vvv.begin();
	while( itor != vvv.end() )
	{
		if( *itor == 300 )
		{
			itor = vvv.erase(itor);
		}
		else
		{
			itor++;
		}
	}
	for( itor = vvv.begin(); itor != vvv.end(); itor++)
	{
		cout<< *itor <<" ";
	}	
  cout << "\nsize = " << vvv.size() << ", capacity " << vvv.capacity() << endl;

  

  
}