#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>

using std::string;  using std::cin;
using std::cout;    using std::endl;
using std::vector;     using std::stringstream;
using std::set;

const int elemToFind = 5;

void printVec (const vector<int>& v){
    for (auto elem : v){
        cout << elem << " ";
    }
    cout << endl; 
}

int main() {
    vector<int> vec{3,1,4,1,5,9,2,6,5,3};

    // we can use iterators in algorithms like sort to sort a vecotr
    std::sort(vec.begin(), vec.end());


    // we can also use the find algorithm to look for an element
    // in a collection and return an iterator to it
    vector<int>::iterator it = std::find(vec.begin(), vec.end(), elemToFind);
    if(it != vec.end()) {
       cout << "Found elem " << *it << endl;
    } else {
       cout << "Element not found " << endl;
    }



    set<int> mySet{4,1,3,5,55,5, 9, 22, 19, 28};

    // we can iterate through a range of elements in
    // a sorted collection

    // lower_bound: returns an iterator to the first element not less than the given key
    // upper_bound : returns an iterator to the first element greater than the given key

    set<int>::iterator iter = mySet.lower_bound(7);
    set<int>::iterator end = mySet.upper_bound(28);

    while(iter != end) {
        // index = std::distance(vec.begin(), iter); 获得索引
        cout << *iter << endl;
        ++iter;
    }

    return 0;
}
