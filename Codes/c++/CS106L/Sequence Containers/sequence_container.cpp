// Provides access to sequences of elements
/* Includes: 
    std::vector<T>, deque, list, array, forward_list
*/

#include <vector>
#include <string>
#include <iostream>
using std::vector;   using std::string;
using std::cout;     using std::endl;

void printVec(const vector<string>& v){
    cout << "{";

    for (auto elem : v) cout << elem << " ";

    cout << "}" << endl;
}

int main() {
    vector<string> names;
    names.push_back("Anna");
    names.push_back("Avery");
    printVec(names);

    names.at(0) = "Karel";
    printVec(names);

    // error
    names.at(3) = "Onno";
    printVec(names);
    
    names.clear();
    printVec(names);

    // error
    cout << names[2] << endl;
    return 0;
}

// VECTER IS THE TYPE OF SEQUENCE SHOULD BE USE BY DEFAULT
// DEQUE IS THE CHOICE WHEN MOST INSERTIONS AND DELETIONS TAKE PLACE AT THE BEGINNING OR END