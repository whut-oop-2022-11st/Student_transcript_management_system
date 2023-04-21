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
		cout << "录入完毕!";
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

void user_service::stats()
{
	vector<double>all_grades;
	vector<size_t>subsection(10,0);
	double max = 0, min = 100,all=0;
	int i = 0,n=manager.length();
	for(i=0;i<n;i++)
	{
		data_node message = *manager[i];
		all_grades.push_back(message.grade());
		if (message.grade() / 10 < 10)
			subsection[message.grade() / 10]++;
		else
			subsection[9]++;
		if (max < message.grade())
			max = message.grade();
		if (min > message.grade())
			min = message.grade();
		all += message.grade();
	}
	i = 0;
	tl[2];
	cout << "最高成绩为：";
	tl[4];
	cout << setprecision(2) << max << endl;
	tl[2];
	cout << "最低成绩为：";
	tl[4];
	cout << setprecision(2) << min << endl;
	tl[2];
	cout << "平均成绩为：";
	tl[4];
	cout << setprecision(2) << all/n << endl;
	for (int j = 0, k = 9; i < 10; i++)
	{
		if (subsection[i] == 0);
		else
		{
			tl[1];
			cout << j << "分到" << k << "分区间人数：";
			tl[4];
			cout<< subsection[i] << endl;
			tl[16];
		}
		j += 10;
		if (k == 89)
			k = 100;
		else
			k += 10;
	}
	tl[6];
	cout << "其余区间人数均为0" << endl;
	tl[16];
}
