#include "user_service.hpp"
using namespace std;
void user_service::add()
{
}

void user_service::search()
{
	cout << "请输入查询的学号" << endl;
	string student;
	cin >> student;
	auto it = manager.search_by_num(student);
	if (it == data.end())
	cout << it->show_all_ele() << endl;
}
