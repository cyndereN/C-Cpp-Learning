struct Course {
    string code;

    Time startTime; Time endTime;

    vector<string> instructors;
}

void transformToDST(vector<Course>& courses){
    for (auto& course : courses){
        course.startTime.hour++;
        course.endTime.hour++;
    }

    //----------------------------------------------------------------
    for (auto& [code, start, end, instructors] : courses){
        start++; end++;
    }
}

int main(){
    vector<int> vec{3, 1, 4, 5, 9};
    Course now {"CS106L", {15,30},{16,30}
                {"Wang", "Zeng"} };
}

// StringStream - when to use?

// Process strings, e.g. simplify "/./a/b/.." to "/a"
// Formatting input/output, e.g. Uppercase, hex, and other stream manipulators
// Parsing different types, e.g. stringToInteger()