// ͨ���Լ�д��Ա������ʵ����������������Ժ󷵻��µĶ���
Person PersonAddPerson(Person& p) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}
// �����������˸�ͨ������
// ͨ����Ա��������+��
Person operator+(Person& p) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}

//Person p3 = p1.PersonAddPerson(p2);
//��Ϊ
//Person p3 = p1 + p2;

// ͨ��ȫ�ֺ�������+
Person operator+(Person& p1, Person& p2) {
	Person temp;
	temp.m_A = this->m_A + p.m_A;
	temp.m_B = this->m_B + p.m_B;
	return temp;
}

//Person p3 = operator+(p1, p2);
//��Ϊ
//Person p3 = p1 + p2;
