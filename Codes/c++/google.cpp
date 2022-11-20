#include <iostream>
#include <string>

using namespace std;

int solution(string S) {
  cerr << "Tip: Use cerr to write debug messages on the output tab.";
  
  
  int count = 0;
  int index = 0;
  
  // String must start with a
  char lastChar = 'c';
  
  // simulation
  while (index<S.length()){
    char currentChar = S[index];
    
    if (lastChar == 'c' && currentChar != 'a'){
      lastChar = 'a';
      count += 1;
    }
    else if (lastChar == 'a' && currentChar != 'b'){
      lastChar = 'b';
      count += 1;
    }
      
    else if (lastChar == 'b' && currentChar != 'c'){
      lastChar = 'c';
      count += 1;
    }
   
    else{
      lastChar = currentChar;
      index += 1;
    }
      
  }
  return count;
}


//----------------------------------------------------------------
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int solution(vector<int> A) {
  cerr << "Tip: Use cerr to write debug messages on the output tab.";
  
  int size = A.size();
  
  if (size < 4) return -1;
  
  map<int, int> lengthCounts;
  
  for(int i = 0; i < size; i++){
    ++lengthCounts[A[i]];
  }

  for (const auto &pair : lengthCounts){
    if(pair.second >= 4)  return 0;
  }

  // Otherwise, remove all keys with counts less than 2, and return the difference of last 2 elements

  vector<int> keysToErase;
  
  for (const auto &pair : lengthCounts){
    if(pair.second < 2){
      keysToErase.push_back(pair.first);
    }
  }

  for (int key:keysToErase)  lengthCounts.erase(key);

  if (lengthCounts.size() < 2)  return -1;

  auto rit = lengthCounts.crbegin();
  int value1 = rit->first;
  rit++;
  int value2 = rit->first;
  
  return value1 - value2;
}
/*
报错原因：采用erase移除迭代器后，迭代器的值变为-572662307，无法作为迭代器继续运算。
详细：当程序执行到 stu_map.erase(itor) 时，满足条件的第一个元素被删除，从而导致 itor 指针被删除，使其不指向任何元素。针对该问题我们首先想到的就是在删除指针之前，对其进行备份，C++ 将这个临时变量直接建立在 erase 实现里。
因此将stu_map.erase(itor)改为stu_map.erase(itor--)即可
*/
#include <map>
#include <iostream>
using namespace std;
 
int main()
{
	// 初始化变量
	map<int, char> stu_map;
 
	// 变量的赋值
	stu_map[10010] = 'm';
	stu_map[10011] = 'f';
	stu_map[10012] = 'f';
	stu_map[10013] = 'm';
	stu_map[10014] = 'f';
	stu_map[10015] = 'm';
 
	// 循环删除value为“f”的元素
	map<int, char>::iterator itor;
	for (itor = stu_map.begin(); itor != stu_map.end(); itor++)
	{
		if (itor->second == 'f')
		{
			// 移除元素
			stu_map.erase(itor--);
		}
		else 
		{
			int stu_num = itor->first;
			char stu_sex = itor->second;
 
			cout << "key = " << stu_num << ", value = " << stu_sex << endl;
		}
	}
 
	return 0;
}