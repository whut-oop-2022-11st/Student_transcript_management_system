#pragma once
#include "global.hpp"
class user_service
{
public:
	void add();
	void search();
	void del();
	void change();
	void stats();
private:
};
extern user_service service;
