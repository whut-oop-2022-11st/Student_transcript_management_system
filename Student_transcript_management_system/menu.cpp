#include "global.hpp"
int menu()
{
	int i;
	cout << "-------欢迎来到学生成绩单管理系统-------\n";
	cout << "1.添加\n" << "2.查询\n" << "3.修改\n" << "4.删除\n" << "5.输出所有学生信息\n"
		<< "6.数据分析\n" << "0.退出\n" << "请输入：";
	for (;;)
	{
		cin >> i;
		if (i >= 0 && i < 7)
		{
			return i;
		}
		else
		{
			cout << "请重新输入：";
		}
	}
}
