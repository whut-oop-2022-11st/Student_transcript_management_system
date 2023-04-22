#include "data_log.hpp"



void log_manager::add(string& num, string& name, double usual, double exam){
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

void log_manager::log_out(time_t set, time_t end){
	read();
	if (logs.empty()) {
		cout << "ϵͳ������־��Ϣ��";
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
			cout << "δ��ѯ����־��Ϣ��";
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
	cout << setiosflags(ios::left) << D << "ʱ��" << setw(14) << "����" << setw(12) << "ƽʱ�ɼ�" << setw(12) << "���Գɼ�" << setw(12) << "�ܳɼ�" << endl;
	tl[7];
}*/

void log_manager::logout(_log& l){
	read();
	int type;    //�¼�����
	time_t time; //�¼�ʱ��
	string num;
	string name;
	double usual;
	double exam;
	//����Ϊ�޸��е�"֮ǰ"��
	string prenum;
	string prename;
	double preusual;
	double preexam;

	tie(type,time, num, name, usual, exam,
		prenum, prename, preusual, preexam) = l;
	string t = tl.TimeToString(time);
	cout << "[" << t << "] ";
	switch (type){
	case 1: //¼��
		cout << "�����һ��ѧ����Ϣ��ѧ��: " << setw(14) << num << "����: " << name <<"ƽʱ�ɼ�: " << setw(20) << usual << "��ĩ�ɼ�: " << setw(20) << exam;
		break;
	case 2: //��ѯ
		cout << "���ؼ��� " << setw(14) << name << " ��ѯ�˳ɼ���";
		break;
	case 3:
		cout << "��ѧ��˳����ʾ��һ�γɼ�����";
		break;
	case 4:
		cout << "��ѧ�Źؼ��� " << setw(14) << name << " ɾ����һ����¼��";
		break;
	case 5:
		cout << "�޸��˸���ѧ����Ϣ��"
			<<"ԭѧ��: " << setw(16) << prenum 
			<< "ԭ����: " << setw(14) << prename
			<< "ԭƽʱ�ɼ�: " << setw(20) << preusual << "ԭ��ĩ�ɼ�: " << setw(20) << preexam
			<<" ==> "<< "ѧ��: " << setw(16) << num 
			<< "����: " << setw(14) << name
			<< "ƽʱ�ɼ�: " << setw(20) << usual << "��ĩ�ɼ�: " << setw(20) << exam;
		break;
	case 6: //������ָͳ�����͡�ƽ���֡���λ��
		cout << "ͳ�Ʒ�����һ��" <<name <<"�ɼ�����ƽ����: " << usual << " ��λ��: " << exam;
		break;
	default:
		cout << "������־��";
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
		cout << "ŶӴ����־�ļ� " << logfile << " �򲻿�����\n";
		return;
	}
	_log* buf = new _log;
	if (!buf){
		cout << "�ڴ治�㣡\n";
		return;
	}
	ifs.read((char*)buf,sizeof(_log));
	logs.push_back(*buf);
}

void log_manager::write()
{
	ofstream ofs;
	try {
		ofs.open(logfile, ios::binary | ios::out | ios::trunc);
	}
	catch (...) {
		cout << "ŶӴ����־�ļ� " << logfile << " �򲻿�����\n";
		return;
	}
	_log* buf = new _log;
	if (!buf) {
		cout << "�ڴ治�㣡\n";
		return;
	}
	for (auto x : logs) {
		ofs.write((char*)&x, sizeof(_log));
	}
	logs.clear();
}
