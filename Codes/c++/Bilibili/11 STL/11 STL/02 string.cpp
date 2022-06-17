
// char*是一个指针
// string是c++风格的字符串 本质上是一个类 内部封装了char*管理这个字符串，是一个char*型的容器

string str;
str.assign("hello c++", 5); // str = "hello"

str += "!";  // str.append("1234!1234",4,1); 从第四个开始截取，截一个 str = "hello c++!"

str.find("lo") // 返回3（lo第一次出现的位置） 如果不出现返回-1. rfind从右往左找

str.replace(1, 3, "1111");  // "h1111o c++"

str.compare("xxx"); // 相等返回0, str > "xxx" 返回值>0

str.at(i); str[i];

str.insert(1, "111"); // "h111ello c++"
str.erase(1, 3) // 删除从第1个index开始的3个字符

str.substr(1, 3);  // "ell" 截取从第1个index开始的3个字符