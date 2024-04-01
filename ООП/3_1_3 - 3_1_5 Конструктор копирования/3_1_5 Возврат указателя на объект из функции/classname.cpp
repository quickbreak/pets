#include "classname.h"
#include <iostream>
#include <cassert>

classname::classname() {
	std::cout << "\nDefault constructor";
};

classname::classname(int n) {
	assert(n > 2 && n % 2 == 0);
	this->len_a = n;
	std::cout << "\nConstructor set";
};

classname::classname(const classname& obj) {
	this->len_a = obj.len_a;
	this->a = new int[this->len_a];
	for (int i = 0; i < len_a; ++i) {
		this->a[i] = obj.a[i];
	}
	std::cout << "\nCopy constructor";
};

classname::~classname() {
	std::cout << "\nDestructor";
};

void classname::create_a() {
	int n = this->len_a;
	this->a = new int[n];
};

void classname::fill_a() {
	int n = this->len_a, x;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		(this->a)[i] = x;

	}

};

int classname::sum_a() {
	int n = this->len_a, summa = 0;
	for (int i = 0; i < n; ++i)
		summa += (this->a)[i];
	return summa;
};

void classname::half_sum() {
	int n = this->len_a;
	for (int i = 0; i < n - 1; i += 2)
		(this->a)[i] = (this->a)[i] + (this->a)[i + 1];
	// return this->sum_a();
};

void classname::half_product() {
	int n = this->len_a;
	for (int i = 0; i < n - 1; i += 2)
		(this->a)[i] = (this->a)[i] * (this->a)[i + 1];
	// return this->sum_a();
};

void classname::print() {
	int n = this->len_a;
	std::cout << '\n';
	std::cout << (this->a)[0];
	for (int i = 1; i < n; ++i)
		std::cout << "   " << (this->a)[i];
};

int* classname::get_a() {
	return this->a;
};

void classname::set_a(int* array) {
	this->a = array;
};
