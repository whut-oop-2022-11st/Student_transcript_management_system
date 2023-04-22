#include "global.hpp"
int login()
{
	encipher* checker = &enci;
	ifstream in;
	in.open("code.txt", ios::in);
	try
	{
		if (!in.is_open())
		{
			throw - 1;
		}
		else
		{
			char ch;
			in >> ch;
			if (in.eof())
				throw - 2;
		}
	}
	catch (int error_code)
	{
		in.close();
		switch (error_code)
		{
		case -1:
			tl[12];
			cout << "系统找不到密码相关文件，可能是第一次使用或者重置密码" << endl;
			tl[14];
			cout << "请创建一个管理员账户" << endl;
			tl[7];
			break;
		case -2:
			tl[12];
			cout << "管理员身份文件无效，需要重新创建管理员账户" << endl;
			tl[7];
			break;
		default:
			tl[4];
			cout << "出现未知错误";
			return -1;
		}
		string codea, codeb, username;
	begin:
		tl[14];
		cout << "用户名:";
		cin >> username;
		cout << "密码:";
		cin >> codea;
		cout << "请再次输入密码:";
		cin >> codeb;
		if (codea != codeb)
		{
			tl[4];
			cout << "两次输入密码不一致" << endl;
			tl[14];
			goto begin;
		}
		ofstream out("code.txt");
		out << username << " " << checker->ascii_to_sha1(username + codea);
		out.close();
		tl[2];
		cout << "账户" << username << "已创建" << endl;
		tl[7];
		return 1;
	}
	string username, code, temp;
	tl[2];
	cout << "欢迎进入学生信息管理系统" << endl;
	for (int i = 0; i < 3; i++)
	{
		in.seekg(ios::beg);
		tl[14];
		cout << "用户名:";
		tl[7];
		cin >> username;
		tl[14];
		cout << "密码:";
		tl[7];
		cin >> code;
		code = checker->ascii_to_sha1(username + code);
		code = username + " " + code;
		for (;;)
		{
			getline(in, temp);
			if (temp == code)
			{
				in.close();
				tl[2];
				system("cls");
				cout << "登陆成功，欢迎回来" << username << endl;
				tl[7];
				return 0;
			}
			if (in.eof())
			{
				if (i == 2)
				{
					tl[4];
					cout << "失败次数过多,想要重置密码，请删除文件code.txt";
					in.close();
					return -1;
				}
				tl[12];
				cout << "抱歉，请重试" << endl;
				tl[7];
				break;
			}
		}
	}
	return -1;
}
int menu()
{
	int i;
	tl[14];
	cout << "-------欢迎来到学生成绩单管理系统-------\n";
	cout << "1.添加\n" << "2.查询\n" << "3.修改\n" << "4.删除\n" << "5.输出所有学生信息\n"
		<< "6.数据分析\n" << "0.退出\n" << "请输入：";
	for (;;)
	{
		tl[7];
		cin >> i;
		if (i >= 0 && i < 7)
		{
			return i;
		}
		else
		{
			tl[14];
			cout << "请重新输入：";
		}
	}
}
