// 通过自己写成员函数，实现两个对象相加属性后返回新的对象
Person PersonAddPerson(Person& p) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}
// 编译器给起了个通用名称
// 通过成员函数重载+号
Person operator+(Person& p) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}

//Person p3 = p1.PersonAddPerson(p2);
//简化为
//Person p3 = p1 + p2;

// 通过全局函数重载+
Person operator+(Person& p1, Person& p2) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}

//Person p3 = operator+(p1, p2);
//简化为
//Person p3 = p1 + p2;
