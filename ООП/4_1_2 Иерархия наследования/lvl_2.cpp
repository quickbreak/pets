#include "lvl_2.h"


lvl_2::lvl_2(const string objectname, const int number) : lvl_1(objectname, number), objectname(objectname + "_2") {
	this->number = number;
	for (int i = 1; i < 2; ++i)
		this->number *= number;
	//cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_2::print() const {
	cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_2::change_number(const int new_number) {
	this->number = new_number;
}
