#include "tool.hpp"
void tool::operator[](short x)
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色 
	else//默认的颜色白色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void tool::clc()
{
	int ch = 0;
	while ((ch = getchar()) != EOF && ch != '\n')
	{
		;
	}
}
string tool::current_time()
{
	char s[101];
	chrono::system_clock::time_point now = chrono::system_clock::now();
	time_t tt = chrono::system_clock::to_time_t(now);
	ctime_s(s, 100, &tt);
	return string(s);
}

string tool::TimeToString(time_t time) {
	char* str = new char[24];
	if (!str) {
		cout << "内存不足！\n";
		return "";
	}
	struct tm* timeinfo = (struct tm*)malloc(sizeof(struct tm));
	if (!timeinfo) {
		printf("TimeToString函数出现错误！");;
		str = NULL;
		return "";
	}
	localtime_s(timeinfo, &time);
	strftime(str, 35, "%Y-%m-%d %H:%M:%S", timeinfo);
	string res = str;
	delete[] str;
	return res;
}

time_t tool::StringToTime(char* timestr) {
	struct tm* tm1 = (struct tm*)malloc(sizeof(struct tm));
	if (!tm1) {
		printf("TimeToString函数出现错误！");;
		return 0;
	}
	time_t time1;
	sscanf_s(timestr, "%d-%d-%d %d:%d:%d", &tm1->tm_year, &tm1->tm_mon,
		&tm1->tm_mday, &tm1->tm_hour, &tm1->tm_min, &tm1->tm_sec);
	tm1->tm_year -= 1900;  // 年份为从1900年开始
	tm1->tm_mon -= 1;      // 月份为0~11
	tm1->tm_isdst = -1;
	time1 = mktime(tm1);
	free(tm1);
	return time1;
}


//判断日期合法性（1980年元旦-2199年12月31日）
int tool::judday(int yy, int mm, int dd) {
	//1980年为限，防止边界出错
	if (yy < 1980 || yy > 2199) return 0;
	if (mm < 1 || mm >12) return 0;
	if (dd < 1) return 0;
	switch (mm) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dd > 31) return 0;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (dd > 30) return 0;
		break;
	case 2:
		if (yy % 4 == 0 && yy % 100 || yy % 400 == 0) {
			if (dd > 29) return 0;
		}
		else {
			if (dd > 28) return 0;
		}
		break;
	default:
		return 0;
	}
	return 1;
}

//请输入年月日（以xxxx-xx-xx格式）
time_t tool::getday(const char* msg) {
	time_t res = 0;
	printf(msg);
	int yy, mm, dd;
	int flag = scanf_s("%d-%d-%d", &yy, &mm, &dd);
	//对额外非法附加部分判断
	if (getchar() != '\n') {
		tl.clc();
		flag = 0;
	}
	if (!judday(yy, mm, dd)) flag = 0;
	while (flag != 3) {
		printf("时间输入有误！请重新输入：");
		flag = scanf_s("%d-%d-%d", &yy, &mm, &dd);
		//对额外非法附加部分判断
		if (getchar() != '\n') {
			tl.clc();
			flag = 0;
		}
		if (!judday(yy, mm, dd)) flag = 0;
	}
	char temp[32];
	sprintf_s(temp, 24, "%d-%d-%d 00:00:00", yy, mm, dd);
	res = tl.StringToTime(temp);
	return res;
}

//请输入年月日的提示信息（以xxxx-xx-xx格式）
void tool::getday_tips() {
	printf("日期输入格式：四位年份-月-日，如 2023-2-22 或 1997-12-31\n");
	printf("日期接受范围：1980-1-1 至 2199-12-31\n");
}
