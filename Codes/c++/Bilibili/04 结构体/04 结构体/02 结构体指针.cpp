struct student {
	string name;
	int age;
	int score;
};

struct student s = { "张三"， 18， 100 };

student* p = &s;

cout << p->name << p->age ...