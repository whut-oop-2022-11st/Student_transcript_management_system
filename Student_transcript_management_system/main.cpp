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
	tl[3];
	cout << R"(  _______ _____            _   _  _____  _____ _____  _____ _____ _______    _______     _______ _______ ______ __  __ 
 |__   __|  __ \     /\   | \ | |/ ____|/ ____|  __ \|_   _|  __ \__   __|  / ____\ \   / / ____|__   __|  ____|  \/  |
    | |  | |__) |   /  \  |  \| | (___ | |    | |__) | | | | |__) | | |    | (___  \ \_/ / (___    | |  | |__  | \  / |
    | |  |  _  /   / /\ \ | . ` |\___ \| |    |  _  /  | | |  ___/  | |     \___ \  \   / \___ \   | |  |  __| | |\/| |
    | |  | | \ \  / ____ \| |\  |____) | |____| | \ \ _| |_| |      | |     ____) |  | |  ____) |  | |  | |____| |  | |
    |_|  |_|  \_\/_/    \_\_| \_|_____/ \_____|_|  \_\_____|_|      |_|    |_____/   |_| |_____/   |_|  |______|_|  |_|)" << endl;
	tl[13];
	cout << tl.current_time() << endl;
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
