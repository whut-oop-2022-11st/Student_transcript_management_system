#include "tool.hpp"
void tool::operator[](short x)
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
string tool::current_time()
{
	char s[101];
	chrono::system_clock::time_point now = chrono::system_clock::now();
	time_t tt = chrono::system_clock::to_time_t(now);
	ctime_s(s, 100, &tt);
	return string(s);
}
