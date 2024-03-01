#include "Test.h"
#include <iostream>

//using namespace std;

Test::Test(int i_data) {
	open = i_data;
	hidden = 3 * i_data;
}

void Test::hidden_change() {
	open += 7;
	hidden += 5;
}

void Test::print() {
	std::cout << "Value of the available property " <<
		open << "; Value of a hidden property " <<
		hidden;
}

void Test::call_hidden_change() {
	hidden_change();
}

void Test::open_change() {
	open += 4;
	hidden += 1;
}