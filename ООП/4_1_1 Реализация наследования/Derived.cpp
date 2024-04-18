#include "Derived.h"
#include <iostream>


// public:
Derived::Derived(const int private_number, const int public_number) : private_number(private_number), public_number(public_number), Base(private_number, public_number){}

void Derived::set_both(const int private_number, const int public_number) {
	this->private_number = private_number;
	this->public_number = public_number;
}

void Derived::show() const {
	std::cout << this->private_number << "    " << this->public_number;
}
