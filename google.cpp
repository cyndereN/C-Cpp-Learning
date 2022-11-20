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
