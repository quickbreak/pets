#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class class_w_a {

	int* a;

public:

	class_w_a(int number) {
		a = new int[number];
		for (int i = 0; i < number; ++i) {
			a[i] = number;
		}

	};

	~class_w_a() {
		delete a;
	}

	void print() {
		{
			for (int i = 0; i < a[0] - 1; ++i) {
				std::cout << a[i] << "  ";
			}
			std::cout << a[a[0] - 1];
		}
	};

	void set_a(int* b) {
		a = b;

	};

	int* get_a() {
		return a;

	};
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
	int* p_a = obj_1.get_a(); // спасение поля а первого объекта
	obj_1 = obj_2;
	obj_1.set_a(p_a);
	obj_1.print();
	cout << '\n';
	obj_2.print();
	return(0);

}