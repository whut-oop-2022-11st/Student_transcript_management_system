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
		throw string("info size error");
}

bool data_node::num_infohit(string info)
{
	if (info == dnum)
		return true;
	return false;
}

bool data_node::name_infohit(string info)
{
	if (info == dname)
		return true;
	return false;
}

void data_node::setgrade(double usual, double exam)
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

void data_node::resetinfo(vector<string> info)
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
		throw string("info size error");
}

string data_node::show_all_ele()
{
	return string(dnum + ' ' + dname + ' ' + to_string(dusual_grades) + ' ' + to_string(dexam_scores) + ' ' + to_string(dgrade));
}

string data_node::num()
{
	return dnum;
}

string data_node::name()
{
	return dname;
}

double data_node::usual_grades()
{
	return dusual_grades;
}

double data_node::exam_scores()
{
	return dexam_scores;
}

double data_node::grade()
{
	return dgrade;
}
