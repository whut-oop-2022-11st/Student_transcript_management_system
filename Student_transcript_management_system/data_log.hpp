#pragma once
#include "global.hpp"
//Ԫ��ʵ����־

typedef tuple<int, time_t,
	string, string, double, double,
	string, string, double, double> _log;

class log_manager {
public:
	void add(string& num,string& name,double usual,double exam); //¼��
	void search(string& keyword); //��ѯ
	void show(); //��ʾ
	void del(string& num); //ɾ��
	void change(string& num, string& name, double usual, double exam, string& anum, string& aname, double ausual, double aexam); //�޸�
	void stats(string& type, double avg, double mid); //��ѯͳ��
	void log_out(time_t set, time_t end); //�����־
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