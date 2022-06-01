// ���Խ������ָ���ͷ��������
// ��Ҫ�о��庯��ʵ��
// ����Ǵ����������������ڳ����࣬�޷�ʵ����

class Animal {
public:
	Animal() {
		cout << "Animal���캯������" << endl;
	}

	//virtual ~Animal() {
	//	// ������ ���Խ������ָ���ͷ��������ʱ���ɾ�������
	//	cout << "Animal��������������" << endl;
	//}

	// ������������Ҫ����ʵ��
	// ���˴�������֮�������Ҳ���ڳ����࣬�޷�ʵ��������
	virtual ~Animal() = 0;

	// ���麯��
	virtual void speak() = 0;
};
Animal::~Animal() {
	cout << "Animal����������������" << endl;
}

class Cat : public Animal {
public:
	Cat(string name) {
		cout << "Cat ���캯������" << endl;
		m_name = new string(name); // ���ٵ���������Ҫ�õ������е�����
	}
	void speak() {
		cout << *m_name << "è��˵��" << endl;
	}

	~Cat() {
		if (m_name != NULL) {
			cout << "Cat ������������" << endl;
			delete m_name;
			m_name = NULL;
		}
	}
	string* m_name;
};

void test01() {
	Animal* animal = new Cat('Tom');
	animal->speak();
	// ����ָ��������ʱ�򲻻������������������
	// ������������ж������ԣ������ڴ�й©
	delete animal;
}