#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Test.h"


using namespace std;
using ll = long long;


#define cn cout<<'\n';


int main(){
	// program hereint i_data; 
	cin >> i_data;
	Test Example(i_data);
	Example.print(); cn;
	Example.open_change();
	Example.print(); cn;
	cin >> i_data;
	Example.open*=i_data;
	Example.print(); cn;
	Example.call_hidden_change();
	Example.print(); cn;
	return(0);
}