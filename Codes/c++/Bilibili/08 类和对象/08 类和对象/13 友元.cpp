// privateֻ���Լ��ܷ��ʣ�����Ҳ��Ҫ���������һЩ����������з��ʣ�����Ҫ�õ���Ԫ�ļ���
// �ؼ��� friend
// ����ʵ��:
// �� ȫ�ֺ�������Ԫ
// �� ������Ԫ
// �� ��Ա��������Ԫ

class Building {
	//goodGayȫ�ֺ�����Building�����ѣ����Է���building��˽�г�Ա
	friend void goodGay(Building& building);

	// GoodGay���Ǳ������Ԫ�����Է��ʱ�����˽�г�Ա
	friend class GoodGay;

	// GoodGay����visit01��Ա�����Ǳ������Ԫ�����Է��ʱ�����˽�г�Ա
	friend void GoodGay::visit01();


public:
	string m_sittingroom;
	Building() {
		m_sittingroom = "����";
		m_bedroom = "����";
	}
private:
	string m_bedroom;
};


//  ȫ�ֺ���
void goodGay(Building& building) {
	cout << "��Ԫȫ�ֺ������ʿ���" << building.m_sittingroom << endl;
	cout << "��Ԫȫ�ֺ�����������" << building.m_bedroom << endl;
}

void test01() {
	Building b;
	goodGay(b);
}

/*********************************************************/
// ������Ԫ
class GoodGay {

public:
	Building* building;

	void visit();  // ����building������

	void visit01();
};

// ����д��Ա����
Building::Building() {
	m_sittingroom = "����";
	m_bedroom = "����";
}

GoodGay::GoodGay() {
	// �������������
	building = new Building;
}

void GoodGay::visit() {
	cout << "�û��������ڷ���: " << building->m_sittingroom << endl;
	cout << "�û��������ڷ���: " << building->m_bedroom << endl;
}

void test02() {
	GoodGay gg;
	gg.visit();
}

/*********************************************************/
void GoodGay::visit01() {
	cout << "�û��������ڷ���: " << building->m_sittingroom << endl;
	cout << "�û�����vist01�������ڷ���: " << building->m_bedroom << endl;
}