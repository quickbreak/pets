#pragma once
#include <string>
#include <iostream>

using namespace std;

class lvl_1 {
private:
	string objectname;
	int number = -int(1e9);

public:
	lvl_1(const string objectname, const int number);
	void print() const;
	void change_number(const int new_number);
};

