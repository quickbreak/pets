#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"

using namespace std;

#define cn cout<<'\n';

int main()
{
	// program here
	int i_data; cin >> i_data;
	Test* Example = new Test(i_data);
	Example->print(); cn;
	Example->open_change();
	Example->print(); cn;
	cin >> i_data;
	if (i_data > Example->open)
		Example->open = 8 * i_data;
	Example->print(); cn;
	Example->call_hidden_change();
	Example->print(); 
	
	cn;
	Example->~Test();
	delete Example;
	Example->~Test();

	return(0);
}