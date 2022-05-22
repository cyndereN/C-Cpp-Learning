#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <iomanip>

struct Course{
  std::string name;
  double rating;  
};

// print a Course struct to any ostream
std::ostream& operator<<(std::ostream& os, const Course& c) {
    os << std::setw(15) << std::setfill(' ') << c.name << "  " << c.rating;
    return os;
}

template <typename InputIt, typename UniPred>
int countOccurrences(InputIt begin, InputIt end, UniPred pred){
    int count = 0;
    for (auto i = begin; i != end; ++i){
        if (pred(*i))  ++count;     // too few arguments
    }
    return count;
}

bool isLessThan5(int val){
    return val < 5;
}

bool isLessThanLimit(int val, int limit){
    return val < limit;
}

std::vector<Course> readCourses(){
    std::vector<Course> v = {
        {"CS 106A", 4.4337}, {"CS 106B", 4.4025},
        {"CS 107", 4.6912}, {"CS 110", 4.343},
        {"Math 51", 3.6119}, {"Math 52", 4.325},
        {"Math 53", 4.3111}, {"Econ 1", 4.2552},
        {"Anthro 3", 3.71}, {"Educ 342", 4.55},
        {"Chem 33",  3.50}, {"German 132", 4.83}
    };

    std::random_shuffle(v.begin(), v.end());
    return v;
}

// A function which returns a vector of a bunch of numbers
std::vector<double> readNumbers() {
    std::vector<double> numbers;
    std::generate_n(std::back_inserter(numbers), 500, std::rand);
    return numbers;
}

int main(){
    // count how many timnes 5 appears in the second half of a vector<int>

    std::vector<int> phoneNumber {5, 5, 5, 8, 2, 6, 5, 5, 3, 5};
    // int times1 = countOccurrences(phoneNumber.begin()+phoneNumber.size()/2, phoneNumber.end(), 5);

    // std::cout << "the second half of phoneNumber contains " << times1 << " elements of 5" << std::endl;

    // count how many elements in the second half of a vector<int> that are less than 5
    int times2 = 0;
    times2 = countOccurrences(phoneNumber.begin()+phoneNumber.size()/2, phoneNumber.end(), isLessThan5);
    
    std::cout << "the second half of phoneNumber contains " << times2 << " elements that are less than 5" << std::endl;

    // Using lambda function
    int limit = 5;
    int num_times_called = 0;
    // "=" captures everything nby value
    //  "&" by reference 
    auto isLessThanLimit = [limit = 2, &num_times_called] (auto val ){
        ++num_times_called;
        return val < limit;
    };

    auto courses = readCourses();
    auto numbers = readNumbers();


    auto compareRating = [] (const Course& c1, const Course& c2){
        return c1.rating < c2.rating;
    };
    std::sort(numbers.begin(), numbers.end());
    std::sort(courses.begin(), courses.end(), compareRating);

    auto median = courses[courses.size()/2];

    std::string department = "CS";
    auto isDep = [department] (auto element){
        return element.name.size()>2 && element.name.substr(0, 2) == department;
    };

    std::stable_partition(courses.begin(), courses.end(), isDep);


    std::vector<Course> csCourses;
    std::copy_if(courses.begin(), courses.end(), back_inserter(csCourses), isDep);

    // remove_if 不能改变container size
    courses.erase(std::remove_if(courses.begin(), courses.end(), isDep), courses.end());

    std::copy(courses.begin(), courses.end(), std::ostream_iterator<Course>(std::cout, "\n"));

}