#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class class_w_a {

	int* a = NULL;

public:

	class_w_a(int number) {
		this->a = new int[number];
		for (int i = 0; i < number; ++i) {
			this->a[i] = number;
		}

	};

	~class_w_a() {
		delete this->a;
	}

	void print() {
		for (int i = 0; i < this->a[0] - 1; ++i) {
			std::cout << this->a[i] << "  ";
		}
		std::cout << this->a[this->a[0] - 1];
	};

	void set_a(int number) {
		delete this->a;
		this->a = new int[number];
		for (int i = 0; i < number; ++i) {
			this->a[i] = number;
		}
	};

	int get_a() {
		return this->a[0];

	};

	class_w_a& operator = (const class_w_a& b) {
		delete this->a;
		int number = b.a[0];
		this->a = new int[number];
		for (int i = 0; i < number; ++i)
			this->a[i] = number;
		return *this;
	}
};


int main()
{

	int number; cin >> number;
	if (number <= 4) {
		cout << number << "?";
		return 0;
	}
	class_w_a obj_1(number);
	cin >> number;
	if (number <= 4) {
		cout << number << "?";
		return 0;
	}
	class_w_a obj_2(number);
	number = obj_1.get_a(); // чтобы запомнить массив первого объекта                                                                   
	obj_1 = obj_2;
	obj_1.set_a(number);
	obj_1.print();
	cout << '\n';
	obj_2.print();
	return(0);

}