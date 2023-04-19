#pragma once
#include "global.hpp"
using namespace std;
class data_node;
class data_manager
{
public:
	void push_back(string info);//在链表尾部添加一个用户节点，通过string方式 eg:manager.push_back("num name usual_grades exam_scores")
	void push_back(vector<string>info);//同上，但是传入一个vector<string>类型数据 内部包含 info[0]="num" info[1]="name" info[2]="usual_grades" info[3]="exam_scores"
	void push_back(data_node node);//不建议使用
	void del(list<data_node>::iterator del_ele);//删除元素，要求传入对应元素迭代器（指针）,可用下面的search方法获得
	void change(list<data_node>::iterator change_ele, string info);//改变元素信息，
	void change(list<data_node>::iterator change_ele, vector<string>info);
	void save(string path = "./data.db");//保存信息，缺省值为./data.db
	void load(string path = "./data.db");//读取信息，缺省值为./data.db
	string node_info(list<data_node>::iterator node);//返回迭代器所指节点的所有信息，以string方式返回
	list<data_node>::iterator search_by_num(string info);//通过学号搜索学生，返回对应迭代器
	vector<list<data_node>::iterator> search_by_name(string info, bool use_fuzzy_sezrch_if_no_ans = false, bool Regex_Search = false);//通过姓名搜索学生，返回迭代器组（同名情况）,use_fuzzy_search:使用模糊搜索
	vector<string> all_node_info_by_num();//学号按字典序输出，返回字符串组
	size_t length();//返回信息数量
	size_t size();//返回信息数量
	list<data_node>::iterator& operator[](int i);//重载[]操作符，提供下标访问支持（随机访问支持）
	void update_index();//更新索引信息，一般不需要使用
private:
	void del_index(list<data_node>::iterator target_ele);//删除节点索引信息
	list<data_node>data;//数据
	map<string, vector<list<data_node>::iterator>>name_data;//名字索引信息
	map<string, list<data_node>::iterator>num_data;//学号索引信息
	vector<list<data_node>::iterator>sequence_data;//下标访问支持
	vector<size_t>del_eles;//删除的元素（下标访问支持）
};
extern data_manager manager;
