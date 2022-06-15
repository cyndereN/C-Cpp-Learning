#Constructors

Initializes state of new object as they are created

e.g., BankAccount ba("Cynthia", 1.25);

#Destructor

Called when the object is deleted by the program

# Const
Global variables can be read or modified by any part of the program making it difficult to remember or reason about every possible use.


## Const Iterators
const vector<int>::iterator itr = vector.begin();  // acts like int* const itr
*itr = 5; // OK! changing what itr points to
++itr; // BAD! can't modify itr

vector<int>::const_iterator itr = vector.begin(); 
*itr = 5; // BAD! can't change value of itr
++itr; // OK! changing v
int value = *itr; // OK! reading from itr

## Const obj/fucntion

- const on objects: 
Guarantees that the object won't change by allowing you to call only const functions and treating all public members as if they were const. This helps the programmer write safe code and also gives the compiler more information to use to optimize.

- const on functions:
Guarantees that the function won't call anything but const functions, and won't modify any non-static, non-mutable members
