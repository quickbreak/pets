#pragma once
#include "lvl_3.h"
class lvl_4 final: private lvl_3 {
private:
	string objectname;
	int number = -int(1e9);

public:
	lvl_4(const string objectname, const int number);
	void print() const;
	void change_number(const int new_number);
};

