//  将函数的形参改为指针，可以减少内存空间，而且不会复制新的副本出来


void printStudent(const Student* stu) {
	//stu->age = 100;  //操作失败因为加了const修饰
}


