#include "lvl_1.h"


lvl_1::lvl_1(const string objectname, const int number) : objectname(objectname+"_1"), number(number) {}

void lvl_1::print() const {
	cout << this->objectname << ' ' << this->number;
}

void lvl_1::change_number(const int new_number){
	this->number = new_number;
}
