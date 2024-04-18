#pragma once
#include "lvl_1.h"
class lvl_2 : private lvl_1 {
private:
	string objectname;
	int number = -int(1e9);

public:
	lvl_2(const string objectname, const int number);
	void print() const;
	void change_number(const int new_number);
};

