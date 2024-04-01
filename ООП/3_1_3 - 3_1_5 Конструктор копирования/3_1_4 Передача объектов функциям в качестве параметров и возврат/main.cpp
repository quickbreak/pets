#include<iostream>
#include "classname.h"

classname function(int n) {
	classname obj_local(n);
	return obj_local;
}

int32_t main() {
	int n; std::cin >> n;
	if (!(n > 2 && n % 2 == 0)) {
		std::cout << n << '?';
		return 0;
	}

	std::cout << n;
	classname obj;
	//classname obj_2 = function(n);
	obj = function(n);
	obj.create_a();
	obj.fill_a();
	obj.half_product();

	classname obj_2 = obj;
	obj_2.half_sum();
	obj.print();
	std::cout << '\n' << obj.sum_a();

	obj_2.print();
	std::cout << '\n' << obj_2.sum_a();
	
	return 0;
}

/*
4
3 5 1 2
-Default constructor
.
.
.

2
-2?

7
-7?
*/