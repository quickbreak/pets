#pragma once
#include "lvl_2.h"
class lvl_3 : private lvl_2 {
private:
	string objectname;
	int number = -int(1e9);

public:
	lvl_3(const string objectname, const int number);
	void print() const;
	void change_number(const int new_number);
};

