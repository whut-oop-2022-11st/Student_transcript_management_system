#include "global.hpp"
using namespace std;
data_manager manager;
tool tl;
user_service service;
encipher enci;
log_manager Log;
string logfile = "log.dat";
int main()
{
	manager.load();
	manager.update_index();
	errno_t err = 0;
	do
	{
		int login();
		err = login();
		if (err == -1)
		{
			return -1;
		}
	} while (err != 0);
	for (;;)
	{
		int menu();
		int i = menu();
		switch (i)
		{
		case 0:
			manager.save();
			return 0;
		case 1:
			service.add();
			break;
		case 2:
			service.search();
			break;
		case 3:
			service.change();
			break;
		case 4:
			service.del();
			break;
		case 5:
			service.show();
			break;
		case 6:
			service.stats();
			break;
		case 7:
			service.show_log();
			break;
		}
	}
	return 0;
}
