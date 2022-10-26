// 结构体属于用户自定义的数据类型，允许用户存储不同的数据类型

struct student {
	string name;
	int age;
	int score;
};

// 第一种
struct Student s1;
s1.name = ....
.....

// 第二种
struct Student S2 = { ... }

	// 第三种
	struct student {
	string name;
	int age;
	int score;
} s3;

// 定义时关键字struct不可省略，创建时可省