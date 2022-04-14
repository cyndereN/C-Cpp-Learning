// Cin is a nightmare

#include <iostream>
#include <sstream>

using namespace std;

int getInteger(const string& prompt = "Enter an integer: ",
                const string& reprompt = "Illegal numeric format. Try again.");

int main(){
    cout << "What is your name? ";
    string name;
    //cin >> name;
    getline(cin, name, '\n');

    cout << "What is your age? ";
    int age;
    //cin >> age;
    age = getInteger();

    cout << "What is your home? ";
    string home;
    cin >> home;

    cout << "Hello " << name << " (age " << age << " from " << home << ")" << endl;
    
    return 0;
}

int getInteger(const string& prompt, const string& reprompt){
    while(true){
        cout << prompt;
        string line;

        if(!getline(cin, line)) throw domain_error("...");

        istringstream iss(line);
        int val; char remain;

        if (iss >> val && !(iss >> remain))  return val;

        cout << reprompt << endl;
    }
    return 0;
}