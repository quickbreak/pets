#include "Derived.h"
#include<iostream>

using namespace std;

int32_t main() {
	int private_number, public_number; cin >> private_number >> public_number;
	Derived object(private_number, public_number);
	object.Base::show();
	cout << '\n';
	object.show();
	cout << '\n';
	if (private_number > 0) {
		object.set_both(private_number + 1, public_number + 1);
		object.Base::set_both(private_number - 1, public_number - 1);
		object.show();
		cout << '\n';
		object.Base::show();
	}
	else {
		object.Base::set_both(private_number + 1, public_number + 1);
		object.set_both(private_number - 1, public_number - 1);
		object.Base::show();
		cout << '\n';
		object.show();
	}
}