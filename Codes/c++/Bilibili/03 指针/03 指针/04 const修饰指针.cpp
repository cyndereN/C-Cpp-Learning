int a = 10;
int b = 10;
int* p = &a;


// ����ָ��
// ָ���ָ������޸ģ�����ָ��ָ���ֵ���ܸ�
const int* p = &a; // int const* p = &a;
*p = 20; //�Ǵ��
p = &b; // ��ȷ
// ��ʱconst�޶������Σ�����int* ����*p���ܸ�

// ָ�볣��
// ָ���ָ�򲻿����޸ģ�����ָ��ָ���ֵ�ܸ� // CONST pointer to a non-constant int
int* const p = &a;
int const* p = &a;
// ��ʱconst�޶�����ָ��ָ��ĳ���(p)�����Բ��ܸ�

// const������ָ�������γ���
// ָ���ָ���ָ��ָ���ֵ�������Ը���	
const int* const p = &a;
int const* const p = &a;

