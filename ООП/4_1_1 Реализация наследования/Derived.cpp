#include "Derived.h"
#include <iostream>


// public:
Derived::Derived(int private_number, int public_number) : private_number(private_number), public_number(public_number), Base(private_number, public_number){}

void Derived::set_both(int private_number, int public_number) {
	this->private_number = private_number;
	this->public_number = public_number;
}

void Derived::show() const {
	std::cout << this->private_number << ' ' << this->public_number;
}
