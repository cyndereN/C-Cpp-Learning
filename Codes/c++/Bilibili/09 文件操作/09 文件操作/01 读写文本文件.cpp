// ����ͷ�ļ� <fstram>

// �ı��ļ� - ���ı�ASCII����ʽ�洢�ڼ������	
// �������ļ� - �ļ����ı��Ķ�������ʽ�洢�ڼ������

// ofstream д
// ifstream ��
// fstream ��д����

// 1. д�ļ��������£�
// ����ͷ�ļ�
# include <fstream>
// ����������
ofstream ofs;
// ���ļ�
ofs.open("�ļ�·��", �򿪷�ʽ);
/*
ios::in Ϊ���ļ�
ios::out ��в�ļ�
ios::app ׷�ӷ�ʽ
ios::binary ������

������д��ios::binary | ios::out
*/
// д����
ofs << "д�������";
// �ر��ļ�
ofs.close();

// 2. ���ļ��������£�
// ����ͷ�ļ�
# include <fstream>
// ����������
ifstream ifs;
// ���ļ����ж��Ƿ�򿪳ɹ�
ifs.open("�ļ�·��", �򿪷�ʽ);
// ������
���ַ�ʽ��ȡ
// �ر��ļ�
ifs.close()

// ����
void test01() {
	ifstream ifs;
	ifs.open("test.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		return
	}

	// ������
	// ��һ��

	char buf[1024] = { 0 };
	while (ifs >> buf) {
		cout << buf << endl;
	}

	// �ڶ���
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf))){
		cout << buf << endl;
	}

	// ������
	string buf;
	while (getline(ifs, buf)) {
		cout << buf << endl;
	}

	// ������
	char c;
	while ((c = ifs.get())!= EOF) {
		cout << c;
	}



	ifs.close();
}