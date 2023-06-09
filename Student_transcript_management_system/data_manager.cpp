﻿#include "data_manager.hpp"
//0 num 1 name 2 usual_grades 3 exam_scores 4 sequence

void data_manager::push_back(string info)
{
	if ((info.find('?', 0)) != -1)
		throw string("'?' is not allowed");
	if ((info.find('*', 0)) != -1)
		throw string("'*' is not allowed");
	stringstream sstream(info);
	string temp;
	vector<string>ve_info;//学生信息保存的临时数组
	for (int i = 0; i < 4; i++)
	{
		sstream >> temp;
		ve_info.push_back(temp);
		temp.clear();
	}
	ve_info.push_back(to_string(sequence_data.size()));//在该数组最后添加次序下标，便于后续下标访问
	if (!(search_by_num(ve_info[0]) == data.end()))
		throw string("Number conflict!");//抛出异常，外面需要try...catch...
	data_node node(ve_info);
	data.push_back(node);
	num_data.insert(pair<string, list<data_node>::iterator>(ve_info[0], --data.end()));
	if ((search_by_name(ve_info[1]))[0] == data.end())
		name_data.insert(pair<string, vector<list<data_node>::iterator>>(ve_info[1], vector<list<data_node>::iterator>({ --data.end() })));
	else
		name_data[ve_info[1]].push_back(--(data.end()));
	sequence_data.push_back(--data.end());
}

void data_manager::push_back(vector<string> info)
{
	info.push_back(to_string(sequence_data.size()));//添加次序
	data_node node(info);
	if (!(search_by_num(info[0]) == data.end()))
		throw string("Number conflict!");//抛出异常
	if ((info[0].find('?', 0)) != -1)
		throw string("'?' is not allowed");
	if ((info[0].find('*', 0)) != -1)
		throw string("'*' is not allowed");
	if ((info[1].find('?', 0)) != -1)
		throw string("'?' is not allowed");
	if ((info[1].find('*', 0)) != -1)
		throw string("'*' is not allowed");
	data.push_back(node);
	num_data.insert(pair<string, list<data_node>::iterator>(info[0], --data.end()));
	if ((search_by_name(info[1]))[0] == data.end())
		name_data.insert(pair<string, vector<list<data_node>::iterator>>(info[1], vector<list<data_node>::iterator>({ --data.end() })));
	else
		name_data[info[1]].push_back(--(data.end()));
	sequence_data.push_back(--data.end());
}

void data_manager::push_back(data_node node)
{
	node.sequence = sequence_data.size();
	data.push_back(node);
}

void data_manager::del(list<data_node>::iterator del_ele)
{
	if (del_ele == data.end())
		throw string("try to erase the element after the last element");
	del_eles.push_back(del_ele->sequence);
	del_index(del_ele);
	data.erase(del_ele);
}

void data_manager::change(list<data_node>::iterator change_ele, string info)
{
	stringstream sstream(info);
	string temp;
	vector<string>ve_info;
	for (int i = 0; i < 4; i++)
	{
		sstream >> temp;
		ve_info.push_back(temp);
		temp.clear();
	}
	if (change_ele->num() != info && search_by_num(ve_info[0]) != data.end())
		throw string("Number conflict");
	del_index(change_ele);
	change_ele->resetinfo(ve_info);
	num_data.insert(pair<string, list<data_node>::iterator>(change_ele->num(), change_ele));
	if ((search_by_name(change_ele->name())[0] == data.end()))
		name_data.insert(pair<string, vector<list<data_node>::iterator>>(change_ele->name(), vector<list<data_node>::iterator>({ change_ele })));
	else
		name_data[change_ele->name()].push_back(change_ele);
}

void data_manager::change(list<data_node>::iterator change_ele, vector<string>info)
{
	if (change_ele->num() != info[0] && search_by_num(info[0]) != data.end())
		throw string("Number conflict");
	del_index(change_ele);
	change_ele->resetinfo(info);
	num_data.insert(pair<string, list<data_node>::iterator>(change_ele->num(), change_ele));
	if ((search_by_name(change_ele->name())[0] == data.end()))
		name_data.insert(pair<string, vector<list<data_node>::iterator>>(change_ele->name(), vector<list<data_node>::iterator>({ change_ele })));
	else
		name_data[change_ele->name()].push_back(change_ele);
}

void data_manager::save(string path)
{
	ofstream out(path, ios::out);
	if (!out.is_open())
		throw string("open file failed");
	for (list<data_node>::iterator p = data.begin(); p != data.end(); p++)
	{
		out << p->show_all_ele() << endl;
	}
	out.close();
}

void data_manager::load(string path)
{
	ifstream in(path, ios::in);
	if (!in.is_open())
		throw string("open file failed");
	string temp;
	for (;;)
	{
		if (in.eof())
			break;
		getline(in, temp);
		if (temp.length() == 0)
			break;
		push_back(temp);
		temp.clear();
	}
	in.close();
}

string data_manager::node_info(list<data_node>::iterator node)
{
	if (node == data.end())
		throw string("try to show the node after the last node");
	return node->show_all_ele();
}

