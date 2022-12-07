#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMaximumAmount' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY quantity
 *  2. INTEGER m
 *
 *  e.g., n = 3, m = 4, quantity = [1, 2, 4] maximum = 11
 *
 */

long getMaximumAmount(vector<int> quantity, int m) {
    
    // Keep track of current maximum revenue in a heap
    priority_queue<int> max_heap;
    
    long max_revenue = 0;
    
    for (int i = 0; i < quantity.size(); i++){
        max_heap.push(quantity[i]);
    }
    
    while (m > 0){
        m--;
        int cur_revenue = max_heap.top();
        max_heap.pop();
        
        max_revenue += cur_revenue;
        
        max_heap.push(cur_revenue-1);
    }
    
    return max_revenue;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string quantity_count_temp;
    getline(cin, quantity_count_temp);

    int quantity_count = stoi(ltrim(rtrim(quantity_count_temp)));

    vector<int> quantity(quantity_count);

    for (int i = 0; i < quantity_count; i++) {
        string quantity_item_temp;
        getline(cin, quantity_item_temp);

        int quantity_item = stoi(ltrim(rtrim(quantity_item_temp)));

        quantity[i] = quantity_item;
    }

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    long result = getMaximumAmount(quantity, m);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
