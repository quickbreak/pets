#include "classname.h"
#include <iostream>
#include <cassert>
#include <vector>

classname::classname() {
	std::cout << "\nDefault costructor";
};

classname::classname(int n) {
	assert(n > 2 && n % 2 == 0);
	this->len_a = n;
	std::cout << "\nCostructor set";
};

classname::classname(const classname& obj) {
	len_a = obj.len_a;
	a = obj.a;
	std::cout << "\nCopy constructor";
};

classname::~classname() {
	std::cout << "\nDestructor";
};

void classname::create_a() {
	this->a.assign(this->len_a, 0);
};

void classname::fill_a() {
	int n = this->len_a, x;
	for (int i = 0; i < n; ++i) {
		std::cin >> x;
		this->a[i] = x;
	}
};

int classname::sum_a() {
	int n = this->len_a;
	int summa = 0;
	for (int i = 0; i < n; ++i)
		summa += this->a[i];
	return summa;
};

int classname::half_sum() {
	int n = this->len_a;
	for (int i = 0; i < n - 1; i += 2) {
		this->a[i] = this->a[i] + this->a[i + 1];
	}
	return this->sum_a();
};

int classname::half_product() {
	int n = this->len_a;
	for (int i = 0; i < n - 1; i += 2) {
		this->a[i] = this->a[i] * this->a[i + 1];
	}
	return this->sum_a();
};

void classname::print() {
	int n = this->len_a;
	std::cout << '\n';
	std::cout << this->a[0];
	for (int i = 1; i < n; ++i)
		std::cout << "   " << this->a[i];
};