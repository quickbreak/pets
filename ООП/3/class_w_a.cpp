#include "class_w_a.h"
#include <iostream>

class_w_a::class_w_a(int number) {
	a = new int[number];
	for (int i = 0; i < number; ++i) {
		a[i] = number;
	}

};

class_w_a::~class_w_a() {
	delete a;
}

void class_w_a::print() {
	{
		for (int i = 0; i < a[0] - 1; ++i) {
			std::cout << a[i] << "  ";
		}
		std::cout << a[a[0] - 1];
	}
};

void class_w_a::set_a(int* b) {
	a = b;

};

int* class_w_a::get_a() {
	return a;

};
