#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ostringstream oss("Ito En Green Tea ");
  cout << oss.str() << endl;
  
  oss << 16.9 << " ouce ";
  cout << oss.str() << endl;
  // 16.9 ouce en Tea 

  ostringstream osse("Ito En Green Tea ", stringstream::ate);
  cout << osse.str() << endl;

  osse << 16.9 << " ouce ";
  cout << osse.str() << endl;
  //Ito En Green Tea 16.9 ouce 

  osse <<"(Pack of " << 12 << ")";
  cout << osse.str() << endl;

  istringstream iss(oss.str());
  
  int amount;
  string unit;

  cout << iss.str() << endl;;
  stringstream ss("16 ouce");
  
  ss >> amount >> unit;

  cout << amount << "\n"+unit << endl;
  
  return 0;
}