#pragma once
#include "global.hpp"
using namespace std;
class data_node
{
public:
	friend class data_manager;
	data_node() = default;
	data_node(vector<string>info);//初始化数据
	bool num_infohit(string info);//num是否对应
	bool name_infohit(string info);//name是否对应
	void setgrade(double usual = -1, double exam = -1);//设置成绩，计算总成绩
	void resetinfo(vector<string>info);//重设所有信息
	string show_all_ele();//显示所有信息
	string num();
	string name();
	double usual_grades();
	double exam_scores();
	double grade();
private:
	string dnum;//学号
	string dname;//姓名
	double dusual_grades;//平时成绩
	double dexam_scores;//考试成绩
	double dgrade;//总成绩
	size_t sequence;//次序
};
