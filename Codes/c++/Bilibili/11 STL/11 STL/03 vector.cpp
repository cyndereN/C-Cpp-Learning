// ���������ƣ�Ҳ��Ϊ��������

// ��֮ͬ�����������Ǿ�̬�ռ䣬vector���Զ�̬��չ
// ��̬��չ����������ԭ�ռ�������¿ռ䣬�����Ҹ�����ڴ�ռ䣬Ȼ��ԭ���ݿ����¿ռ䣬�ͷ�ԭ�ռ�

// vector �ĵ�����֧���������

vector<int> v4(10, 100);

vector<int> v4;
v4.assign(10, 100);  // ʮ��100

vector<int> v3;
v3.assign(v.begin(), v1.end());

v.empty()  // �Ƿ�Ϊ��
v.capacity()
v.size()
v.resize(int num);
v.resize(int num, elem);   // ���������elem��� ����ɾ��

v.push_back();
v.pop_back();
v.insert(v.begin(), 100); // ��һ�������ǵ�����
v.insert(v.begin(),2, 100);
v.erase(v.begin());
v.erase(v.begin(), v.end()); // ���
v.clear();

v[i]; v.at(i);
v.front() // ��һ��Ԫ��
v.end() // ���һ��Ԫ��

// vector��������
v1.swap(v2)
// ����swap���������ڴ�ռ�
vector<int>(v).swap(v); // ��������û�н��а󶨲�������������

// Ԥ���ռ�
reserve(int len); // ����Ԥ��len��Ԫ�س��ȣ�Ԥ��λ�ò���ʼ����Ԫ�ز��ɷ���
vector<int> v;

v.reserve(100000);

int num = 0;  // ͳ�ƿ��ٴ���
int* p = NULL;
for (int i = 0; i < 10000; i++) {
	v.push_back(i);

	if (p != &v[0]) {
		p = &v[0];
		num++; // 30�Σ�reserve֮��1��
	}
}



// ͷ������ɾ����O(N)

// β������ɾ��:O(1)

// �м����ɾ����O(N)

// ���ң�O(N)