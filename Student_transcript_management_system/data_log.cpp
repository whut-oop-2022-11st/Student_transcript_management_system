#include "data_log.hpp"

void log_manager::add(string& num, string& name, double usual, double exam) {
	_log temp;
	get<0>(temp) = 1;
	time(&get<1>(temp));
	get<2>(temp) = num;
	get<3>(temp) = name;
	get<4>(temp) = usual;
	get<5>(temp) = exam;
	logs.push_back(temp);
	write();
}

void log_manager::search(string& keyword)
{
	_log temp;
	get<0>(temp) = 2;
	time(&get<1>(temp));
	get<3>(temp) = keyword;
	logs.push_back(temp);
	write();
}

void log_manager::del(string& num)
{
	_log temp;
	get<0>(temp) = 4;
	time(&get<1>(temp));
	get<2>(temp) = num;
	logs.push_back(temp);
	write();
}

void log_manager::change(string& num, string& name, double usual, double exam, string& prenum, string& prename, double preusual, double preexam)
{
	_log temp;
	get<0>(temp) = 5;
	time(&get<1>(temp));
	get<2>(temp) = num;
	get<3>(temp) = name;
	get<4>(temp) = usual;
	get<5>(temp) = exam;
	get<6>(temp) = prenum;
	get<7>(temp) = prename;
	get<8>(temp) = preusual;
	get<9>(temp) = preexam;
	logs.push_back(temp);
	write();
}

void log_manager::show() {
	_log temp;
	get<0>(temp) = 3;
	time(&get<1>(temp));
	write();
}

void log_manager::log_out(time_t set, time_t end) {
	read();
	if (logs.empty()) {
		cout << "系统中无日志信息！" << endl;
	}
	else {
		int cnt = 0;
		for (auto x : logs) {
			if (get<1>(x) >= set && get<1>(x) <= end) {
				cnt++;
				logout(x);
			}
		}
		if (!cnt) {
			cout << "未查询到日志信息！" << endl;
		}
	}
	logs.clear();
}

void log_manager::stats(string& type, double avg, double mid) {
	_log temp;
	get<0>(temp) = 6;
	time(&get<1>(temp));
	get<3>(temp) = type;
	get<4>(temp) = avg;
	get<5>(temp) = mid;
	logs.push_back(temp);
	write();
}
/*
void log_manager::head(){
	tl[3];
	cout << setiosflags(ios::left) << D << "时间" << setw(14) << "姓名" << setw(12) << "平时成绩" << setw(12) << "考试成绩" << setw(12) << "总成绩" << endl;
	tl[7];
}*/

void log_manager::logout(_log& l) {
	int type;    //事件类型
	time_t time; //事件时间
	string num;
	string name;
	double usual;
	double exam;
	//以下为修改中的"之前"项
	string prenum;
	string prename;
	double preusual;
	double preexam;

	tie(type, time, num, name, usual, exam,
		prenum, prename, preusual, preexam) = l;
	string t = tl.TimeToString(time);
	tl[14];
	cout << "[" << t << "] ";
	tl[7];
	switch (type) {
	case 1: //录入
		cout << "添加了一条学生信息：" << endl << "学号 : " << num << setw(15) << "姓名 : " << name << setw(15) << "平时成绩 : " << usual << setw(15) << "期末成绩 : " << exam << endl;
		break;
	case 2: //查询
		cout << "按关键词 " << name << setw(14) << " 查询了成绩！" << endl;
		break;
	case 3:
		cout << "按学号顺序显示了一次成绩单！" << endl;
		break;
	case 4:
		cout << "按学号关键词 " << name << setw(14) << " 删除了一条记录！" << endl;
		break;
	case 5:
		cout << "修改了该条学生信息："
			<< "原学号: " << prenum << setw(16)
			<< "原姓名: " << prename << setw(14)
			<< "原平时成绩: " << preusual << setw(20) << "原期末成绩: " << preexam << setw(20) << endl
			<< " ==> " << "学号: " << num << setw(16)
			<< "姓名: " << name << setw(14)
			<< "平时成绩: " << usual << setw(20) << "期末成绩: " << exam << endl;
		break;
	case 6: //变量代指统计类型、平均分、中位数
		cout << "统计分析了一次" << name << "成绩——平均分: " << usual << " 中位数: " << exam << endl;
		break;
	default:
		cout << "错误日志！" << endl;
		break;
	}
}

void log_manager::read()
{
	ifstream ifs;
	try {
		ifs.open("./log.dat", ios::in);
	}
	catch (...) {
		cout << "哦哟，日志文件 " << logfile << " 打不开啦！\n";
		return;
	}
	if (!ifs.is_open())
	{
		cout << "哦哟，日志文件 " << logfile << " 打不开啦！\n";
		return;
	}
	for (;;)
	{
		string temp;
		if (ifs.eof())
			break;
		getline(ifs, temp);
		if (temp.length() == 0)
			break;
		int type = -1;
		_log x;
		stringstream sstream(temp);
		sstream >> type;
		switch (type)
		{
		case 1:
			get<0>(x) = type;
			sstream >> get<1>(x);
			sstream >> get<2>(x);
			sstream >> get<3>(x);
			sstream >> get<4>(x);
			sstream >> get<5>(x);
			break;
		case 2:
			get<0>(x) = type;
			sstream >> get<1>(x);
			sstream >> get<3>(x);
			break;
		case 3:
			get<0>(x) = type;
			sstream >> get<1>(x);
			break;
		case 4:
			get<0>(x) = type;
			sstream >> get<1>(x);
			sstream >> get<2>(x);
			break;
		case 5:
			get<0>(x) = type;
			sstream >> get<1>(x);
			sstream >> get<2>(x);
			sstream >> get<3>(x);
			sstream >> get<4>(x);
			sstream >> get<5>(x);
			sstream >> get<6>(x);
			sstream >> get<7>(x);
			sstream >> get<8>(x);
			sstream >> get<9>(x);
			break;
		case 6:
			get<0>(x) = type;
			sstream >> get<1>(x);
			sstream >> get<3>(x);
			sstream >> get<4>(x);
			sstream >> get<5>(x);
			break;
		default:
			break;
		}
		logs.push_back(x);
	}
}

void log_manager::write()
{
	ofstream ofs;
	try {
		ofs.open(logfile, ios::out | ios::app);
	}
	catch (...) {
		cout << "哦哟，日志文件 " << logfile << " 打不开啦！\n";
		return;
	}
	_log* buf = new _log;
	if (!buf) {
		cout << "内存不足！\n";
		return;
	}
	for (auto x : logs) {
		int type = -1;
		size_t time = 0;
		string num, name, prenum, prename;
		double usual, exam, preusual, preexam;
		tie(type, time, num, name, usual, exam, prenum, prename, preusual, preexam) = x;
		switch (type)
		{
		case 1:
			ofs << type << ' ' << time << ' ' << num << ' ' << name << ' ' << usual << ' ' << exam << endl;
			break;
		case 2:
			ofs << type << ' ' << time << ' ' << name << endl;
			break;
		case 3:
			ofs << type << ' ' << time << endl;
			break;
		case 4:
			ofs << type << ' ' << time << ' ' << num << endl;
			break;
		case 5:
			ofs << type << ' ' << time << ' ' << num << ' ' << name << ' ' << usual << ' ' << exam << ' ' << prenum << ' ' << prename << ' ' << preusual << ' ' << preexam << endl;
			break;
		case 6:
			ofs << type << ' ' << time << ' ' << name << ' ' << usual << ' ' << exam << endl;
			break;
		default:
			break;
		}
	}
	logs.clear();
}
