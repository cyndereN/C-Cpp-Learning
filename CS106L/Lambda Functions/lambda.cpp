int main() {
    auto print_int = [](int x) {
        cout << x << endl;
    };
    // print_int is a function now!
    print_int(5); // “5”
    print_int(7); // “7”
    // what type is print_int? who cares!
}


int main() {
    int limit;
    std::cin >> limit;
    auto is_less_than = [limit](int val) { return (val < limit) };
    // this solves our earlier problem!
    vector<int> v = {1, 2, 3, 4, 5}; 
    count_occurrences(v.begin(), v.end(), is_less_than);
    // counts the number of times a number under limit appears
}


auto lambda = [capture-values(capture-clause)](arguments) -> return-value {
    // body
}


set<string> teas {"black", "green", "oolong"};
string banned = "boba";
auto likedByAvery = [&teas, banned] (auto type) {
    return teas.count(type) && type != banned;
};