#include "data_log.hpp"



void log_manager::add(string& num, string& name, double usual, double exam) {
	read();
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
	read();
	_log temp;
	get<0>(temp) = 2;
	time(&get<1>(temp));
	get<3>(temp) = keyword;
	logs.push_back(temp);
	write();
}

void log_manager::del(string& num)
{
	read();
	_log temp;
	get<0>(temp) = 4;
	time(&get<1>(temp));
	get<2>(temp) = num;
	logs.push_back(temp);
	write();
}

void log_manager::change(string& num, string& name, double usual, double exam, string& prenum, string& prename, double preusual, double preexam)
{
	read();
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
	read();
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
	write();
}

void log_manager::stats(string& type, double avg, double mid) {
	read();
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
	read();
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
	cout << "[" << t << "] ";
	switch (type) {
	case 1: //录入
		cout << "添加了一条学生信息：学号: " << setw(14) << num << "姓名: " << name << "平时成绩: " << setw(20) << usual << "期末成绩: " << setw(20) << exam;
		break;
	case 2: //查询
		cout << "按关键词 " << setw(14) << name << " 查询了成绩！";
		break;
	case 3:
		cout << "按学号顺序显示了一次成绩单！";
		break;
	case 4:
		cout << "按学号关键词 " << setw(14) << name << " 删除了一条记录！";
		break;
	case 5:
		cout << "修改了该条学生信息："
			<< "原学号: " << setw(16) << prenum
			<< "原姓名: " << setw(14) << prename
			<< "原平时成绩: " << setw(20) << preusual << "原期末成绩: " << setw(20) << preexam
			<< " ==> " << "学号: " << setw(16) << num
			<< "姓名: " << setw(14) << name
			<< "平时成绩: " << setw(20) << usual << "期末成绩: " << setw(20) << exam;
		break;
	case 6: //变量代指统计类型、平均分、中位数
		cout << "统计分析了一次" << name << "成绩——平均分: " << usual << " 中位数: " << exam;
		break;
	default:
		cout << "错误日志！";
		break;
	}
	cout << endl;
	write();
}

void log_manager::read()
{
	ifstream ifs;
	try {
		ifs.open(logfile, ios::binary | ios::in);
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
	ifs.read((char*)buf, sizeof(_log));
	logs.push_back(*buf);
}

void log_manager::write()
{
	ofstream ofs;
	try {
		ofs.open(logfile, ios::binary | ios::out | ios::trunc);
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
		ofs.write((char*)&x, sizeof(_log));
	}
	logs.clear();
}
