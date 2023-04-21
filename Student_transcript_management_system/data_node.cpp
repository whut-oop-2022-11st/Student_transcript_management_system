#include "data_node.hpp"

data_node::data_node(vector<string> info)
{
	if (info.size() == (size_t)5)
	{
		dnum = info[0];
		dname = info[1];
		dusual_grades = (stod(info[2]));
		dexam_scores = (stod(info[3]));
		setgrade();
		sequence = stoi(info[4]);
	}
	else
		throw string("info size error");//抛出异常，外部用的时候需要用try...catch...
}

bool data_node::num_infohit(string info)//学号是否对应
{
	if (info == dnum)
		return true;
	return false;
}

bool data_node::name_infohit(string info)//姓名是否对应
{
	if (info == dname)
		return true;
	return false;
}

void data_node::setgrade(double usual, double exam)//传入平时成绩与考试成绩，计算总成绩
{
	if (usual == -1 and exam == -1)
	{
		dgrade = 0.8 * dexam_scores + 0.2 * dusual_grades;
		return;
	}
	dusual_grades = usual;
	dexam_scores = exam;
	dgrade = 0.8 * exam + 0.2 * usual;
}

void data_node::resetinfo(vector<string> info)//重新设置信息
{
	if (info.size() == (size_t)4)
	{
		dnum = info[0];
		dname = info[1];
		dusual_grades = (stod(info[2]));
		dexam_scores = (stod(info[3]));
		setgrade();
	}
	else
		throw string("info size error");//抛出异常
}

string data_node::show_all_ele()//返回所有信息
{
	return string(dnum + ' ' + dname + ' ' + to_string(dusual_grades) + ' ' + to_string(dexam_scores) + ' ' + to_string(dgrade));
}

string data_node::num()//返回学号
{
	return dnum;
}

string data_node::name()//返回姓名
{
	return dname;
}

double data_node::usual_grades()//返回平时成绩
{
	return dusual_grades;
}

double data_node::exam_scores()//返回考试成绩
{
	return dexam_scores;
}

double data_node::grade()//返回总成绩
{
	return dgrade;
}
