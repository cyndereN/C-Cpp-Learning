// Overloading
// Define two functions with the same name but different types
struct Student {
    string name; // these are called fields
    string state; // separate these by semicolons
    int age;
};
Student s;
s.name = "Frankie"; 
s.state = "MN";
s.age = 21; // use . to access fields

 //is the same as ...
Student s = {"Frankie", "MN", 21};

void printStudentInfo(Student student) {
    cout << s.name << " from " << s.state;
    cout << " (" << s.age ")" << endl;
}

Student randomStudentFrom(std::string state) {
    Student s;
    s.name = "Frankie";//random = always Frankie
    s.state = state;
    s.age = std::randint(0, 100);
    return s;
}


//std::pair
//- std::pair is a template: You specify the types of the fields 
//      inside <> for each pair object you make
//- The fields in std::pairs are named first and second

Student foundStudent = randomStudentFrom("MN");
cout << foundStudent.name << endl; // Frankie

std::pair<int, string> numSuffix = {1,"st"};
cout << numSuffix.first << numSuffix.second; 
//prints 1st

std::pair<bool, Student> lookupStudent(string name) {
    Student blank;
    if (found(name)) return std::make_pair(false, blank);
    Student result = getStudentWithName(name);
    return std::make_pair(true, result);
    }
std::pair<bool, Student> output = lookupStudent(“Keith”);

auto p = std::make_pair(“s”, 5);
auto [a, b] = p;
// a is of type string
// b is of type int
// auto [a, b] = std::make_pair(...);

//stream: an abstraction for input/output. Streams convert between data and the string representation of data.

