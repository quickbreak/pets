#include<iostream>
#include "classname.h"

void function(classname obj) {
	std::cout << '\n' << obj.half_product();
}

int32_t main() {
	int n; std::cin >> n;
	if (!(n > 2 && n % 2 == 0)) {
		std::cout << n << '?';
		return 0;
	}

	std::cout << n;
	classname obj(n);
	obj.fill_a();
	function(obj);
	std::cout << '\n' << obj.half_sum();
}

/*
8
1 2 3 4 5 6 7 8
*/