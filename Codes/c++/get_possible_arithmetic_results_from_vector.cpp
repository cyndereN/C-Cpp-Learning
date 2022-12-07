#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getNumPossibleRoutes' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER t
 *  3. INTEGER_ARRAY v
 */
int cnt  = 0;

// O(2^n) time complexity, O(n)Space Compleity
void back_track( vector<int> v, int target, int index, int sum, int k) {

    sum = (sum+k)%k;

    if (index <= v.size()){
        if (sum == target)
            cnt++;
        else{
            int val = v[index]%k;
            back_track(v, target, index+1, sum + val, k);
            back_track(v, target, index+1, sum - val, k);
        }
        
    }
    
    
}

int getNumPossibleRoutes(int k, int t, vector<int> v) {

    back_track(v, t, 0, 0, k);
    
    return cnt;
}



int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    string v_count_temp;
    getline(cin, v_count_temp);

    int v_count = stoi(ltrim(rtrim(v_count_temp)));

    vector<int> v(v_count);

    for (int i = 0; i < v_count; i++) {
        string v_item_temp;
        getline(cin, v_item_temp);

        int v_item = stoi(ltrim(rtrim(v_item_temp)));

        v[i] = v_item;
    }

    int result = getNumPossibleRoutes(k, t, v);

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
