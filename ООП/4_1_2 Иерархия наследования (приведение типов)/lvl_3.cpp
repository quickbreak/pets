#include "lvl_3.h"


lvl_3::lvl_3(const string objectname, const int number) : lvl_2(objectname, number), objectname(objectname + "_3") {
	this->number = number;
	for (int i = 1; i < 3; ++i)
		this->number *= number;
	//cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_3::print() const {
	cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_3::change_number(const int new_number) {
	this->number = new_number;
}
