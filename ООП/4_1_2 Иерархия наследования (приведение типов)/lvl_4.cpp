#include "lvl_4.h"


lvl_4::lvl_4(const string objectname, const int number) : lvl_3(objectname, number), objectname(objectname + "_4") {
	this->number = number;
	for (int i = 1; i < 4; ++i)
		this->number *= number;
	//cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_4::print() const {
	cout << '\n' << this->objectname << ' ' << this->number;
}

void lvl_4::change_number(const int new_number) {
	this->number = new_number;
}
