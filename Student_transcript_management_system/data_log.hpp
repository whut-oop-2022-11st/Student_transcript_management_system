#pragma once
#include "global.hpp"
//元组实现日志

typedef tuple<int, time_t,
	string, string, double, double,
	string, string, double, double> _log;

class log_manager {
public:
	void add(string& num,string& name,double usual,double exam); //录入
	void search(string& keyword); //查询
	void show(); //显示
	void del(string& num); //删除
	void change(string& num, string& name, double usual, double exam, string& anum, string& aname, double ausual, double aexam); //修改
	void stats(string& type, double avg, double mid); //查询统计
	void log_out(time_t set, time_t end); //输出日志
private:
	vector<tuple<int, time_t,
		string, string, double, double,
		string, string, double, double>> logs;
	//void head();
	void logout(_log& l);
	void read();
	void write();
};

extern log_manager Log;
extern string logfile;