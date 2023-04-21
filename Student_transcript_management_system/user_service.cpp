#include "user_service.hpp"
void user_service::add()
{
	string temp;
	cout << "------信息录入------" << endl;
	cout << "请选择录入方式。" << endl;
	cout << "(1):录入单个学生信息(默认方式)\n(2)录入多个学生信息\n请输入1或2。" << endl;
	cin >> temp;
	string num;
	string name;
	double usual_grades;
	double exam_scores;
	if (temp == "2")
	{
		int stunum = 0;      //要录入的学生数量
		cout << "请输入要录入的学生数量。" << endl;
		cin >> stunum;
		for (int i = 0; i < stunum; i++)
		{
			cout << "第" << i + 1 << "位学生学号:";
			cin >> num;
			cout << "第" << i + 1 << "位学生姓名:";
			cin >> name;
			cout << "第" << i + 1 << "位学生平时成绩:";
			cin >> usual_grades;
			cout << "第" << i + 1 << "位学生考试成绩:";
			cin >> exam_scores;
			if (stunum > 1)
			{
				cout << "--------------------------" << endl;
			}

			vector<string> x = { num,name,to_string(usual_grades),to_string(exam_scores) };
			try
			{
				manager.push_back(x);

			}
			catch (string s)
			{
				cout << s << endl;
				cout << "请重新输入该学生信息" << endl;
				i--;
				continue;
			}
		}
		cout << "录入完毕!"<<endl;
		return;
	}
	cout << "学生学号:";
	cin >> num;
	cout << "学生姓名:";
	cin >> name;
	cout << "学生平时成绩:";
	cin >> usual_grades;
	cout << "学生考试成绩:";
	cin >> exam_scores;
	cout << "录入完毕!" << endl;
	vector<string> x = { num,name,to_string(usual_grades),to_string(exam_scores) };
	try
	{
		manager.push_back(x);
	}
	catch (string s)
	{

		cout << "error";
	}
	return;
}

void user_service::search()
{
	cout << "请输入查询的学号" << endl;
	string student;
	cin >> student;
	auto it = manager.search_by_num(student);
	cout << it->show_all_ele() << endl;
}

// 删除学生信息
// 输入要删除的学生的学号，得到用户确认后，删除该学生的信息。
void user_service::del()
{
	string num;
	cout << "请输入要删除的学生的学号: ";
	cin >> num;
	
	auto it = manager.search_by_num(num);
	try                                                  //此处的try  catch 解决了要访问manager::data的问题 
	{
		manager.node_info(it);
	}
	catch(...)                                          //为了简便 用...来捕获所有的异常
	{
		cout << "未找到对应学号的学生" << endl;
		return;
	}
	cout << "找到学生：" << it->show_all_ele() << endl;
	
	char confirm;
	cout << "是否确认删除(Y/N): ";
	cin >> confirm;
	
	if (confirm == 'Y' || confirm == 'y') 
	{
		manager.del(it);
		cout << "删除成功" << endl;
	}
	else 
	{
		cout << "已取消操作" << endl;
	}
}


// 修改学生信息
// 输入要修改的学生的学号，显示该学生的原有信息，用户输入修改后的信息。
void user_service::change()
{
	tl.clc();                                 //tl.clc()还是上次实验的问题 中  cin和getline最好不要混用  有回车问题 此处统一为用getline
	string num;
	cout << "请输入要修改的学生的学号: ";
	getline(cin, num);
	auto it = manager.search_by_num(num);
	try
	{
		manager.node_info(it);
	}
	catch (...)
	{
		cout << "未找到对应学号的学生" << endl;
		return;
	}
	cout << "找到学生：" << it->show_all_ele() << endl;
	vector<string> new_info;
	string info;
	cout << "请输入修改后的学号: ";
	getline(cin, info);
	
	if (!info.empty()) 
	{
		new_info.push_back(info);
	}
	cout << "请输入修改后的姓名: ";
	getline(cin, info);
	
	if (!info.empty()) 
	{
		new_info.push_back(info);
	}
	cout << "请输入修改后的平时成绩: ";
	getline(cin, info);
	
	if (!info.empty()) 
	{
		new_info.push_back(info);
	}
	cout << "请输入修改后的考试成绩: ";
	getline(cin, info);
	
	if (!info.empty()) 
	{
		new_info.push_back(info);
	}
	manager.change(it, new_info);
	cout << "修改成功" << endl;
}
