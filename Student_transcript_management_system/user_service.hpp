﻿#pragma once
#include "global.hpp"
class user_service
{
public:
	void add();
	void search();
	void del();
	void change();
	void show();
	void stats();
	void show_log();
private:
	void head();
	void scout(string s);
};
extern user_service service;
