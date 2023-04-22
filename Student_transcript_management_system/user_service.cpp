#include "user_service.hpp"
void user_service::add()
{
	string temp;
	tl[7];
	cout << "------信息录入------" << endl;
	cout << "请选择录入方式。" << endl;
	cout << "(1):录入单个学生信息(默认方式)\n(2)录入多个学生信息\n请输入1或2。" << endl;
	cin >> temp;
	string a;
	string num;
	string name;
	double usual_grades;
	double exam_scores;
	if (temp == "2")
	{
		unsigned int stunum = 0;      //要录入的学生数量

		cout << "请输入要录入的学生数量。" << endl;
		for (;;)
		{
			cin >> a;
			auto test = [](string age)->bool {
				if (age.length() == 0 || age.length() >= 4)
					return false;
				for (char x : age)
				{
					if ('0' <= x && x <= '9')
						continue;
					return false;
				}
				return true;
			};

			if (test(a))
				break;
			else
			{
				tl[4];
				cout << "输入非法,请重新输入" << endl;
				tl[7];
			}
		}
		stunum = atoi(a.c_str());

		for (unsigned int i = 0; i < stunum; i++)
		{
			tl[7];
			cout << "第" << i + 1 << "位学生学号:";
			cin >> num;
			cout << "第" << i + 1 << "位学生姓名:";
			cin >> name;
			cout << "第" << i + 1 << "位学生平时成绩(阿拉伯数字):";
			for (;;)
			{
				cin >> a;
				auto test = [](string age)->bool {
					if (age.length() == 0 || age.length() >= 4)
						return false;
					for (char x : age)
					{
						if ('0' <= x && x <= '9')
							continue;
						return false;
					}
					return true;
				};

				if (test(a))
					break;
				else
				{
					tl[4];
					cout << "输入非法,请重新输入" << endl;
					tl[7];
				}
			}
			usual_grades = atof(a.c_str());

			tl[7];
			cout << "第" << i + 1 << "位学生考试成绩(阿拉伯数字):";
			for (;;)
			{
				cin >> a;
				auto test = [](string age)->bool {
					if (age.length() == 0 || age.length() >= 4)
						return false;
					for (char x : age)
					{
						if ('0' <= x && x <= '9')
							continue;
						return false;
					}
					return true;
				};

				if (test(a))
					break;
				else
				{
					tl[4];
					cout << "输入非法,请重新输入" << endl;
					tl[7];
				}
			}
			exam_scores = atof(a.c_str());

			if (stunum > 1)
			{
				tl[14];
				cout << "--------------------------" << endl;
			}

			vector<string> x = { num,name,to_string(usual_grades),to_string(exam_scores) };
			try
			{
				manager.push_back(x);

			}
			catch (string s)
			{
				tl[4];
				cout << s << endl;
				tl[7];
				cout << "(1):重新输入该学生信息(默认)\n(2):停止添加\n请输入1或2" << endl;
				int x = 0;
				cin >> x;
				if (x == 2)
				{
					cout << "录入停止。" << endl;
					return;
				}
				i--;
				continue;
			}
		}
		tl[7];
		cout << "录入完毕!" << endl;
		return;
	}
	if (temp == "1")
	{
		for (int i = 0; i < 1; i++)
		{
			tl[7];
			cout << "学生学号:";
			cin >> num;
			cout << "学生姓名:";
			cin >> name;
			cout << "学生平时成绩(阿拉伯数字):";

			for (;;)
			{
				cin >> a;
				auto test = [](string age)->bool {
					if (age.length() == 0 || age.length() >= 4)
						return false;
					for (char x : age)
					{
						if ('0' <= x && x <= '9')
							continue;
						return false;
					}
					return true;
				};

				if (test(a))
					break;
				else
				{
					tl[4];
					cout << "输入非法,请重新输入" << endl;
					tl[7];
				}
			}
			usual_grades = atof(a.c_str());
			tl[7];
			cout << "学生考试成绩(阿拉伯数字):";
			for (;;)
			{
				cin >> a;
				auto test = [](string age)->bool {
					if (age.length() == 0 || age.length() >= 4)
						return false;
					for (char x : age)
					{
						if ('0' <= x && x <= '9')
							continue;
						return false;
					}
					return true;
				};


				if (test(a))
					break;
				else
				{
					tl[4];
					cout << "输入非法,请重新输入" << endl;
					tl[7];
				}
			}
			exam_scores = atof(a.c_str());

			vector<string> x = { num,name,to_string(usual_grades),to_string(exam_scores) };
			try
			{
				manager.push_back(x);
			}
			catch (string s)
			{
				tl[4];
				cout << s << endl;
				tl[7];
				cout << "(1):重新输入该学生信息(默认)\n(2):停止添加\n请输入1或2" << endl;
				int x = 0;
				cin >> x;
				if (x == 2)
				{
					cout << "录入停止。" << endl;
					return;
				}
				i--;
				continue;
			}
		}
		tl[7];
		cout << "录入完毕!" << endl;
		return;
	}
}

