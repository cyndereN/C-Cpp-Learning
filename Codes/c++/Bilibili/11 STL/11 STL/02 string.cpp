
// char*��һ��ָ��
// string��c++�����ַ��� ��������һ���� �ڲ���װ��char*��������ַ�������һ��char*�͵�����

string str;
str.assign("hello c++", 5); // str = "hello"

str += "!";  // str.append("1234!1234",4,1); �ӵ��ĸ���ʼ��ȡ����һ�� str = "hello c++!"

str.find("lo") // ����3��lo��һ�γ��ֵ�λ�ã� ��������ַ���-1. rfind����������

str.replace(1, 3, "1111");  // "h1111o c++"

str.compare("xxx"); // ��ȷ���0, str > "xxx" ����ֵ>0

str.at(i); str[i];

str.insert(1, "111"); // "h111ello c++"
str.erase(1, 3) // ɾ���ӵ�1��index��ʼ��3���ַ�

str.substr(1, 3);  // "ell" ��ȡ�ӵ�1��index��ʼ��3���ַ