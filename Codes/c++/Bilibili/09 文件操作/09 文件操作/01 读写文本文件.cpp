// 包含头文件 <fstram>

// 文本文件 - 以文本ASCII码形式存储在计算机中	
// 二进制文件 - 文件以文本的二进制形式存储在计算机中

// ofstream 写
// ifstream 读
// fstream 读写操作

// 1. 写文件步骤如下：
// 包含头文件
# include <fstream>
// 创建流对象
ofstream ofs;
// 打开文件
ofs.open("文件路径", 打开方式);
/*
ios::in 为读文件
ios::out 威胁文件
ios::app 追加方式
ios::binary 二进制

二进制写：ios::binary | ios::out
*/
// 写数据
ofs << "写入的数据";
// 关闭文件
ofs.close();

// 2. 读文件步骤如下：
// 包含头文件
# include <fstream>
// 创建流对象
ifstream ifs;
// 打开文件并判断是否打开成功
ifs.open("文件路径", 打开方式);
// 读数据
四种方式读取
// 关闭文件
ifs.close()

// 例子
void test01() {
	ifstream ifs;
	ifs.open("test.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		return
	}

	// 读数据
	// 第一种

	char buf[1024] = { 0 };
	while (ifs >> buf) {
		cout << buf << endl;
	}

	// 第二种
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf))) {
		cout << buf << endl;
	}

	// 第三种
	string buf;
	while (getline(ifs, buf)) {
		cout << buf << endl;
	}

	// 第四种
	char c;
	while ((c = ifs.get()) != EOF) {
		cout << c;
	}



	ifs.close();
}