void user_service::search()
{
	cout << "请输入查询的学号或名字（名字可使用?或*代替一个或多个字符）:";
	string student;
	cin >> student;
	auto it = manager.search_by_num(student);
	try {
		manager.node_info(it);
		head();
		scout(it->show_all_ele());
		//cout << it->show_all_ele() << endl;
		return;
	}
	catch (...) {}

	if ((student.find('?') != string::npos) || (student.find('*') != string::npos)) {
		auto it2 = manager.search_by_name(student, false, true);
		try {
			manager.node_info(it2[0]);
			head();
			for (auto tmp : it2) {
				scout(tmp->show_all_ele());
				//cout << tmp->show_all_ele() << endl;
			}
			return;
		}
		catch (...) {
			cout << "未找到对应的学生" << endl;
			return;
		}
	}
	else {
		auto it2 = manager.search_by_name(student, true, false);
		try {
			manager.node_info(it2[0]);
			head();
			for (auto tmp : it2) {
				scout(tmp->show_all_ele());
				//cout << tmp->show_all_ele() << endl;
			}
			return;
		}
		catch (...) {
			cout << "未找到对应的学生" << endl;
			return;
		}
	}
}

// 删除学生信息
// 输入要删除的学生的学号，得到用户确认后，删除该学生的信息。
void user_service::del()
{
	string num;
	cout << "请输入要删除的学生的学号: ";
	cin >> num;

	auto it = manager.search_by_num(num);
	try                                         //此处的try  catch 解决了要访问manager::data的问题 
	{
		manager.node_info(it);
	}
	catch (...)                                 //为了简便 用...来捕获所有的异常
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
		cout << "删除成功!" << endl;
	}
	else
	{
		cout << "已取消操作!" << endl;
	}
}


// 修改学生信息
// 输入要修改的学生的学号，显示该学生的原有信息，用户输入修改后的信息。
void user_service::change()
{
	tl.clc();                      //tl.clc()还是上次实验的问题 中  cin和getline最好不要混用  有回车问题
	string num;
	cout << "请输入要修改的学生的学号: ";
	//	getline(cin, num);
	cin >> num;
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
	cout << "请输入你想修改的部分（1：学号，2：姓名，3：平时成绩，4：考试成绩，5：修改多个）:";
	int choice = 5;
	cin >> choice;
	vector<string> new_info = manager.ve_node_info(it);
	string info;
	switch (choice) {
	case 1:
		cout << "请输入修改后的学号: ";
		cin >> info;
		new_info[0] = info;
		break;
	case 2:
		cout << "请输入修改后的姓名: ";
		cin >> info;
		new_info[1] = info;
		break;
	case 3:
		cout << "请输入修改后的平时成绩: ";
		cin >> info;
		new_info[2] = info;
		break;
	case 4:
		cout << "请输入修改后的考试成绩: ";
		cin >> info;
		new_info[3] = info;
		break;
	default:
		cout << "请输入修改后的学号: ";
		cin >> info;
		new_info[0] = info;
		cout << "请输入修改后的姓名: ";
		cin >> info;
		new_info[1] = info;
		cout << "请输入修改后的平时成绩: ";
		cin >> info;
		new_info[2] = info;
		cout << "请输入修改后的考试成绩: ";
		cin >> info;
		new_info[3] = info;
		break;
	}
	try {
		manager.change(it, new_info);
		manager.save();
		cout << "修改成功" << endl;
		return;
	}
	catch (...) {
		cout << "新的学号已经存在，修改已取消" << endl;
		return;
	}
}

void user_service::show()
{
	vector<string>ans = manager.all_node_info_by_num();
	if (ans.empty())
	{
		tl[5];
		cout << "当前系统无储存的信息" << endl;
		tl[16];
	}
	tl[3];
	head();
	for (vector<string>::iterator it = ans.begin(); it != ans.end(); it++)
		scout(*it);
	tl[16];
}

