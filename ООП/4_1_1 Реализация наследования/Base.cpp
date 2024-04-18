#include "Base.h"
#include <iostream>

//private:
void Base::set_private_number(const int private_number) {
	this->private_number = 2 * private_number;

}

// public:
Base::Base(const int private_number, const int public_number):public_number(public_number) {
	this->set_private_number(private_number);
}

void Base::set_both(const int private_number, const int public_number) {
	this->set_private_number(private_number);
	this->public_number = public_number;
}

void Base::show() const {
	std::cout << this->private_number << "    " << this->public_number;
}
