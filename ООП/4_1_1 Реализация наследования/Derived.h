#pragma once
#include "Base.h"
class Derived : public Base {
private:
	int private_number;

public:
	int public_number;
	// параметризированный конструктор
	Derived(const int private_number = -int(1e9), const int public_number = -int(1e9));
	// изменить скрытое int private_number и открытое int public_number поля
	void set_both(const int private_number, const int public_number);
	// вывести скрытое int private_number и открытое int public_number поля
	void show() const;
};