void user_service::stats()
{
	//	vector<double>all_grades;
	//	vector<size_t>subsection(10,0);
	//	double max = 0, min = 100,all=0;
	//	int i = 0,n=manager.length();
	//	for(i=0;i<n;i++)
	//	{
	//		data_node message = *manager[i];
	//		all_grades.push_back(message.grade());
	//		if (message.grade() / 10 < 10)
	//			subsection[message.grade() / 10]++;
	//		else
	//			subsection[9]++;
	//		if (max < message.grade())
	//			max = message.grade();
	//		if (min > message.grade())
	//			min = message.grade();
	//		all += message.grade();
	//	}
	//	i = 0;
	////	tl[2];
	//	cout << "最高成绩为：";
	////	tl[4];
	//	cout << setprecision(2) << max << endl;
	////	tl[2];
	//	cout << "最低成绩为：";
	////	tl[4];
	//	cout << setprecision(2) << min << endl;
	////	tl[2];
	//	cout << "平均成绩为：";
	////	tl[4];
	//	cout << setprecision(2) << all/n << endl;
	//	for (int j = 0, k = 9; i < 10; i++)
	//	{
	//		if (subsection[i] == 0);
	//		else
	//		{
	////			tl[1];
	//			cout << j << "分到" << k << "分区间人数：";
	////			tl[4];
	//			cout<< subsection[i] << endl;
	////			tl[16];
	//		}
	//		j += 10;
	//		if (k == 89)
	//			k = 100;
	//		else
	//			k += 10;
	//	}
	////	tl[6];
	//	cout << "其余区间人数均为0" << endl;
	////	tl[16];
	tl[6];
	cout << "------数据分析------" << endl;
	tl[16];
	for (int k = 0; k < 3; ++k) {
		switch (k) {
		case 0:
			tl[3];
			cout << "----平时成绩----" << endl;
			tl[16];
			break;
		case 1:
			tl[3];
			cout << "----期末成绩----" << endl;
			tl[16];
			break;
		case 2:
			tl[3];
			cout << "----总评成绩----" << endl;
			tl[16];
			break;
		}
		tl[3];
		cout << "--成绩分布--" << endl;
		tl[16];
		auto scoreData = manager.node_scores(k);
		auto max = std::max_element(scoreData.begin(), scoreData.end());
		auto min = std::min_element(scoreData.begin(), scoreData.end());
		int step = int(*max - *min) / 8 + 1;
		int maxNum = 0;
		double center = 0.0;
		double ave = 0.0;
		for (int i = int(*min - 1); i < int(*max + 1); i += step) {
			//        i--i+step-1
			int tmpMaxNum = 0;
			for (double x : scoreData) {
				ave += x;
				if (x >= i && x <= i + step - 1) {
					tmpMaxNum++;
				}
			}
			if (tmpMaxNum > maxNum) {
				maxNum = tmpMaxNum;
			}
		}
		int a = (int)scoreData.size() * 8;
		ave /= a;
		center = scoreData[int(scoreData.size() / 2)];
		for (int i = int(*min - 1); i < int(*max + 1); i += step) {
			tl[11];
			cout << left << setw(4) << setfill(' ') << i << " -- " << setw(4) << setfill(' ') << i + step - 1 << ":";
			tl[16];
			int tmpMaxNum = 0;
			for (double x : scoreData) {
				if (x >= i && x <= i + step - 1) {
					tmpMaxNum++;
				}
			}
			for (int j = 0; j < int(((tmpMaxNum * 1.0) / (maxNum * 1.0) * 20)); ++j) {
				/*cout << u8"\u2588";*/
				cout << char(168) << char(128);
				//cout << "-";
			}
			tl[12];
			cout << tmpMaxNum << "人" << endl;
			tl[16];
		}
		tl[3];
		cout << "--成绩数据--" << endl;
		tl[16];
		tl[14];
		cout << "平均分：" << ave << endl;
		cout << "中位数：" << center << endl;
		tl[16];
	}
}

void user_service::head()
{
	tl[3];
	cout << setiosflags(ios::left) << setw(20) << "学号" << setw(14) << "姓名" << setw(12) << "平时成绩" << setw(12) << "考试成绩" << setw(12) << "总成绩" << endl;
	tl[7];
}

void user_service::scout(string s)
{
	tl[14];
	stringstream sstream{ s };
	string s0, s1, s2, s3, s4;
	sstream >> s0;
	sstream >> s1;
	sstream >> s2;
	sstream >> s3;
	sstream >> s4;
	cout << setiosflags(ios::left) << setw(20) << s0 << setw(14) << s1 << setw(12) << s2 << setw(12) << s3 << setw(12) << s4 << endl;
	tl[7];
}
