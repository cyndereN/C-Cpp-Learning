// ���μ̳л����������ԣ���Ϊ���ӵ�����������̳���үү�࣬��ֻ��һ�ݾ͹�

class Animal {
public:
	int m_Age;
};
class Sheep : virtual public Animal {
	
};
class Tuo : virtual public Animal {

};

class SheepTuo :public Sheep, public Tuo {

};

void test01() {
	SheepTuo st;
	// �����μ̳У���������ӵ����ͬ���ݣ���Ҫ��������������
	st.Sheep::m_Age = 18;
	st.Tuo::m_Age = 28;
	// �����������֪����һ�ݾͿ��ԣ����μ̳е��������ݣ���Դ�˷�

	// ������̳н�����μ̳е����⣬�̳�ʱ�ڸ����ǰ���virtual
}