#include <iostream>
#include <string>
#include <map>
#include <sstream>

// Map/set: keys in sorted order, faster to iterate through a arange of elements
// Unordered map/set: Faster to access individual elements by key


using std::string;  using std::cin;
using std::cout;    using std::endl;

// GetLine asks the user to type in a response at the command line. It returns
// the user input as a string.
string GetLine() {
    string response;
    std::getline(cin, response);
    return response;
}

int main() {
    // We will use a map to count the appearances of words, as well as how many
    // times we encounter them.
    std::map<string, int> frequencyMap;

    cout << "Enter words." << endl;
    while (true) {
        cout << "> ";
        string response = GetLine();
        if (response.empty()) break;
        std::istringstream stream(response);
        string word;
        while(stream >> word) {
            // This single line is doing a ton of work. The square bracket notation for
            // accessing values in maps will return a reference to the value associated
            // with the specified key. We can then modify it with ++ directly.
            //
            // However, if response is not already a key in the map, the square brackets
            // do a bit of extra work first. They automatically insert a new key-value
            // pair into the map, where the key is response and the value is a
            // reasonable default value -- in the case of integers, 0.

            frequencyMap[word]; //auotomatically create an entry and default initialize
            ++frequencyMap[word];
        }

    }

    cout << "Enter words to look up." << endl;
    while (true) {
        cout << "> ";
        string response = GetLine();
        if (response.empty()) break;

        // Returns the number of keys equal to response.
        // In anything but a multimap/multiset, this is
        // either going to be 1 or 0.
        if (frequencyMap.count(response)) {
            cout << frequencyMap[response] << " entries found." << endl;  // or use frequencyMap.at(response) 
            // []不检查索引是否有效,而at()在遇到无效索引时会抛出out_of_range异常.
        } else {
            cout << "None." << endl;
        }
    }

    return 0;
}


