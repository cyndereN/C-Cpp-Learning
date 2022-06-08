// ���ñ����㷨:
// for_each // ��������
// transform // ����


// for_each
void print01() {
	cout << val << " ";
}
for_each(v.begin(), v.end(), print01);


class print02 {
public:
	void operator()(int val) {
		cout << val << " ";
	}
};
for_each(v.begin(), v.end(), print02());

// transform
// Ŀ��������Ҫ��ǰ���ٿռ�
transform(iterator beg1, iterator end1, iterator beg2, _func); // _func���ƻص�����

/*********************************************/
// ���ò����㷨��
// find			 // ����Ԫ��
// find_if		 // ����������
// adjacent_find // ���������ظ�Ԫ��
// binary_search // ���ֲ��ҷ�
// count         // ͳ��Ԫ�ظ���
// count_if      // ������ͳ��Ԫ�ظ���


// find(iterator beg, iterator end, elem);
// �ҵ�����ָ��λ�õ��������Ҳ������ؽ���������
class Person {
public:
	Person(string name, int age) {
		this->m_name = name;
		this->m_age = age;
	}

	// ����== �ײ�find֪����ζԱ�person��������
	bool operator==(const Person& p) {
		if (this->m_name == p.mname && this->m_age == p.m_age) {
			return true;
		}
		return false;
	}

	string m_name;
	int m_age;
};
Person pp("cc", 20);
vector<Person>::iterator it = find(v.gebin(), v.end(), pp);
if (it == v.end()) {
	cout << "û���ҵ�" << endl;
}
else {
	cout << "�ҵ�Ԫ��" << it->m_age << endl;
}

// find_if(iterator beg, iterator end, _Pred);
class Greater20 {
public:
	bool operator()(Person& p) {
		return p.m_age > 20;
	}
};

vector<Person>::iterator it = find_if(v.begin(), v.end(), Greater20());



// adjacent_find(iterator beg, iterator end) �������ظ�Ԫ�أ� ���ص�һ�������ظ���Ԫ�صĵ�����

// binary_search(iterator beg, iterator end, elem) // ����bool���ͣ������������в�����

// count(iterator beg, iterator end, elem)  // ͳ��Ԫ�س��ִ���

// count_if(iterator beg, iterator end, _Pred);

/*********************************************/
// ���������㷨��
// sort

// random_shuffle(iterator beg, iterator end); // ����˳��

// merge(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);
// ����Ԫ�غϲ������洢����һ������
// �������������������
// dest, Ŀ��������ʼ������
// ��ǰ��Ŀ����������ռ�

// reverse(iterator beg, iterator end);

/*********************************************/
// ���ÿ������滻�㷨��
// copy(iterator beg, iterator end, iterator dest);
// ������ָ����Χ��Ԫ�ؿ�������һ������
// ��ǰ��Ŀ����������ռ�

// replace(iterator beg, iterator end, oldvalue, newvalue);
// �������ھ�Ԫ���滻����Ԫ��

// replace_if(iterator beg, iterator end, _Pred, newvalue);

// swap(container c1, container c2);




/*********************************************/
// �������������㷨��
// accumulate(v.begin(), v.end(), value);
// ��������Ԫ���ۼ��ܺ�, value����ʼֵ

// fill(v.begin(), v.end(), value);
// ��������

/*********************************************/
// ���ü����㷨
// set_intersection 
// ����ֵ�ǽ��������һ��Ԫ�ص�λ��
vTarget.resize(min(v1.size(), v2.size())); // ���������������������С����
vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.begin(), vTarget.begin());
for_each(vTarget.begin(), itEnd, myPrint);


// set_union
// vTarget.resize(v1.size() + v2.size());


// set_difference
// vTarget.resize(max(v1.size(), v2.size()));



