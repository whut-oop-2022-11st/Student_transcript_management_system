#pragma once
#include "global.hpp"
class tool
{
public:
	string current_time();
	void operator[](short x);
	string TimeToString(time_t time);
	time_t StringToTime(char* timestr);

	void clc();
	int judday(int yy, int mm, int dd);
	time_t getday(const char* msg);
	void getday_tips();
};
extern tool tl;
