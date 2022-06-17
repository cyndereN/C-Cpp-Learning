//传统的初始化 
Person(int a, int b, int c) {
	m_a = a;
	m_b = b;
	m_c = c;
}

//初始化列表
Person(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}