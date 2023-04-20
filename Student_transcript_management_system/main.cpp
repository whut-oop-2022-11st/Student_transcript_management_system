#include "global.hpp"
using namespace std;
data_manager manager;
tool tl;
user_service service;
int main()
{
	for (;;)
	{
		int menu();
		int i = menu();
		switch (i)
		{
		case 0:
			return 0;
		case 1:
			service.add();
			break;
		case 2:
			service.search();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	return 0;
	//try
	//{
	//	manager.node_info(manager.search_by_num("123"));
	//}
	//catch (string s)
	//{
	//	cout << s;
	//}
	//tl[6];
	//cout << endl << tl.current_time();
	//tl[20];

	//manager.push_back("123 name 65 85");
	//user_service ser;
	//ser.search();
	//manager.push_back("asd snhjdss 123 465");f
	//manager.push_back("asds snhjsxsa 123 465");
	//manager.push_back("assds vsnhjsxsa 123 465");

	//auto x = manager.search_by_name("s*", false, true);
	//for (auto y : x)
	//{
	//	cout << y->show_all_ele() << endl;
	//}

	//string a = "你好", info = "*好*";
	//size_t x = info.find('x');
	//size_t i;


	//manager.push_back("123 name 65 85");
	//try
	//{
	//	manager.push_back("1234 name 65 85");
	//}
	//catch (string err_info)
	//{
	//	cout << err_info;
	//}
	////auto x = manager.search_by_num("123");
	//manager.del(manager.search_by_num("123"));
	//auto y = manager.search_by_name("name");
	//for (auto p : y)
	//{
	//	cout << p->show_all_ele() << endl;
	//}
	//manager.change(manager.search_by_num("1234"), "123 aa 56 85");
	//y = manager.search_by_name("aa");
	//for (auto p : y)
	//{
	//	cout << p->show_all_ele() << endl;
	//}
	//manager.push_back("1234 name 65 85");
	//manager.push_back("1235 name 65 85");
	//manager.push_back("1236 name 65 85");
	//manager.push_back("1237 name 65 85");
	//manager.del(manager.search_by_num("123"));
	//auto z = manager.all_node_info_by_num();
	//for (auto p : z)
	//{
	//	cout << p << endl;
	//}
	//manager.update_index();
	//z = manager.all_node_info_by_num();
	//for (auto p : z)
	//{
	//	cout << p << endl;
	//}
	////cout << x->show_all_ele();
	//return 0;
}