vector<string> data_manager::ve_node_info(list<data_node>::iterator node)
{
	if (node == data.end())
		throw string("try to show the node after the last node");
	return vector<string>{ node->num(), node->name(), to_string(node->usual_grades()), to_string(node->exam_scores()) };
}

list<data_node>::iterator data_manager::search_by_num(string info)
{
	map<string, list<data_node>::iterator>::iterator x;
	if ((x = num_data.find(info)) == num_data.end())
		return data.end();
	return x->second;
}

vector<list<data_node>::iterator> data_manager::search_by_name(string info, bool use_fuzzy_search_if_no_ans, bool Regex_Search)
{
	vector<list<data_node>::iterator>ans;
	map<string, vector<list<data_node>::iterator>>::iterator x;
	if ((x = name_data.find(info)) == name_data.end())
	{
		if (Regex_Search)//正则表达式查询
		{
			auto is_chinese = find_if(info.begin(), info.end(), [](char x) {return !((x ^ 128) == 0); });
			for (size_t i = info.find('?'); i != (numeric_limits<size_t>::max)(); i = info.find('?'))
				if (is_chinese == info.end())
					info.replace((size_t)i, 1, ".");
				else
					info.replace((size_t)i, 1, "..");
			for (size_t i = info.find('*'); i != (numeric_limits<size_t>::max)(); i = info.find('*'))
				info.replace((size_t)i, 1, ".{0,100}");
			for (map<string, vector<list<data_node>::iterator>>::iterator it = name_data.begin(); it != name_data.end(); it++)
			{
				if (regex_match(it->first, regex(info, regex::icase)))
				{
					for (vector<list<data_node>::iterator>::iterator ip = it->second.begin(); ip != it->second.end(); ip++)
					{
						ans.push_back(*ip);
					}
				}
			}
			if (!ans.empty())
				return ans;
		}
		if (use_fuzzy_search_if_no_ans)//使用模糊查询
		{
			for (map<string, vector<list<data_node>::iterator>>::iterator it = name_data.begin(); it != name_data.end(); it++)
			{
				if (!(it->first.find(info) == string::npos))
				{
					for (vector<list<data_node>::iterator>::iterator ip = it->second.begin(); ip != it->second.end(); ip++)
					{
						ans.push_back(*ip);
					}
				}
			}
			if (!ans.empty())
				return ans;
		}
		return vector<list<data_node>::iterator>({ data.end() });
	}
	return x->second;
}

vector<string> data_manager::all_node_info_by_num()
{
	vector<string>ans;
	map<string, list<data_node>::iterator>::iterator p;
	for (p = num_data.begin(); p != num_data.end(); p++)
		ans.push_back(p->second->show_all_ele());
	return ans;
}

size_t data_manager::length()
{
	return data.size();
}

size_t data_manager::size()
{
	return data.size();
}

list<data_node>::iterator& data_manager::operator[](int i)//重载操作符[]
{
	size_t delta = 0;
	if (!del_eles.empty())
		for (vector<size_t>::iterator it = del_eles.begin(); *it <= i && it != del_eles.end(); delta++, it++);
	return sequence_data[i - delta];
}

void data_manager::update_index()//更新索引信息
{
	size_t i = 0;
	name_data.clear();
	num_data.clear();
	sequence_data.clear();
	del_eles.clear();
	for (list<data_node>::iterator it = data.begin(); it != data.end(); it++, i++)
	{
		it->sequence = i;
		num_data.insert(pair<string, list<data_node>::iterator>(it->num(), it));
		if ((search_by_name(it->name()))[0] == data.end())
			name_data.insert(pair<string, vector<list<data_node>::iterator>>(it->name(), vector<list<data_node>::iterator>({ it })));
		else
			name_data[it->name()].push_back(it);
		sequence_data.push_back(it);
	}
}

vector<double> data_manager::node_scores(short choice)
{
	vector<double>ans;
	switch (choice)
	{
	case 0:
	{
		for (list<data_node>::iterator it = data.begin(); it != data.end(); it++)
		{
			ans.push_back(it->usual_grades());
		}
		break;
	}
	case 1:
	{
		for (list<data_node>::iterator it = data.begin(); it != data.end(); it++)
		{
			ans.push_back(it->exam_scores());
		}
		break;
	}
	case 2:
	{
		for (list<data_node>::iterator it = data.begin(); it != data.end(); it++)
		{
			ans.push_back(it->grade());
		}
		break;
	}
	default:
		throw string("No such choice");
	}
	return ans;
}

void data_manager::del_index(list<data_node>::iterator target_ele)//删除索引信息
{
	num_data.erase(num_data.find(target_ele->num()));
	map<string, vector<list<data_node>::iterator>>::iterator it = name_data.find(target_ele->name());
	if (it->second.size() == 1)
		name_data.erase(it);
	else
		for (vector<list<data_node>::iterator>::iterator ip = it->second.begin(); ip != it->second.end(); ip++)
		{
			if ((*ip)->num_infohit(target_ele->num()))
			{
				it->second.erase(ip);
				break;
			}
		}
}
