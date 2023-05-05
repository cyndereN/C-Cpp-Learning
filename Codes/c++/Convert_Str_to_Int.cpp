/*
Write a C function which converts a character 
string into a signed integer without using 
any library functions.  
Assume that the string contains 
a valid integer, and no white space. 
*/

// example of how the function you write would be used
int val = ConvertStringToInt("-640"); 
// val would end up with the integer value -640 


int ConvertStringToInt(char* str) {
    int sign = 1;
    int result = 0;

    // handle sign of integer
    if (str[0] == '-') {
        sign = -1;
        str++;
    }

    // convert digits to integer
    while (*str != '\0') {
        int digit = *str - '0';
        result = result * 10 + digit;
        str++;
    }

    return sign * result;
}
