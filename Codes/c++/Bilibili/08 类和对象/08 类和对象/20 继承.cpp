// �̳з�ʽ�����֣�������������˽��

// �ȹ��츸�࣬�ٹ�������
// ����˳��͹���˳���෴

class A {
public:
	int a;
protected: // ֻ����Ԫ����������������ܷ���
	int b;
private:   // Ҳ��̳У�ֻ����������
	int c;
};

// ���м̳�
class B : public A {
public:
	int a;
protected:
	int b;
���ɷ���:
	int c;
};

// �����̳�
class B : protected A {
protected:
	int a;
	int b;
���ɷ��ʣ�
	int c;
};

// ˽�м̳�
class B : private A {
private:
	int a;
	int b;
���ɷ���:
	int c;
};

class BasePage {
public:
	void header() {
		cout << "Header" << endl;
	}

	void footer() {
		cout << "footer" << endl;
	}
};

class Java : public BasePage {
public:
	void content() {
		cout << "Java content" << endl;
	}
};

class CPP : public BasePage {
public:
	void content() {
		cout << "C++ content" << endl;
	}
};