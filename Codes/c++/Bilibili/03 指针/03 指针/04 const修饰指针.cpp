int a = 10;
int b = 10;
int* p = &a;


// 常量指针
// 指针的指向可以修改，但是指针指向的值不能改
const int* p = &a; // int const* p = &a;
*p = 20; //是错的
p = &b; // 正确
// 此时const限定（修饰）的是int* 所以*p不能改

// 指针常量
// 指针的指向不可以修改，但是指针指向的值能改 // CONST pointer to a non-constant int
int* const p = &a;
int const* p = &a;
// 此时const限定的是指针指向的常量(p)，所以不能改

// const既修饰指针又修饰常量
// 指针的指向和指针指向的值都不可以更改	
const int* const p = &a;
int const* const p = &a;

