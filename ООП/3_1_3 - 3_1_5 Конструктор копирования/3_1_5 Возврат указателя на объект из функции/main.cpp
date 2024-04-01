//#include <stdlib.h>
//#include <stdio.h>
#include <iostream>
#include "classname.h"

classname* function(int n) {
	classname* pointer_obj = new classname(n);
	pointer_obj->create_a();
	pointer_obj->fill_a();
	pointer_obj->half_product();

	return pointer_obj;

}

int32_t main()
{
	setlocale(0, "RU");
	//int* pointer = new int[4];
	////std::cout << pointer[2];
	//pointer[0] = 7;
	//pointer[1] = 8;
	//pointer[2] = 5;
	//pointer[3] = 10;
	//for(int i=0;i<4;++i)
	//	std::cout << pointer [i];
	int n; std::cin >> n;
	if (!(n > 2 && n % 2 == 0)) {
		std::cout << n << '?';
		return 0;
	}
	std::cout << n;

	classname* p_1; 
	p_1 = function(n); 
	p_1->half_sum(); 


	//int* array_1 = &(*(p_1->get_a()));
	classname* p_2 = new classname(*p_1); 
	//std::cout << '\n';
	//std::cout << p_1 << '\n' << p_2;
	p_2->half_product(); 

	//p_1->set_a(array_1);
	p_1->print(); 
	std::cout << '\n' << p_1->sum_a(); 

	p_2->print(); 
	std::cout << '\n' << p_2->sum_a(); 

	int* array_2 = p_2->get_a();

	/*std::cout << "\nДо присвоения";
	p_1->print();
	p_2->print();
	std::cout << "\nBuba1";*/
	
	// если присваивать неразыменованные указатели,
	// они станут указывать на одну и ту же область памяти -
	// первый объект. Ну а второй объект с его
	// полями "пропадут", "потеряются"
	*p_2 = *p_1; // присвоение второму объекту первого объекта

	/*std::cout << "\nПрисвоили";
	p_1->print();
	p_2->print();
	std::cout << "\nBuba2";*/

	p_2->set_a(array_2); 

	/*std::cout << "\nВернули второму";
	p_1->print();
	p_2->print();
	std::cout << "\nBuba3";*/

	p_1->half_sum(); 

	/*std::cout << "\nСуммнули первый";
	p_1->print();
	p_2->print();
	std::cout << "\nBuba4";*/

	p_2->print(); 
	std::cout << '\n' << p_2->sum_a(); 

	delete p_1;
	delete p_2;

	return(0);
}
/*
4
3 5 1 2

4
Constructor set
Copy constructor
20  5  4  2
31
100  5  8  2
115
100  5  8  2
115
Destructor
Destructor
*/
