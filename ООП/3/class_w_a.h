#ifndef __HEADING__H
#define __HEADING__H
//#include <vector>

class class_w_a {
	int* a;
public:
	class_w_a(int number);
	//std::vector<int>*a = new std::vector<int>;
	void set_a(int* b);
	int* get_a();
	void print();
	~class_w_a();
};

#endif
