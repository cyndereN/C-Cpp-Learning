/*
Question 1:
  Write the code for the following function, without using any built-in functions except
  malloc or operator new. Document your assumptions and explain your choices.
  char* itoa(int Value, int Base);
  where the returned value is allocated on behalf of the caller, value is the integer to
  convert, and base is octal, decimal, or hex.
*/

/*
  Assumption:
    1. Value ranges from -2147483648 to 2147483647, since it is an int
    2. Therefore the maximum length of returned char[] is 32. Allocate result
  array of size 40 is legit
    3. Base range from 2 to 16
    4. Default value of Base is 10
*/

/*
  Test case 1:
    10 in Base 10 is 10
    10 in Base 8 is 12
    10 in Base 16 is a
    10 in Base 2 is 1010
*/
/*
  Test case 2:
    123 in Base 10 is 123
    123 in Base 8 is 173
    123 in Base 16 is 7b
    123 in Base 2 is 1111011
*/

/*
  Test case 3:
    -2 in Base 10 is -2
    -2 in Base 8 is 37777777776
    -2 in Base 16 is fffffffe
    -2 in Base 2 is 11111111111111111111111111111110
*/

#include <iostream>
#include <cstring>
using namespace std;


char* itoa(int Value, int Base = 10);
char* reverse(char* s);


char _itoaHelper[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

const unsigned int UNSIGNED_MAX = 0xFFFFFFFFu;
const int MAX_LEN = 40;

char* itoa(int Value, int Base) {
    if (Base < 2 || Base > 16) {
        return NULL;
    }

    // ans is to store each bit of the int
    // Must be static, or global
    // Alternative way: char* ans = (char*)malloc(sizeof(char) * MAX_LEN);
    static char ans[MAX_LEN];
    int i = 0;
    unsigned int temp;

    if (Value < 0) {
        if (Base == 10) {
            Value = -Value;
            do {
                ans[i++] = _itoaHelper[Value % Base];
            } while ((Value /= Base) > 0);
            ans[i++] = '-';
        }
        else {
            temp = UNSIGNED_MAX + Value + 1; // 2's complement
            do {
                ans[i++] = _itoaHelper[temp % Base];
            } while ((temp /= Base) > 0);
        }

    }
    else {
        do {
            ans[i++] = _itoaHelper[Value % Base];
        } while ((Value /= Base) > 0);
    }

    ans[i] = '\0';

    return reverse(ans);
}

// Reverse a string
char* reverse(char* s) {
    char temp;
    char* p = s;
    char* q = s;
    while (*q)
        ++q;
    q--;

    while (q > p) {
        temp = *p;
        *p++ = *q;
        *q-- = temp;
    }
    return s;
}

/*
Question 2:
    Write a function with the following signature that, given a row-major matrix of integers,
    builds a string with the entries of that matrix appended in clockwise order. Unlike the
    previous question, you may use built-in functions. You may also use your solution from the
    previous question, but are not required to. OutBuffer is guaranteed to be valid and large
    enough to hold all of the data. Document your assumptions and explain your choices.
    void BuildStringFromMatrix(int* Matrix, int NumRows, int
    NumColumns, char* OutBuffer);
    For instance, the 3x4 matrix below:
    [2, 3, 4, 8,
    5, 7, 9, 12,
    1, 0, 6, 10]
    would make the string “2, 3, 4, 8, 12, 10, 6, 0, 1, 5, 7, 9”.
*/
/*
  Assumption:
    1. NumRows and NumColumns should not be 0
    2. NumRows and NumColumns must be correct, since we cannot check NumRows * NumColumns != sizeof(Matrix) in the function (it does not pass the length as a parameter)
    3. OutBuffer is of sufficient size
    4. The maximum of NumRows and NumColumns is 100 
*/


void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer);

const int MAX_ROW = 100;
const int MAX_COL = 100;

void BuildStringFromMatrix(int* Matrix, int NumRows, int NumColumns, char* OutBuffer) {
    if (NumRows == 0 || NumColumns == 0) {
        cout << "Row & Column parameters cannot be 0!" << endl;
        return;
    }

    int i = 0, j = 0, k = 0, x = 0, y = 0;
    int size = NumRows * NumColumns;
    int direction = 0;

    int tempIndex = 0;
    string tempString;
    char* tempOutBuffer;
    bool traveled[MAX_ROW + 5][MAX_COL + 5] = { false };

    // Changes of 4 direction
    int dir[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

    for (k = 0; k < size; k++) {
        tempString += itoa(Matrix[i * NumColumns + j]);
        if (k != NumRows * NumColumns - 1)
            tempString += ", ";
        traveled[i][j] = true; // Mark as traveled 
        x = i + dir[direction][0];
        y = j + dir[direction][1];
        if (x < 0 || x >= NumRows || y < 0 || y >= NumColumns || traveled[x][y])
            direction = (direction + 1) % 4;
        i += dir[direction][0];
        j += dir[direction][1];
    }

    tempOutBuffer = (char*)tempString.data();
    strcpy(OutBuffer, tempOutBuffer);
}