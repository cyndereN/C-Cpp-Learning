// ��׼ģ���
// contatiner, algorithm, iterator
// �������㷨֮��ͨ�������������޷�����
// �������д��붼��������ģ��ͺ���ģ��

// �������
// �������㷨�����������º��������������ռ�������

// ��������������㷺��һЩ���ݽṹʵ�ֳ���
// ����ʽ������ǿ��ֵ����������ʽ�����е�ÿ��Ԫ�ؾ��й̶�λ��
// ����ʽ�������������ṹ����Ԫ��֮��û���ϸ�������ϵ�˳���ϵ

// �㷨������Ľⷨ�����޵Ĳ��裬����߼�����ѧ�ϵ�����
// �ʱ��㷨����������л���������ڵ�Ԫ�ص����ݡ����翽����ɾ�����滻�ȵ�
// ���ʱ��㷨��ָ��������в�����������ڵ�Ԫ�����ݡ�������ҡ�������������Ѱ�Ҽ�ֵ�ȵȡ�

// ������
// ���õ�Ϊ˫���������������ʵ�����

// 1. ��������Vector
// ���Բ������ݲ���������

void test01() {
	vector<int> v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);


	// ��һ��
	vector<int>::iterator itBegin = v.begin();
	vector<int>::iterator itEnd = v.end();

	while (itBegin != itEnd) {
		cout << *itBegin << endl;
		itBegin++;
	}

	// �ڶ���
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << endl;
	}

	// ������
	void myPrint(int val) {
		cout << val << endl;
	}
	for_each(v.begin(), v.end(), myPrint);
}
