#pragma once
class Base {
private:
	int private_number;
	// изменить скрытое поле int private_number
	void set_private_number(const int private_number);

public:
	int public_number;
	//Base();
	// параметризированный конструктор
	Base(const int private_number = -int(1e9), const int public_number = -int(1e9));
	// изменить скрытое int private_number и открытое int public_number поля
	void set_both(const int private_number, const int public_number);
	// вывести скрытое int private_number и открытое int public_number поля
	void show() const;

};

